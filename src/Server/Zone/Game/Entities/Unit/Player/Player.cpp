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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "Player.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Models::Character;
using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;

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
	//
}

void Player::initialize()
{
	Unit::initialize();

	std::shared_ptr<Character> character = get_character();
	std::shared_ptr<Status> status = get_character()->get_status_data();
	std::shared_ptr<View> view = get_character()->get_view_data();

	set_guid(get_game_account()->get_id());
	set_name(character->get_name());
	set_gender(character->get_gender());
	set_hp(status->get_hp());
	set_sp(status->get_sp());
	set_max_hp(status->get_max_hp());
	set_max_sp(status->get_max_sp());
	set_base_level(status->get_base_level());
	set_job_level(status->get_job_level());
	set_job_id(status->get_job_class());

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
	std::shared_ptr<Position> p = get_character()->get_position_data();

	get_packet_handler()->Send_ZC_NOTIFY_PLAYERMOVE(get_dest_pos().x(), get_dest_pos().y());

	p->set_current_x(get_map_coords().x());
	p->set_current_y(get_map_coords().y());
}

void Player::on_movement_end()
{

}

void Player::on_movement_step()
{
	update_viewport();
	get_map()->ensure_grid_for_entity(this, get_map_coords());
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

void Player::realize_entity_movement(std::weak_ptr<Entity> entity)
{
	std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(entity.lock());
	get_packet_handler()->Send_ZC_NOTIFY_MOVEENTRY(create_viewport_entry(entity));
}

entity_viewport_entry Player::create_viewport_entry(std::weak_ptr<Entity> entity)
{
	entity_viewport_entry entry;
	std::shared_ptr<Unit> unit = std::dynamic_pointer_cast<Unit>(entity.lock());

	entry.guid = entry.account_id = unit->get_guid();
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
			entry.x_size = entry.y_size = 5;
			break;
		case ENTITY_NPC:
		default:
			entry.x_size = entry.y_size = 0;
			break;
	}

	return entry;
}
