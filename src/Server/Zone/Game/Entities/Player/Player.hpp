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

#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"
#include "Server/Common/Definitions/ItemDefinitions.hpp"
#include "Server/Common/Definitions/NPCDefinitions.hpp"
#include "Server/Common/SQL/Character/Character.hpp"

#include <memory>

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
class ZoneSession;
class ZoneSocket;
namespace Assets
{
	class Inventory;
}
namespace Entities
{
class Player : public Entity, public GridObject<Player>
{
	struct s_char_data {
		uint32_t _character_id{0};
		uint32_t _account_id{0};
		uint16_t _slot{0};
		bool _online{false};
		character_gender_type _gender{CHARACTER_GENDER_MALE};
		uint32_t _max_inventory_size{MAX_INVENTORY_SIZE};
		uint64_t _last_unique_id{0};
	};
	
public:
	Player(std::shared_ptr<ZoneSession> session, uint32_t guid, std::shared_ptr<Map> map, MapCoords mcoords);
	~Player();

	/**
	 * Relations
	 */
	std::shared_ptr<ZoneSession> get_session() { return _session; }

	virtual void initialize() override;

	/**
	 * Movement
	 */
	void stop_movement() override;
	void on_movement_begin() override;
	void on_movement_step() override;
	void on_movement_end() override;

	/**
	 * Equipments
	 */
	void on_item_equip(std::shared_ptr<const item_entry_data> item);
	void on_item_unequip(std::shared_ptr<const item_entry_data> item);

	/**
	 * Grid applications
	 */
	void update_viewport();
	void add_entity_to_viewport(std::weak_ptr<Entity> entity);
	void realize_entity_movement(std::weak_ptr<Entity> entity);
	void remove_entity_from_viewport(std::shared_ptr<Entity> entity, entity_viewport_notification_type type);

	void notify_in_area(ByteBuffer &buf, player_notifier_type type, uint16_t range = MAX_VIEW_RANGE);

	/**
	 * NPC / Script applications
	 */
	sol::state &get_lua_state() { return _lua_state; }

	/**
	 * Player applications.
	 */
	void on_map_enter();
	bool move_to_map(std::shared_ptr<Map> map, MapCoords coords = { 0, 0 });
	void update(uint64_t diff) override;
	void sync_with_models() override;

	uint64_t new_unique_id();

	bool is_logged_in() { return _is_logged_in; }
	bool set_logged_in(bool logged_in) { return _is_logged_in.exchange(logged_in); }

	s_char_data &character() { return _char; }
	
	/**
	 * Item Stores
	 */
	void set_last_unique_id(uint64_t last_unique_id) { character()._last_unique_id = last_unique_id; }
	uint64_t last_unique_id() { return character()._last_unique_id; }
	
	std::shared_ptr<Assets::Inventory> get_inventory() { return _inventory; }
	
	uint32_t get_max_inventory_size() { return character()._max_inventory_size; }
	void set_max_inventory_size(uint32_t size) { character()._max_inventory_size = size; }

private:
	std::shared_ptr<ZoneSession> _session;
	sol::state _lua_state;
	std::shared_ptr<Assets::Inventory> _inventory;
	std::atomic<bool> _is_logged_in{false};
	
	s_char_data _char;
};
}
}
}

#include "PlayerImpl.hpp"

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP */
