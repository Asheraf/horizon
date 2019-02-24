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

#include "Player.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"

using namespace Horizon::Models::Character;
using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Zone;

Player::Player(uint32_t guid, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER), _session(session), _game_account(session->get_game_account()), _character_model(session->get_character()),
  _packet_handler(session->get_packet_handler())
{
}

Player::Player(uint32_t guid, MapCoords mcoords, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER, mcoords), _session(session), _game_account(session->get_game_account()), _character_model(session->get_character()),
  _packet_handler(session->get_packet_handler())
{
}

Player::Player(uint32_t guid, MapCoords mcoords, GridCoords gcoords, std::shared_ptr<ZoneSession> session)
: Unit(guid, ENTITY_PLAYER, mcoords, gcoords), _session(session), _game_account(session->get_game_account()), _character_model(session->get_character()),
  _packet_handler(session->get_packet_handler())
{
}

Player::~Player()
{
	if (has_valid_grid_reference())
		remove_grid_reference();
}

void Player::initialize()
{
	Unit::initialize();

	std::shared_ptr<Character> character = get_character();
	std::shared_ptr<Horizon::Models::Character::Status> status = get_character()->get_status_data();
	std::shared_ptr<View> view = get_character()->get_view_data();

	// Status Data
	set_strength(Status::Strength(status->get_strength(), 0, 0));
	set_agility(Status::Agility(status->get_agility(), 0, 0));
	set_vitality(Status::Vitality(status->get_vitality(), 0, 0));
	set_intelligence(Status::Intelligence(status->get_intelligence(), 0, 0));
	set_dexterity(Status::Dexterity(status->get_dexterity(), 0, 0));
	set_luck(Status::Luck(status->get_luck(), 0, 0));

	// Unit Data
	set_guid(get_session()->get_game_account()->get_id());
	set_name(character->get_name());
	set_gender(character->get_gender());
	set_hp(status->get_hp());
	set_sp(status->get_sp());
	set_max_hp(status->get_max_hp());
	set_max_sp(status->get_max_sp());
	set_base_level(status->get_base_level());
	set_job_level(status->get_job_level());
	set_job_id(status->get_job_id());

	set_hair_color_id(view->get_hair_color_id());
	set_cloth_color_id(view->get_cloth_color_id());
	set_head_top_id(view->get_head_top_view_id());
	set_head_mid_id(view->get_head_mid_view_id());
	set_head_bottom_id(view->get_head_bottom_view_id());
	set_hair_style_id(view->get_hair_style_id());
	set_shield_id(view->get_shield_id());
	set_weapon_id(view->get_weapon_id());
	set_robe_id(view->get_robe_view_id());
	set_body_style_id(view->get_body_id());

	set_direction(DIR_SOUTH);
	set_posture(POSTURE_STANDING);

	get_map()->ensure_grid_for_entity(this, get_map_coords());

	update_viewport();
}

void Player::stop_movement()
{
	MapCoords const &coords = get_map_coords();
	get_packet_handler()->Send_ZC_STOPMOVE(get_guid(), coords.x(), coords.y());
}

void Player::update(uint32_t diff)
{
	Unit::update(diff);
}

void Player::update_status()
{
}

void Player::on_movement_begin()
{
	get_packet_handler()->Send_ZC_NOTIFY_PLAYERMOVE(get_dest_pos().x(), get_dest_pos().y());
}

void Player::on_movement_end()
{
}

void Player::on_movement_step()
{
	std::shared_ptr<Position> p = get_character()->get_position_data();

	update_viewport();

	get_map()->ensure_grid_for_entity(this, get_map_coords());

	p->set_current_x(get_map_coords().x());
	p->set_current_y(get_map_coords().y());
}

void Player::update_viewport()
{
	GridViewPortUpdater updater(shared_from_this());
	GridReferenceContainerVisitor<GridViewPortUpdater, GridReferenceContainer<AllEntityTypes>> update_caller(updater);

	MapCoords lower_bounds = get_map_coords().at_range<MAX_CELLS_PER_MAP>(-MAX_VIEW_RANGE);
	MapCoords upper_bounds = get_map_coords().at_range<MAX_CELLS_PER_MAP>(MAX_VIEW_RANGE);

	get_map()->visit(lower_bounds.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>(), upper_bounds.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>(), update_caller);
}

void Player::add_entity_to_viewport(std::weak_ptr<Entity> entity)
{
	get_packet_handler()->Send_ZC_NOTIFY_STANDENTRY(create_viewport_entry(entity));
}

void Player::remove_entity_from_viewport(std::shared_ptr<Entity> entity, entity_viewport_notification_type type)
{
	get_packet_handler()->Send_ZC_NOTIFY_VANISH(entity->get_guid(), type);
}

void Player::realize_entity_movement(std::weak_ptr<Entity> entity)
{
	std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(entity.lock());
	get_packet_handler()->Send_ZC_NOTIFY_MOVEENTRY(create_viewport_entry(entity));
}

entity_viewport_entry Player::create_viewport_entry(std::weak_ptr<Entity> entity)
{
	entity_viewport_entry entry;
	std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(entity.lock());

	entry.guid = unit->get_guid();
	entry.unit_type = unit->get_type();
	entry.speed = unit->get_movement_speed();
	entry.body_state = 0;
	entry.health_state = 0;
	entry.effect_state = 0;
	entry.job_id = unit->get_job_id();
	entry.hair_style_id = unit->get_hair_style_id();
	entry.hair_color_id = unit->get_hair_color_id();
	entry.robe_id = unit->get_robe_id();
	entry.guild_id = 0;
	entry.guild_emblem_version = 0;
	entry.honor = 0;
	entry.virtue = 0;
	entry.in_pk_mode = 0;
	entry.gender = unit->get_gender();
	entry.current_x = unit->get_map_coords().x();
	entry.current_y = unit->get_map_coords().y();
	entry.current_dir = unit->get_direction();

	if (unit->is_walking()) {
		entry.to_x = unit->get_dest_pos().x();
		entry.to_y = unit->get_dest_pos().y();
	}

	entry.posture = unit->get_posture();
	entry.base_level = unit->get_base_level();
	entry.font = 1;

	if (unit->get_max_hp() > 0)
		entry.max_hp = unit->get_max_hp();

	if (unit->get_hp() > 0)
		entry.hp = unit->get_hp();

	entry.is_boss = 0;
	entry.body_style_id = 0;
	std::strncpy(entry.name, unit->get_name().c_str(), unit->get_name().size());

	switch (entry.unit_type)
	{
		case ENTITY_PLAYER:
			entry.character_id = std::dynamic_pointer_cast<Player>(unit)->get_character()->get_character_id();
			entry.x_size = entry.y_size = 0;
			break;
		case ENTITY_NPC:
		default:
			entry.x_size = entry.y_size = 0;
			break;
	}

	return entry;
}


void Player::move_to_map(std::shared_ptr<Map> map, MapCoords coords)
{
	std::shared_ptr<Player> myself = std::dynamic_pointer_cast<Player>(shared_from_this());
	std::string map_name = map->get_name();

	notify_nearby_players_of_self(EVP_NOTIFY_TELEPORT);

	{
		if (!map->get_map_container()->get_map(get_map()->get_name())) {
			get_map()->get_map_container()->remove_player(myself);
			map->get_map_container()->add_player(map_name, myself);
		}

		if (coords == MapCoords(0, 0))
			coords = map->get_random_coords();

		set_map_coords(coords);

		map->ensure_grid_for_entity(this, coords);
		set_map(map);
		get_character()->get_position_data()->set_current_map(get_map()->get_name());
	}

	get_packet_handler()->Send_ZC_NPCACK_MAPMOVE(map_name, coords.x(), coords.y());
	update_viewport();
	notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);
}

void Player::send_npc_dialog(uint32_t npc_guid, std::string dialog)
{
	get_packet_handler()->Send_ZC_SAY_DIALOG(npc_guid, dialog);
}

void Player::send_npc_next_dialog(uint32_t npc_guid)
{
	get_packet_handler()->Send_ZC_WAIT_DIALOG(npc_guid);
}

void Player::send_npc_close_dialog(uint32_t npc_guid)
{
	get_packet_handler()->Send_ZC_CLOSE_DIALOG(npc_guid);
}

void Player::send_npc_menu_list(uint32_t npc_guid, std::string const &menu)
{
	get_packet_handler()->Send_ZC_MENU_LIST(npc_guid, menu);
}
