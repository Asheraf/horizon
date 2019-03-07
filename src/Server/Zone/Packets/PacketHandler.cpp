/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#include "PacketHandler.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Definitions/Client.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/MapThreadContainer.hpp"
#include "Server/Zone/Game/Map/Script/ScriptManager.hpp"
#include "Server/Zone/Game/Status/Status.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Zone.hpp"
#include "Utility/Utility.hpp"

#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "Server/Zone/Packets/Ragexe/PacketStructs.hpp"

#include <boost/bind.hpp>
#include <algorithm>

using namespace Horizon::Zone;
using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Models;
using namespace Horizon::Models::Character;

/**
 * @brief Packet Handler Constructor.
 */
PacketHandler::PacketHandler(std::shared_ptr<ZoneSocket> socket)
: Horizon::Base::PacketHandler<ZoneSocket>(socket)
{
	_session = socket->get_session();
	initialize_handlers();
}

/**
 * @brief Packet Handler destructor.
 */
PacketHandler::~PacketHandler()
{
}

/**
 * @brief Initialize packet handlers.
 */
void PacketHandler::initialize_handlers()
{
#define HANDLER_FUNC(packet) add_packet_handler(Ragexe::packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_CLIENT_VERSION)
	HANDLER_FUNC(CZ_RESTART)
	HANDLER_FUNC(CZ_REQ_DISCONNECT)
	HANDLER_FUNC(CZ_CHANGE_DIRECTION)
	HANDLER_FUNC(CZ_CHANGE_DIRECTION2)
	// Chat
	HANDLER_FUNC(CZ_REQUEST_CHAT)
	// Script
	HANDLER_FUNC(CZ_CONTACTNPC)
	HANDLER_FUNC(CZ_REQ_NEXT_SCRIPT)
	HANDLER_FUNC(CZ_CLOSE_DIALOG)
	HANDLER_FUNC(CZ_CHOOSE_MENU)
	// Items
	HANDLER_FUNC(CZ_USE_ITEM)
	HANDLER_FUNC(CZ_USE_ITEM2)
	HANDLER_FUNC(CZ_REQ_WEAR_EQUIP)
	HANDLER_FUNC(CZ_REQ_WEAR_EQUIP_V5)
	HANDLER_FUNC(CZ_REQ_TAKEOFF_EQUIP)
	HANDLER_FUNC(CZ_USE_ITEM)
	HANDLER_FUNC(CZ_USE_ITEM2)
	// Status
	HANDLER_FUNC(CZ_STATUS_CHANGE)
	// Map
	HANDLER_FUNC(CZ_NOTIFY_ACTORINIT)
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/
bool PacketHandler::Handle_CZ_CLIENT_VERSION(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CLIENT_VERSION pkt;

	pkt << buf;

	ZoneLog->info("Account '{}' has successfully logged in.", get_socket()->get_session()->get_game_account()->get_id());

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_TIME(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQUEST_TIME pkt(buf.getOpCode());

	pkt << buf;

	Send_ZC_NOTIFY_TIME();

	return true;
}

bool PacketHandler::Handle_CZ_REQNAME(PacketBuffer &buf)
{
	std::shared_ptr<Player> player = get_socket()->get_session()->get_player();
	Ragexe::PACKET_CZ_REQNAME pkt(buf.getOpCode());
	pkt << buf;

	std::shared_ptr<Game::Entity> entity = player->get_nearby_entity(pkt.guid);

	if (entity == nullptr)
		return true;

	Send_ZC_ACK_REQNAME(entity->get_guid(), entity->get_name());

	return true;
}

bool PacketHandler::verify_new_connection(uint32_t auth_code, uint32_t account_id, uint32_t char_id)
{
	std::shared_ptr<ZoneSession> session = get_socket()->get_session();
	std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();

	if (!session_data->load(ZoneServer, account_id)) {
		ZoneLog->info("New connection attempt from unauthorized session '{}'.", auth_code);
		session->get_packet_handler()->Send_ZC_REFUSE_ENTER(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();

	if (!game_account->load(ZoneServer, account_id)) {
		ZoneLog->info("New connection attempt from unknown account '{}'.", account_id);
		session->get_packet_handler()->Send_ZC_REFUSE_ENTER(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	session->set_session_data(session_data);
	session->set_game_account(game_account);
	session->set_character(std::make_shared<Models::Character::Character>(char_id));

	if (!session->get_character()->load_all(ZoneServer, char_id)) {
		ZoneLog->error("Attempted connection for non-existent character {} by account {}.", account_id, char_id);
		session->get_packet_handler()->Send_ZC_REFUSE_ENTER(ZONE_SERV_ERROR_REJECT);
		return false;
	}

	return true;
}

bool PacketHandler::process_player_entry()
{
	std::shared_ptr<ZoneSession> session = get_socket()->get_session();
	std::shared_ptr<Position> position = session->get_character()->get_position_data();

	// Initilaize The Player
	MapCoords mcoords(position->get_current_x(), position->get_current_y());

	std::shared_ptr<Map> map = MapMgr->get_map(position->get_current_map());

	if (map == nullptr) {
		ZoneLog->error("PacketHandler::process_player_entry: Map '{}' was not found or managed by any container! Login to session '{}' is denied.", position->get_current_map(), session->get_session_data()->get_auth_code());
		return false;
	}

	std::shared_ptr<Player> player = std::make_shared<Player>(session->get_game_account()->get_id(), map, mcoords, session);
	session->set_player(player);
	set_player(player);

	player->set_map(map);
	map->get_map_container()->add_player(player);

	// Remove socket from updates on zone server after initial connection
	// it will be managed by the map container thread.
	ClientSocktMgr->set_socket_for_removal(get_socket());

	ZoneLog->info("New connection established for account '{}' using version '{}' from '{}'.",
				  session->get_game_account()->get_id(), session->get_session_data()->get_client_version(), get_socket()->remote_ip_address());

	return true;
}

bool PacketHandler::Handle_CZ_ENTER(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_ENTER pkt(buf.getOpCode());

	pkt << buf;

	if (!verify_new_connection(pkt.auth_code, pkt.account_id, pkt.char_id))
		return false;

	if (!process_player_entry())
		return false;

	// Send initial packets.
	Send_ZC_AID();
	Send_ZC_ACCEPT_ENTER3();

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_ACT(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQUEST_ACT pkt(buf.getOpCode());
	pkt << buf;
	printf("act %d %d\n", pkt.target_guid, pkt.action);

	return true;
}

bool PacketHandler::Handle_CZ_REQUEST_MOVE(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQUEST_MOVE pkt;
	pkt << buf;
	get_player()->move_to_pos(pkt.x, pkt.y);
	return true;
}

bool PacketHandler::Handle_CZ_RESTART(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_RESTART pkt(buf.getOpCode());

	pkt << buf;

	switch (pkt.type)
	{
	case 0: std::cout << "Respawn" << std::endl; break;
	case 1:
			Send_ZC_RESTART_ACK(1);
			get_player()->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
			break;
	}

	return true;
}

bool PacketHandler::Handle_CZ_REQ_DISCONNECT(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQ_DISCONNECT pkt;

	pkt << buf;
	ZoneLog->info("Character '{}' has logged out. {}", get_session()->get_character()->get_name(), pkt.type);
	Send_ZC_ACK_REQ_DISCONNECT(true);
	get_session()->get_session_data()->remove(ZoneServer);
	get_player()->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
	return true;
}

bool PacketHandler::Handle_CZ_CHOOSE_MENU(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CHOOSE_MENU pkt;

	pkt << buf;

	if (pkt.choice != -1) {
		auto scr_mgr = get_player()->get_map()->get_map_container()->get_script_manager();
		scr_mgr->continue_npc_script_for_player(get_player(), pkt.guid, pkt.choice);
	}

	return true;
}

bool PacketHandler::Handle_CZ_CONTACTNPC(PacketBuffer &buf)
{
	uint32_t current_npc_guid = get_player()->get_npc_contact_guid();
	Ragexe::PACKET_CZ_CONTACTNPC pkt;

	pkt << buf;

	if (current_npc_guid != 0 && current_npc_guid != pkt.guid) {
		ZoneLog->warn("Player {} has attempted to contact npc {} while already engaged in another npc {}. Possible hacking!", get_player()->get_name(), pkt.guid, current_npc_guid);
		return true;
	}

	auto scr_mgr = get_player()->get_map()->get_map_container()->get_script_manager();
	scr_mgr->contact_npc_for_player(get_player(), pkt.guid);

	return true;
}

bool PacketHandler::Handle_CZ_REQ_NEXT_SCRIPT(PacketBuffer &buf)
{
	uint32_t current_npc_guid = get_player()->get_npc_contact_guid();
	Ragexe::PACKET_CZ_REQ_NEXT_SCRIPT pkt;

	pkt << buf;

	if (pkt.guid == current_npc_guid) {
		auto scr_mgr = get_player()->get_map()->get_map_container()->get_script_manager();
		scr_mgr->continue_npc_script_for_player(get_player(), pkt.guid);
	} else {
		ZoneLog->warn("Player {} has attempted to contact npc {} while already engaged in another npc {}. Possible hacking!", get_player()->get_name(), pkt.guid, current_npc_guid);
	}

	return true;
}

bool PacketHandler::Handle_CZ_CLOSE_DIALOG(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CLOSE_DIALOG pkt;

	pkt << buf;

	if (pkt.guid == get_player()->get_npc_contact_guid()) {
		get_player()->set_npc_contact_guid(0);
	}

	return true;
}

bool PacketHandler::Handle_CZ_INPUT_EDITDLG(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_INPUT_EDITDLG pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_INPUT_EDITDLGSTR(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_INPUT_EDITDLGSTR pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_CHANGE_DIRECTION(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_CHANGE_DIRECTION pkt;

	pkt << buf;

	return true;
}

bool PacketHandler::Handle_CZ_CHANGE_DIRECTION2(PacketBuffer &buf)
{
	return Handle_CZ_CHANGE_DIRECTION(buf);
}

bool PacketHandler::Handle_CZ_REQUEST_CHAT(PacketBuffer &buf)
{
	uint32_t guid = get_player()->get_guid();
	Ragexe::PACKET_CZ_REQUEST_CHAT pkt;
	int msg_first_char = get_player()->get_name().size() + 3;

	pkt << buf;

	if (pkt.message[msg_first_char] == '@') {
		get_player()->get_script_manager()->perform_command_from_player(get_player(), &pkt.message[msg_first_char + 1]);
		return true;
	}

	Send_ZC_NOTIFY_CHAT(guid, pkt.message, GRID_NOTIFY_AREA_WOS);
	Send_ZC_NOTIFY_PLAYERCHAT(pkt.message);

	return true;
}

bool PacketHandler::Handle_CZ_USE_ITEM(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_USE_ITEM pkt;
	pkt << buf;
	get_player()->get_inventory()->use_item(pkt.inventory_index - 2, pkt.guid);
	return true;
}

bool PacketHandler::Handle_CZ_USE_ITEM2(PacketBuffer &buf)
{
	return Handle_CZ_USE_ITEM(buf);
}

bool PacketHandler::Handle_CZ_REQ_WEAR_EQUIP(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQ_WEAR_EQUIP pkt;
	pkt << buf;
	get_player()->get_inventory()->equip_item(pkt.inventory_index - 2, pkt.equip_location_mask);
	return true;
}

bool PacketHandler::Handle_CZ_REQ_WEAR_EQUIP_V5(PacketBuffer &buf)
{
	return Handle_CZ_REQ_WEAR_EQUIP(buf);
}

bool PacketHandler::Handle_CZ_REQ_TAKEOFF_EQUIP(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_REQ_TAKEOFF_EQUIP pkt;
	pkt << buf;

	get_player()->get_inventory()->unequip_item(pkt.inventory_index - 2);
	return true;
}

bool PacketHandler::Handle_CZ_STATUS_CHANGE(PacketBuffer &buf)
{
	uint32_t stat = 0;
	Ragexe::PACKET_CZ_STATUS_CHANGE pkt;
	pkt << buf;

	stat = get_player()->get_status()->increase_status_point((status_point_type) pkt.type, pkt.amount);

	Send_ZC_STATUS_CHANGE_ACK((status_point_type) pkt.type, stat ? true : false, stat);
	return true;
}

bool PacketHandler::Handle_CZ_NOTIFY_ACTORINIT(PacketBuffer &buf)
{
	Ragexe::PACKET_CZ_NOTIFY_ACTORINIT pkt;
	get_player()->on_map_enter();
	return true;
}
/*==============*
 * Sender Methods
 *==============*/
void PacketHandler::Send_ZC_REFUSE_ENTER(zone_server_reject_type error)
{
	Ragexe::PACKET_ZC_REFUSE_ENTER pkt;
	pkt.error = error;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_RESTART_ACK(uint8_t type)
{
	Ragexe::PACKET_ZC_RESTART_ACK pkt;
	pkt.type = type;
	send_packet(pkt.serialize());

	ZoneLog->info("Character '{}' has moved to the character server.", get_session()->get_character()->get_name());
}

void PacketHandler::Send_ZC_ACK_REQ_DISCONNECT(bool allowed)
{
	Ragexe::PACKET_ZC_ACK_REQ_DISCONNECT pkt;
	pkt.type = allowed ? 0 : 1;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_AID()
{
	Ragexe::PACKET_ZC_AID pkt;
	pkt.account_id = get_session()->get_game_account()->get_id();
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_ACCEPT_ENTER3()
{
	std::shared_ptr<Models::Character::Character> character = get_socket()->get_session()->get_character();
	std::shared_ptr<Position> position = character->get_position_data();
	std::shared_ptr<UISettings> ui_settings = character->get_ui_settings();

	Ragexe::PACKET_ZC_ACCEPT_ENTER3 pkt;
	int x = position->get_current_x();
	int y = position->get_current_y();

	if (x == 0 && y == 0) {
		if ((x = position->get_saved_x()) == 0)
			x = 0;
		if ((y = position->get_saved_y()) == 0)
			y = 0;
	}

	pkt.start_time = (uint32_t) get_sys_time();
	pkt.x_size = pkt.y_size = 5;
	pkt.font = ui_settings->get_font();
	pkt.gender = character->get_gender();
	send_packet(pkt.serialize(x, y, DIR_SOUTH));
}

void PacketHandler::Send_ZC_ACCEPT_ENTER2()
{
	std::shared_ptr<Models::Character::Character> character = get_socket()->get_session()->get_character();
	std::shared_ptr<Models::Character::Position> position = character->get_position_data();
	std::shared_ptr<Models::Character::UISettings> ui_settings = character->get_ui_settings();

	Ragexe::PACKET_ZC_ACCEPT_ENTER2 pkt;
	int x = position->get_current_x();
	int y = position->get_current_y();

	if (x == 0 && y == 0) {
		if ((x = position->get_saved_x()) == 0)
			x = 0;
		if ((y = position->get_saved_y()) == 0)
			y = 0;
	}

	pkt.start_time = (uint32_t) get_sys_time();
	pkt.x_size = pkt.y_size = 5;
	pkt.font = ui_settings->get_font();
	send_packet(pkt.serialize(x, y, DIR_SOUTH));
}

void PacketHandler::Send_ZC_NPCACK_MAPMOVE(std::string map_name, uint16_t x, uint16_t y)
{
	Ragexe::PACKET_ZC_NPCACK_MAPMOVE pkt;

	if (map_name.size() + 4 > MAP_NAME_LENGTH_EXT) {
		ZoneLog->error("Copying '.gat' to map name {} would exceed length.", map_name);
		return;
	}

	map_name.append(".gat");

	strncpy(pkt.map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);

	pkt.x = x;
	pkt.y = y;

	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_TIME()
{
	Ragexe::PACKET_ZC_NOTIFY_TIME pkt;
	pkt.timestamp = (uint32_t) get_sys_time();
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_MOVE(uint32_t guid, MapCoords from, MapCoords to)
{
	std::shared_ptr<Models::Character::Character> character = get_session()->get_character();
	Ragexe::PACKET_ZC_NOTIFY_MOVE pkt;

	pkt.guid = guid;

	send_packet(pkt.serialize(from.x(), from.y(), to.x(), to.y()));
}

void PacketHandler::Send_ZC_NOTIFY_PLAYERMOVE(uint16_t to_x, uint16_t to_y)
{
	MapCoords mcoords = get_player()->get_map_coords();
	Ragexe::PACKET_ZC_NOTIFY_PLAYERMOVE pkt;

	send_packet(pkt.serialize(mcoords.x(), mcoords.y(), to_x, to_y));
}

void PacketHandler::Send_ZC_STOPMOVE(uint32_t guid, uint16_t x, uint16_t y)
{
	Ragexe::PACKET_ZC_STOPMOVE pkt;
	pkt.guid = guid;
	pkt.x = x;
	pkt.y = y;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_PAR_CHANGE(uint16_t type, uint16_t value)
{
	Ragexe::PACKET_ZC_PAR_CHANGE pkt;
	pkt.type = type;
	pkt.value = value;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_LONGPAR_CHANGE(uint16_t type, uint16_t value)
{
	Ragexe::PACKET_ZC_LONGPAR_CHANGE pkt;
	pkt.type = type;
	pkt.value = value;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_STATUS()
{
	Ragexe::PACKET_ZC_STATUS pkt;
	std::shared_ptr<Horizon::Zone::Game::Status::Status> status = get_player()->get_status();

	pkt.data.status_points = status->get_status_point()->get_base();
	pkt.data.strength = status->get_strength()->get_base();
	pkt.data.strength_req_stats = status->get_strength_cost()->get_base();
	pkt.data.agility = status->get_agility()->get_base();
	pkt.data.agility_req_stats = status->get_agility_cost()->get_base();
	pkt.data.vitality = status->get_vitality()->get_base();
	pkt.data.vitality_req_stats = status->get_vitality_cost()->get_base();
	pkt.data.intelligence = status->get_intelligence()->get_base();
	pkt.data.intelligence_req_stats = status->get_intelligence_cost()->get_base();
	pkt.data.dexterity = status->get_dexterity()->get_base();
	pkt.data.dexterity_req_stats = status->get_dexterity_cost()->get_base();
	pkt.data.luck = status->get_luck()->get_base();
	pkt.data.luck_req_stats = status->get_luck_cost()->get_base();
	pkt.data.status_atk = status->get_status_atk()->total();
	pkt.data.equip_atk = 0;
	pkt.data.status_matk = status->get_status_matk()->total();
	pkt.data.equip_matk = 0;
	pkt.data.soft_def = status->get_soft_def()->total();
	pkt.data.hard_def = 0;
	pkt.data.soft_mdef = status->get_soft_mdef()->total();
	pkt.data.hard_mdef = 0;
	pkt.data.hit = status->get_hit()->total();
	pkt.data.flee = status->get_flee()->total();
	pkt.data.perfect_dodge = 0;
	pkt.data.critical = status->get_crit()->total();
	pkt.data.attack_speed = 0;
	pkt.data.plus_aspd = 0;

	send_packet(pkt.serialize());
}
void PacketHandler::Send_ZC_STATUS_CHANGE(status_point_type type, uint16_t amount)
{
	Ragexe::PACKET_ZC_STATUS_CHANGE pkt;
	pkt.type = (uint16_t) type;
	pkt.amount = amount;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_STATUS_CHANGE_ACK(status_point_type type, bool success, uint16_t amount)
{
	Ragexe::PACKET_ZC_STATUS_CHANGE_ACK pkt;
	pkt.type = type;
	pkt.success = success;
	pkt.amount = amount;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_COUPLESTATUS(uint32_t type, uint32_t base, uint32_t bonus)
{
	Ragexe::PACKET_ZC_COUPLESTATUS pkt;
	pkt.type = type;
	pkt.base = base;
	pkt.bonus = bonus;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_ATTACK_RANGE(uint32_t value)
{
	Ragexe::PACKET_ZC_ATTACK_RANGE pkt;
	pkt.value = value;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_SAY_DIALOG(uint32_t npc_id, std::string &message)
{
	Ragexe::PACKET_ZC_SAY_DIALOG pkt;
	pkt.packet_length = 8 + message.size();
	pkt.guid = npc_id;
	send_packet(pkt.serialize(message));
}

void PacketHandler::Send_ZC_WAIT_DIALOG(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_WAIT_DIALOG pkt;
	pkt.guid = npc_id;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_CLOSE_DIALOG(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_CLOSE_DIALOG pkt;
	pkt.guid = npc_id;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_MENU_LIST(uint32_t npc_id, std::string const &menu_list)
{
	Ragexe::PACKET_ZC_MENU_LIST pkt;
	pkt.packet_length = 8 + menu_list.size();
	pkt.guid = npc_id;
	send_packet(pkt.serialize(menu_list));
}

void PacketHandler::Send_ZC_OPEN_EDITDLG(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_OPEN_EDITDLG pkt;

	pkt.guid = npc_id;

	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_OPEN_EDITDLGSTR(uint32_t npc_id)
{
	Ragexe::PACKET_ZC_OPEN_EDITDLGSTR pkt;
	pkt.guid = npc_id;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_NEWENTRY5()
{
	Ragexe::PACKET_ZC_NOTIFY_NEWENTRY5 pkt;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_UPDATE_MAPINFO(uint16_t x, uint16_t y, const char *map_name, uint16_t type)
{
	Ragexe::PACKET_ZC_UPDATE_MAPINFO pkt;
	pkt.x = x;
	pkt.y = y;
	memcpy(pkt.map_name, map_name, sizeof(MAP_NAME_LENGTH_EXT));
	pkt.type = type;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_GROUNDSKILL(uint16_t skill_id, uint32_t guid, uint16_t level, uint16_t x, uint16_t y, uint32_t duration)
{
	Ragexe::PACKET_ZC_NOTIFY_GROUNDSKILL pkt;

	pkt.skill_id = skill_id;
	pkt.guid = guid;
	pkt.level = level;
	pkt.x = x;
	pkt.y = y;
	pkt.duration = duration;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_STANDENTRY(entity_viewport_entry const &/*entry*/)
{
	Ragexe::PACKET_ZC_NOTIFY_STANDENTRY10 pkt;
	// set here params.
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_MOVEENTRY(entity_viewport_entry const &/*entry*/)
{
	Ragexe::PACKET_ZC_NOTIFY_MOVEENTRY10 pkt;
	// set here params.
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_CHAT(uint32_t guid, std::string message, player_notifier_type type)
{
	Ragexe::PACKET_ZC_NOTIFY_CHAT pkt;
	PacketBuffer buf;

	pkt.guid = guid;
	buf = pkt.serialize(message);

	get_player()->template notify_in_area<PacketBuffer>(buf, type);
}

void PacketHandler::Send_ZC_NOTIFY_PLAYERCHAT(std::string message)
{
	Ragexe::PACKET_ZC_NOTIFY_PLAYERCHAT pkt;

	pkt.packet_length = 4 + message.size();
	send_packet(pkt.serialize(message));
}

void PacketHandler::Send_ZC_NPC_CHAT(uint32_t guid, std::string message, player_notifier_type type)
{
	Ragexe::PACKET_ZC_NPC_CHAT pkt;

	pkt.guid = guid;

	PacketBuffer buf = pkt.serialize(message);

	get_player()->template notify_in_area<PacketBuffer>(buf, type);
}

void PacketHandler::Send_ZC_ACK_REQNAME(uint32_t guid, std::string name)
{
	Ragexe::PACKET_ZC_ACK_REQNAME pkt;
	pkt.guid = guid;
	std::strncpy(pkt.name, name.c_str(), sizeof(pkt.name));
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_VANISH(uint32_t guid, uint8_t type)
{
	Ragexe::PACKET_ZC_NOTIFY_VANISH pkt;
	pkt.guid = guid;
	pkt.type = type;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NORMAL_ITEMLIST(std::vector<std::shared_ptr<item_entry_data>> const &items)
{
	Ragexe::PACKET_ZC_INVENTORY_ITEMLIST_NORMAL_V5 pkt;
	send_packet(pkt.serialize(items));
}

void PacketHandler::Send_ZC_EQUIPMENT_ITEMLIST(std::vector<std::shared_ptr<item_entry_data>> const &items)
{
	Ragexe::PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V6 pkt;
	send_packet(pkt.serialize(items));
}

void PacketHandler::Send_ZC_ITEM_PICKUP_ACK(item_entry_data id, uint16_t amount, item_inventory_addition_notif_type result)
{
	Ragexe::PACKET_ZC_ITEM_PICKUP_ACK_V7 pkt;
	send_packet(pkt.serialize(id, amount, result));
}

void PacketHandler::Send_ZC_ITEM_THROW_ACK(uint16_t inventory_index, uint16_t amount)
{
	Ragexe::PACKET_ZC_ITEM_THROW_ACK pkt;
	pkt.inventory_index = inventory_index;
	pkt.amount = amount;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_INVENTORY_MOVE_FAILED(uint16_t inventory_index, bool silent)
{
	Ragexe::PACKET_ZC_INVENTORY_MOVE_FAILED pkt;
	pkt.inventory_index = inventory_index;
	pkt.silent = silent ? 1 : 0;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_DELETE_ITEM_FROM_BODY(uint16_t inventory_index, uint16_t amount, item_deletion_reason_type reason)
{
	Ragexe::PACKET_ZC_DELETE_ITEM_FROM_BODY pkt;
	pkt.inventory_index = inventory_index;
	pkt.amount = amount;
	pkt.reason = reason;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_NOTIFY_BIND_ON_EQUIP(std::shared_ptr<const item_entry_data> item)
{
	Ragexe::PACKET_ZC_NOTIFY_BIND_ON_EQUIP pkt;
	pkt.index = item->inventory_index;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_REQ_WEAR_EQUIP_ACK(std::shared_ptr<const item_entry_data> item, item_equip_result_type result)
{
	Ragexe::PACKET_ZC_REQ_WEAR_EQUIP_ACK2 pkt;
	pkt.inventory_index = item->inventory_index;
	pkt.equip_location_mask = item->current_equip_location_mask;
	pkt.sprite_id = item->sprite_id;
	pkt.result = (uint8_t) result;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_REQ_TAKEOFF_EQUIP_ACK(std::shared_ptr<const item_entry_data> item, item_unequip_result_type result)
{
	Ragexe::PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK2 pkt;
	pkt.inventory_index = item->inventory_index;
	pkt.equip_location_mask = item->current_equip_location_mask;
	pkt.result = (uint8_t) result;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_EQUIP_ARROW(std::shared_ptr<const item_entry_data> item)
{
	Ragexe::PACKET_ZC_EQUIP_ARROW pkt;
	pkt.inventory_index = item->inventory_index;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_ACTION_MESSAGE(uint16_t message_type)
{
	Ragexe::PACKET_ZC_ACTION_MESSAGE pkt;
	pkt.message_type = message_type;
	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_MAPPROPERTY_R2(std::shared_ptr<Map> map)
{
	Ragexe::PACKET_ZC_MAPPROPERTY_R2 pkt;

	pkt.property.pvp = 0;
	pkt.property.gvg = 0;
	pkt.property.siege = 0;
	pkt.property.no_effects = 0;
	pkt.property.party_pvp = 0;
	pkt.property.pvp_kill_counter = 0;
	pkt.property.disallow_party = 0;
	pkt.property.battleground = 0;
	pkt.property.no_costume = 0;
	pkt.property.allow_carts = 0;
	pkt.property.stargladiator_miracles = 0;
	pkt.property.spare_bits = 0;

	send_packet(pkt.serialize());
}

void PacketHandler::Send_ZC_USE_ITEM_ACK(std::shared_ptr<const item_entry_data> item, bool success)
{
	Ragexe::PACKET_ZC_USE_ITEM_ACK2 pkt;

	pkt.inventory_index = item->inventory_index;
	pkt.item_id = item->item_id;
	pkt.amount = item->amount;
	pkt.guid = get_player()->get_guid();
	pkt.result = success;

	send_packet(pkt.serialize());
}
