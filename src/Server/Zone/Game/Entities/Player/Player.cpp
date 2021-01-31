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
#include "Server/Zone/Game/Entities/Player/Assets/Inventory.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/Traits/Attributes.hpp"
#include "Server/Zone/Game/Entities/Traits/Appearance.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Zone.hpp"


using namespace Horizon::Zone;
using namespace Horizon::Zone::Entities;

Player::Player(std::shared_ptr<ZoneSession> session, uint32_t guid, std::shared_ptr<Map> map, MapCoords mcoords)
: Entity(guid, ENTITY_PLAYER, map, mcoords), _session(session)
{
}

Player::~Player()
{
	if (has_valid_grid_reference())
		remove_grid_reference();
}

uint64_t Player::new_unique_id()
{
	int32_t char_id = character()._character_id;
	
	if (character()._last_unique_id > 0)
		return ++character()._last_unique_id;

	return (character()._last_unique_id = uint64_t (char_id << 32));
}

void Player::initialize()
{
	Entity::initialize();

	// Initialize Script States.
	script_manager()->initialize_state(get_lua_state());

	// Initialize Status.
	status()->initialize_player(shared_from_this());

	// Inventory.
	_inventory = std::make_shared<Assets::Inventory>(downcast<Player>(), get_max_inventory_size());
	_inventory->sync_from_model();

	// Ensure grid for entity.
	map()->ensure_grid_for_entity(this, map_coords());
	// Update current viewport.
	update_viewport();
	// On map entry processing.
	on_map_enter();
	
	notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);
}

void Player::stop_movement()
{
	MapCoords const &coords = map_coords();
	get_session()->clif()->notify_movement_stop(guid(), coords.x(), coords.y());
}

void Player::update(uint64_t diff)
{
	Entity::update(diff);
}

void Player::sync_with_models()
{
//	uint32_t char_save_mask = 0x0;
//
//	std::shared_ptr<Status::Status> status = get_status();
//	std::shared_ptr<Models::Character::Status> csd = get_char_model()->get_status_model();
//
//	if (get_name() != get_char_model()->get_name()) {
//		get_char_model()->set_name(get_name());
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (get_gender() != get_char_model()->get_gender()) {
//		get_char_model()->set_gender((character_gender_type) get_gender());
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (_last_unique_id != get_char_model()->get_last_unique_id()) {
//		get_char_model()->set_last_unique_id(_last_unique_id);
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (get_map()->get_name() != get_char_model()->get_current_map()) {
//		get_char_model()->set_current_map(get_map()->get_name());
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (get_map_coords().x() != get_char_model()->get_current_x()) {
//		get_char_model()->set_current_x(get_map_coords().x());
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (get_map_coords().y() != get_char_model()->get_current_y()) {
//		get_char_model()->set_current_y(get_map_coords().y());
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (is_logged_in() != get_char_model()->is_online()) {
//		if (is_logged_in())
//			get_char_model()->set_online();
//		else
//			get_char_model()->set_offline();
//		char_save_mask |= CHAR_SAVE_BASE_DATA;
//	}
//
//	if (status->sync_to_model(csd) == false)
//		char_save_mask |= CHAR_SAVE_STATUS_DATA;
//
//	if (get_inventory()->sync_to_model() > 0)
//		char_save_mask |= CHAR_SAVE_INVENTORY_DATA;
//
//	if (get_char_model()->save(ZoneServer, char_save_mask) >= CHAR_SAVE_BASE_DATA) {
//		std::string saved_str;
//
//		if (char_save_mask &  CHAR_SAVE_BASE_DATA)
//			saved_str.append("basic");
//
//		if (char_save_mask & CHAR_SAVE_STATUS_DATA)
//			saved_str.append(saved_str.empty() ? "status" : ", status");
//
//		if (char_save_mask & CHAR_SAVE_INVENTORY_DATA)
//			saved_str.append(saved_str.empty() ? "inventory" : ", inventory");
//
//		HLog(info) <<"Saved {} data for character {} (AID: {}, CID: {}).", saved_str, get_char_model()->get_name(), get_guid(), get_char_model()->get_id());
//	}
}

void Player::on_movement_begin()
{
	get_session()->clif()->notify_player_movement(map_coords(), dest_coords());
}

void Player::on_movement_end()
{
}

void Player::on_movement_step()
{
	GridNPCTrigger npc_trigger(shared_from_this());
	GridReferenceContainerVisitor<GridNPCTrigger, GridReferenceContainer<AllEntityTypes>> npc_trigger_performer(npc_trigger);

	update_viewport();
	map()->ensure_grid_for_entity(this, map_coords());

	map()->visit_in_range(map_coords(), npc_trigger_performer, MAX_NPC_TRIGGER_RANGE);
}

void Player::update_viewport()
{
	GridViewPortUpdater updater(shared_from_this());
	GridReferenceContainerVisitor<GridViewPortUpdater, GridReferenceContainer<AllEntityTypes>> update_caller(updater);

	map()->visit_in_range(map_coords(), update_caller);
}

void Player::add_entity_to_viewport(std::weak_ptr<Entity> entity)
{
	if (!entity.expired()) {
		entity_viewport_entry entry = get_session()->clif()->create_viewport_entry(entity.lock());
		get_session()->clif()->notify_viewport_add_entity(entry);
	}
}

void Player::remove_entity_from_viewport(std::shared_ptr<Entity> entity, entity_viewport_notification_type type)
{
	get_session()->clif()->notify_viewport_remove_entity(entity, type);
}

void Player::realize_entity_movement(std::weak_ptr<Entity> entity)
{
	if (!entity.expired()) {
		entity_viewport_entry entry = get_session()->clif()->create_viewport_entry(entity.lock());
		get_session()->clif()->notify_viewport_moving_entity(entry);
	}
}

bool Player::move_to_map(std::shared_ptr<Map> dest_map, MapCoords coords)
{
	if (dest_map == nullptr)
		return false;

	force_movement_stop_internal(true);
	getScheduler().CancelGroup(ENTITY_SCHEDULE_WALK);

	std::shared_ptr<Player> myself = downcast<Player>();

	notify_nearby_players_of_self(EVP_NOTIFY_TELEPORT);

	{
		if (!dest_map->container()->get_map(map()->get_name())) {
			map()->container()->remove_player(myself);
			dest_map->container()->add_player(myself);
		}

		if (coords == MapCoords(0, 0))
			coords = dest_map->get_random_coords();

		dest_map->ensure_grid_for_entity(this, coords);
		set_map(dest_map);
		set_map_coords(coords);
	}

	get_session()->clif()->notify_move_to_map(dest_map->get_name(), coords.x(), coords.y());
	return true;
}

void Player::send_npc_dialog(uint32_t npc_guid, std::string dialog)
{
	get_session()->clif()->notify_npc_dialog(npc_guid, dialog);
}

void Player::send_npc_next_dialog(uint32_t npc_guid)
{
	get_session()->clif()->notify_npc_next_dialog(npc_guid);
}

void Player::send_npc_close_dialog(uint32_t npc_guid)
{
	get_session()->clif()->notify_npc_close_dialog(npc_guid);
}

void Player::send_npc_menu_list(uint32_t npc_guid, std::string const &menu)
{
	get_session()->clif()->notify_npc_menu_list(npc_guid, menu);
}

void Player::on_item_equip(std::shared_ptr<const item_entry_data> item)
{
	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(item->item_id);
	std::shared_ptr<Traits::Status> s = status();

	if (item->type == IT_TYPE_WEAPON) {
		s->status_atk()->set_weapon_type(itemd->sub_type.weapon_t);
		s->equip_atk()->on_equipment_change();
	}
}

void Player::on_item_unequip(std::shared_ptr<const item_entry_data> item)
{
	std::shared_ptr<const item_config_data> itemd = ItemDB->get_item_by_id(item->item_id);
	std::shared_ptr<Traits::Status> s = status();

	if (item->type == IT_TYPE_WEAPON) {
		s->status_atk()->set_weapon_type(IT_WT_FIST);
		s->equip_atk()->on_equipment_change();
	}
}

void Player::on_map_enter()
{
	force_movement_stop_internal(false);
//	get_packet_handler()->Send_ZC_MAPPROPERTY_R2(get_map());

	get_inventory()->notify_all();
	// Status Notifications.

	update_viewport();

	notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);
}

void Player::notify_in_area(ByteBuffer &buf, player_notifier_type type, uint16_t range)
{
	GridPlayerNotifier notifier(buf, static_cast<Entity *>(this)->shared_from_this(), type);
	GridReferenceContainerVisitor<GridPlayerNotifier, GridReferenceContainer<AllEntityTypes>> container(notifier);

	map()->visit_in_range(map_coords(), container, range);
}

