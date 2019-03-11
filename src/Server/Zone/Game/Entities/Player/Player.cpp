/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Status.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/Status/Attributes.hpp"
#include "Server/Zone/Game/Status/Appearance.hpp"
#include "Server/Zone/Game/Status/Status.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"


using namespace Horizon::Models::Character;
using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Zone;

Player::Player(uint32_t guid, std::shared_ptr<Map> map, MapCoords mcoords, std::shared_ptr<ZoneSession> session)
: Entity(guid, ENTITY_PLAYER, map, mcoords), _session(session),
 _character_model(session->get_char_model()), _packet_handler(session->get_packet_handler())
{
}

Player::~Player()
{
	if (has_valid_grid_reference())
		remove_grid_reference();
}

uint64_t Player::new_unique_id()
{
	if (_last_unique_id > 0)
		return ++_last_unique_id;

	uint64_t char_id = get_char_model()->get_id();

	return (_last_unique_id = (char_id << 32));
}

void Player::initialize()
{
	Entity::initialize();

	_game_account = get_session()->get_game_account();

	std::shared_ptr<Character> character = get_char_model();
	std::shared_ptr<Horizon::Models::Character::Status> status = get_char_model()->get_status_model();

	// Unit Data.
	set_guid(get_game_account()->get_id());
	set_name(character->get_name());
	set_job_id(status->get_job_id());
	set_gender(character->get_gender());
	set_direction(DIR_SOUTH);
	set_posture(POSTURE_STANDING);

	// Initialize Script States.
	get_script_manager()->initialize_state(get_lua_state());

	// Initialize Status.
	get_status()->initialize(character);

	// Inventory.
	_last_unique_id = character->get_last_unique_id();
	_inventory = std::make_shared<Assets::Inventory>(downcast<Player>(), get_max_inventory_size());
	_inventory->sync_from_model();

	// Compute sub-statuses and notify the client.
	get_status()->compute_and_notify();

	// Ensure grid for entity.
	get_map()->ensure_grid_for_entity(this, get_map_coords());
	// Update current viewport.
	update_viewport();
	// On map entry processing.
	on_map_enter();
}

void Player::stop_movement()
{
	MapCoords const &coords = get_map_coords();
	get_packet_handler()->Send_ZC_STOPMOVE(get_guid(), coords.x(), coords.y());
}

void Player::update(uint32_t diff)
{
	Entity::update(diff);
}

void Player::sync_with_models()
{
	uint32_t char_save_mask = 0x0;

	std::shared_ptr<Status::Status> status = get_status();
	std::shared_ptr<Models::Character::Status> csd = get_char_model()->get_status_model();

	if (get_name() != get_char_model()->get_name()) {
		get_char_model()->set_name(get_name());
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (get_gender() != get_char_model()->get_gender()) {
		get_char_model()->set_gender((character_gender_type) get_gender());
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (_last_unique_id != get_char_model()->get_last_unique_id()) {
		get_char_model()->set_last_unique_id(_last_unique_id);
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (get_map()->get_name() != get_char_model()->get_current_map()) {
		get_char_model()->set_current_map(get_map()->get_name());
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (get_map_coords().x() != get_char_model()->get_current_x()) {
		get_char_model()->set_current_x(get_map_coords().x());
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (get_map_coords().y() != get_char_model()->get_current_y()) {
		get_char_model()->set_current_y(get_map_coords().y());
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (is_logged_in() != get_char_model()->is_online()) {
		if (is_logged_in())
			get_char_model()->set_online();
		else
			get_char_model()->set_offline();
		char_save_mask |= CHAR_SAVE_BASE_DATA;
	}

	if (status->sync_to_model(csd) == false)
		char_save_mask |= CHAR_SAVE_STATUS_DATA;

	if (get_inventory()->sync_to_model() > 0)
		char_save_mask |= CHAR_SAVE_INVENTORY_DATA;

	if (get_char_model()->save(ZoneServer, char_save_mask) >= CHAR_SAVE_BASE_DATA) {
		std::string saved_str;

		if (char_save_mask &  CHAR_SAVE_BASE_DATA)
			saved_str.append("basic");

		if (char_save_mask & CHAR_SAVE_STATUS_DATA)
			saved_str.append(saved_str.empty() ? "status" : ", status");

		if (char_save_mask & CHAR_SAVE_INVENTORY_DATA)
			saved_str.append(saved_str.empty() ? "inventory" : ", inventory");

		ZoneLog->info("Saved {} data for character {} (AID: {}, CID: {}).", saved_str, get_char_model()->get_name(), get_guid(), get_char_model()->get_id());
	}
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
	if (!entity.expired())
		get_packet_handler()->Send_ZC_NOTIFY_STANDENTRY(create_viewport_entry(entity.lock()));
}

void Player::remove_entity_from_viewport(std::shared_ptr<Entity> entity, entity_viewport_notification_type type)
{
	get_packet_handler()->Send_ZC_NOTIFY_VANISH(entity->get_guid(), type);
}

void Player::realize_entity_movement(std::weak_ptr<Entity> entity)
{
	if (!entity.expired())
		get_packet_handler()->Send_ZC_NOTIFY_MOVEENTRY(create_viewport_entry(entity.lock()));
}

entity_viewport_entry Player::create_viewport_entry(std::shared_ptr<Entity> entity)
{
	entity_viewport_entry entry;
	std::shared_ptr<Status::Status> status = entity->get_status();

	entry.guid = entity->get_guid();
	entry.unit_type = entity->get_type();
	entry.speed = status->get_movement_speed()->total();
	entry.body_state = 0;
	entry.health_state = 0;
	entry.effect_state = 0;
	entry.job_id = entity->get_job_id();
	entry.hair_style_id = status->get_hair_style()->get();
	entry.hair_color_id = status->get_hair_color()->get();
	entry.robe_id = status->get_robe_sprite()->get();
	entry.guild_id = 0;
	entry.guild_emblem_version = 0;
	entry.honor = 0;
	entry.virtue = 0;
	entry.in_pk_mode = 0;
	entry.gender = entity->get_gender();
	entry.current_x = entity->get_map_coords().x();
	entry.current_y = entity->get_map_coords().y();
	entry.current_dir = entity->get_direction();

	if (entity->is_walking()) {
		entry.to_x = entity->get_dest_pos().x();
		entry.to_y = entity->get_dest_pos().y();
	}

	entry.posture = entity->get_posture();
	entry.base_level = status->get_base_level()->total();
	entry.font = 1;

	if (status->get_max_hp()->total() > 0)
		entry.max_hp = status->get_max_hp()->total();

	if (status->get_current_hp()->total() > 0)
		entry.hp = status->get_current_hp()->total();

	entry.is_boss = 0;
	entry.body_style_id = 0;
	std::strncpy(entry.name, entity->get_name().c_str(), entity->get_name().size());

	switch (entry.unit_type)
	{
		case ENTITY_PLAYER:
			entry.character_id = entity->downcast<Player>()->get_char_model()->get_id();
			entry.x_size = entry.y_size = 0;
			break;
		case ENTITY_NPC:
		default:
			entry.x_size = entry.y_size = 0;
			break;
	}

	return entry;
}


bool Player::move_to_map(std::shared_ptr<Map> map, MapCoords coords)
{
	if (map == nullptr)
		return false;

	std::shared_ptr<Player> myself = downcast<Player>();

	notify_nearby_players_of_self(EVP_NOTIFY_TELEPORT);

	{
		if (!map->get_map_container()->get_map(get_map()->get_name())) {
			get_map()->get_map_container()->remove_player(myself);
			map->get_map_container()->add_player(myself);
		}

		if (coords == MapCoords(0, 0))
			coords = map->get_random_coords();

		set_map_coords(coords);

		map->ensure_grid_for_entity(this, coords);
		set_map(map);
	}

	get_packet_handler()->Send_ZC_NPCACK_MAPMOVE(map->get_name(), coords.x(), coords.y());
	update_viewport();
	notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);

	return true;
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

void Player::on_item_equip(std::shared_ptr<const item_entry_data> item)
{
	std::shared_ptr<const item_config_data> itemd = ItemDB->get(item->item_id);
	std::shared_ptr<Status::Status> status = get_status();

	if (item->type == IT_TYPE_WEAPON) {
		status->get_status_atk()->set_weapon_type(itemd->sub_type.weapon_t);
		status->get_weapon_atk()->on_equipment_change();
	}
}

void Player::on_item_unequip(std::shared_ptr<const item_entry_data> item)
{
	std::shared_ptr<const item_config_data> itemd = ItemDB->get(item->item_id);
	std::shared_ptr<Status::Status> status = get_status();

	if (item->type == IT_TYPE_WEAPON) {
		status->get_status_atk()->set_weapon_type(IT_WT_FIST);
		status->get_weapon_atk()->on_equipment_change();
	}
}

void Player::on_map_enter()
{
	get_packet_handler()->Send_ZC_MAPPROPERTY_R2(get_map());

	get_inventory()->notify_all();
	// Status Notifications.
	get_status()->get_max_weight()->notify_update();
	get_status()->get_current_weight()->notify_update();
	get_status()->get_next_base_experience()->notify_update();
	get_status()->get_base_experience()->notify_update();
}
