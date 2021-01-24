/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#include "CharClientInterface.hpp"

#include "Libraries/Argon2/Argon2.hpp"
#include "Server/Common/SQL/GameAccount.hpp"
#include "Server/Common/SQL/SessionData.hpp"
#include "Server/Common/SQL/Character/Character.hpp"
#include "Server/Common/SQL/Character/Status.hpp"
#include "Server/Common/SQL/Character/Inventory.hpp"
#include "Server/Common/SQL/GameAccount.hpp"

#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/MapContainerThread.hpp"
#include "Server/Zone/Packets/TransmittedPackets.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Zone.hpp"

#include <date/date.h>
#include <sqlpp11/sqlpp11.h>
#include <sqlpp11/functions.h>
#include <sqlpp11/insert.h>


#include <memory>

using namespace Horizon::Zone;

ZoneClientInterface::ZoneClientInterface(std::shared_ptr<ZoneSession> s)
: ClientInterface(s)
{
	
}

ZoneClientInterface::~ZoneClientInterface()
{
}

bool ZoneClientInterface::login(uint32_t account_id, uint32_t char_id, uint32_t auth_code, uint32_t client_time, uint8_t gender)
{
	SQL::TableGameAccounts tga;
	SQL::TableSessionData tsd;
	SQL::TableCharacters tch;
	std::shared_ptr<sqlpp::mysql::connection> conn = sZone->get_db_connection();
	
	auto res = (*conn)(select(all_of(tsd)).from(tsd).where(tsd.game_account_id == account_id and tsd.auth_code == auth_code));
	
	if (res.empty()) {
		HLog(error) << "Login error! Session data for game account " << account_id << " and authentication code " << auth_code << " does not exist.";
		return false;
	}
	
	auto res2 = (*conn)(select(all_of(tga)).from(tga).where(tga.id == account_id));
	
	if (res2.empty()) {
		HLog(error) << "Login error! Game account with id " << account_id << " does not exist.";
		return false;
	}
	
	(*conn)(update(tsd).set(tsd.current_server = "Z").where(tsd.game_account_id == account_id and tsd.auth_code == auth_code));
	
	auto res3 = (*conn)(select(all_of(tch)).from(tch).where(tch.id == char_id));
	
	if (res3.empty()) {
		HLog(error) << "Login error! Character with ID " << char_id << " does not exist.";
		return false;
	}
	
	MapCoords mcoords(res3.front().current_x, res3.front().current_y);
	std::shared_ptr<Map> map = MapMgr->get_map(res3.front().current_map);
	std::shared_ptr<Entities::Player> pl = std::make_shared<Entities::Player>(get_session(), account_id, map, mcoords);
	
	/* Initialize Player Model */
	pl->character()._character_id = res3.front().id;
	pl->character()._account_id = res3.front().account_id;
	pl->character()._slot = res3.front().slot;
	pl->set_name(res3.front().name);
	pl->set_posture(POSTURE_STANDING);
	
	std::string acc_gender = res2.front().gender;
	std::string char_gender = res3.front().gender;
	pl->character()._gender = strcmp(char_gender.c_str(), "U") == 0
		? (strcmp(acc_gender.c_str(), "M") == 0 ? CHARACTER_GENDER_MALE : CHARACTER_GENDER_FEMALE)
		: strcmp(char_gender.c_str(), "M") == 0 ? CHARACTER_GENDER_MALE : CHARACTER_GENDER_FEMALE;
	
	pl->character()._online = true;
	pl->set_last_unique_id((uint64_t) res3.front().last_unique_id);
	
	
	ZC_AID zc_aid(get_session());
	ZC_ACCEPT_ENTER2 zc_ae2(get_session());
	
	zc_aid.deliver(account_id);
	zc_ae2.deliver(uint16_t(res3.front().current_x), uint16_t(res3.front().current_y), DIR_SOUTH, uint16_t(res3.front().font));
	
	get_session()->set_player(pl);
	map->container()->add_player(std::move(pl));
	
	ClientSocktMgr->set_socket_for_removal(get_session()->get_socket());
	
	return true;
}

void ZoneClientInterface::notify_status(std::shared_ptr<Entities::Traits::Status> status)
{
	ZC_STATUS zcs(get_session());
	zc_status_data data;
	
	data.status_points = status->get_status_point()->get_base();
	data.strength = status->get_strength()->get_base();
	data.strength_req_stats = status->get_strength_cost()->get_base();
	data.agility = status->get_agility()->get_base();
	data.agility_req_stats = status->get_agility_cost()->get_base();
	data.vitality = status->get_vitality()->get_base();
	data.vitality_req_stats = status->get_vitality_cost()->get_base();
	data.intelligence = status->get_intelligence()->get_base();
	data.intelligence_req_stats = status->get_intelligence_cost()->get_base();
	data.dexterity = status->get_dexterity()->get_base();
	data.dexterity_req_stats = status->get_dexterity_cost()->get_base();
	data.luck = status->get_luck()->get_base();
	data.luck_req_stats = status->get_luck_cost()->get_base();
	data.status_atk = status->get_status_atk()->total();
	data.equip_atk = 0;
	data.status_matk = status->get_status_matk()->total();
	data.equip_matk = 0;
	data.soft_def = status->get_soft_def()->total();
	data.hard_def = 0;
	data.soft_mdef = status->get_soft_mdef()->total();
	data.hard_mdef = 0;
	data.hit = status->get_hit()->total();
	data.flee = status->get_flee()->total();
	data.perfect_dodge = 0;
	data.critical = status->get_crit()->total();
	data.attack_speed = 0;
	data.plus_aspd = 0;
	
	zcs.deliver(data);
}

bool ZoneClientInterface::restart(uint8_t type)
{
	ZC_RESTART_ACK rpkt(get_session());
	
	switch (type) {
		case 0:
			HLog(info) << "Character is being respawned.";
			break;
		default:
			rpkt.deliver(type);
			HLog(info) << "Character has moved to the character server.";
			std::shared_ptr<Entities::Player> pl = get_session()->player();
			pl->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
			pl->character()._online = false;
			pl->map_container()->remove_player(pl);
			break;
	}
	
	return true;
}

bool ZoneClientInterface::disconnect(uint8_t type)
{
	ZC_ACK_REQ_DISCONNECT ard(get_session());
	
	ard.deliver(0); // 0 => Quit, 1 => Wait for 10 seconds
	
	std::shared_ptr<Entities::Player> pl = get_session()->player();
	pl->map_container()->remove_player(pl);
	return true;
}

bool ZoneClientInterface::walk_to_coordinates(uint16_t x, uint16_t y, uint8_t dir)
{
	get_session()->player()->move_to_coordinates(x, y);
	return true;
}

bool ZoneClientInterface::notify_time()
{
	ZC_NOTIFY_TIME pkt(get_session());
	pkt.deliver();
	return true;
}


bool ZoneClientInterface::notify_entity_name(uint32_t guid)
{
	std::shared_ptr<Entity> entity = get_session()->player()->get_nearby_entity(guid);
	
#if (CLIENT_TYPE == 'M' && PACKET_VERSION >= 20150225) \
	|| (CLIENT_TYPE == 'R' && PACKET_VERSION >= 20141126) \
	|| (CLIENT_TYPE == 'Z')
	ZC_ACK_REQNAMEALL2 req(get_session());
	req.deliver(guid, entity->name(), "", "", "", 0);
#else
	ZC_ACK_REQNAMEALL req(get_session());
	req.deliver(guid, entity->name(), "", "", "");
#endif
	
	return true;
}

entity_viewport_entry ZoneClientInterface::create_viewport_entry(std::shared_ptr<Entity> entity)
{
	entity_viewport_entry entry;
	std::shared_ptr<Entities::Traits::Status> status = entity->status();
	
	entry.guid = entity->guid();
	entry.unit_type = entity->type();
	entry.speed = status->get_movement_speed()->total();
	entry.body_state = 0;
	entry.health_state = 0;
	entry.effect_state = 0;
	entry.job_id = entity->job_id();
	entry.hair_style_id = status->get_hair_style()->get();
	entry.hair_color_id = status->get_hair_color()->get();
	entry.robe_id = status->get_robe_sprite()->get();
	entry.guild_id = 0;
	entry.guild_emblem_version = 0;
	entry.honor = 0;
	entry.virtue = 0;
	entry.in_pk_mode = 0;
	entry.current_x = entity->map_coords().x();
	entry.current_y = entity->map_coords().y();
	entry.current_dir = entity->direction();
	
	if (entity->is_walking()) {
		entry.to_x = entity->dest_coords().x();
		entry.to_y = entity->dest_coords().y();
	}
	
	entry.posture = entity->posture();
	entry.base_level = status->get_base_level()->total();
	entry.font = 1;
	
	if (status->get_max_hp()->total() > 0)
		entry.max_hp = status->get_max_hp()->total();
	
	if (status->get_current_hp()->total() > 0)
		entry.hp = status->get_current_hp()->total();
	
	entry.is_boss = 0;
	entry.body_style_id = 0;
	std::strncpy(entry.name, entity->name().c_str(), entity->name().size());
	
	switch (entry.unit_type)
	{
		case ENTITY_PLAYER:
			entry.character_id = entity->downcast<Entities::Player>()->character()._character_id;
			entry.x_size = entry.y_size = 0;
			entry.gender = entity->downcast<Entities::Player>()->character()._gender;
			break;
		case ENTITY_NPC:
		default:
			entry.x_size = entry.y_size = 0;
			break;
	}
	
	return entry;
}

bool ZoneClientInterface::notify_player_movement(MapCoords from, MapCoords to)
{
	ZC_NOTIFY_PLAYERMOVE pkt(get_session());
	pkt.deliver(from.x(), from.y(), to.x(), to.y());
	return true;
}

bool ZoneClientInterface::notify_movement_stop(int32_t guid, int16_t x, int16_t y)
{
	ZC_STOPMOVE pkt(get_session());
	pkt.deliver(guid, x, y);
	return true;
}

bool ZoneClientInterface::notify_viewport_add_entity(entity_viewport_entry entry)
{
#if PACKET_VERSION >= 20150513
	ZC_NOTIFY_STANDENTRY11 pkt(get_session());
	pkt.deliver(entry);
#endif
	return true;
}

bool ZoneClientInterface::notify_viewport_moving_entity(entity_viewport_entry entry)
{
#if PACKET_VERSION >= 20150513
	ZC_NOTIFY_MOVEENTRY11 pkt(get_session());
	pkt.deliver(entry);
#endif
	return true;
}

bool ZoneClientInterface::notify_viewport_remove_entity(std::shared_ptr<Entity> entity, entity_viewport_notification_type type)
{
	ZC_NOTIFY_VANISH pkt(get_session());
	pkt.deliver(entity->guid(), type);
	return true;
}

void ZoneClientInterface::notify_npc_dialog(uint32_t npc_guid, std::string dialog)
{
	
}

void ZoneClientInterface::notify_npc_next_dialog(uint32_t npc_guid)
{
	
}

void ZoneClientInterface::ZoneClientInterface::notify_npc_close_dialog(uint32_t npc_guid)
{
	
}

void ZoneClientInterface::notify_npc_menu_list(uint32_t npc_guid, std::string const &menu)
{
	
}

