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

#include "Server/Common/Definitions/Horizon.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"
#include "Server/Common/Definitions/ItemDefinitions.hpp"
#include "Server/Common/Definitions/NPCDefinitions.hpp"

#include <memory>
#include <atomic>

#ifndef SOL_EXCEPTIONS_SAFE_PROPAGATION
#define SOL_EXCEPTIONS_SAFE_PROPAGATION
#endif

#include <sol.hpp>

namespace Horizon
{
	namespace Models
	{
		class GameAccount;

		namespace Character
		{
			class Character;
		}
	}
}

namespace Horizon
{
namespace Zone
{
class ZoneSession;
class PacketHandler;
namespace Game
{
	namespace Assets
	{
		class Inventory;
	}
namespace Entities
{
class Player : public Entity, public GridObject<Player>
{
public:
	Player(uint32_t guid, std::shared_ptr<Map> map, MapCoords mcoords, std::shared_ptr<ZoneSession> session);
	~Player();

	/**
	 * Relations
	 */
	std::shared_ptr<ZoneSession> get_session() { return _session; }
	std::shared_ptr<Models::GameAccount> get_game_account() { return _game_account.lock(); }
	std::shared_ptr<Models::Character::Character> get_char_model() { return _character_model.lock(); }
	std::shared_ptr<PacketHandler> get_packet_handler() { return _packet_handler.lock(); }

	/**
	 * Item Stores
	 */
	std::shared_ptr<Assets::Inventory> get_inventory() { return _inventory; }

	uint32_t get_max_inventory_size() const { return _max_inventory_size; }
	void set_max_inventory_size(uint32_t size) { _max_inventory_size = size; }

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
	entity_viewport_entry create_viewport_entry(std::shared_ptr<Entity> entity);

	template<typename ZC_PACKET_T>
	void notify_in_area(ZC_PACKET_T &pkt, player_notifier_type type, uint16_t range = MAX_VIEW_RANGE);

	/**
	 * NPC / Script applications
	 */
	sol::state &get_lua_state() { return _lua_state; }
	uint32_t get_npc_contact_guid() { return _npc_contact_guid; }
	void set_npc_contact_guid(uint32_t guid) { _npc_contact_guid = guid; }
	void send_npc_dialog(uint32_t npc_guid, std::string dialog);
	void send_npc_next_dialog(uint32_t npc_guid);
	void send_npc_close_dialog(uint32_t npc_guid);
	void send_npc_menu_list(uint32_t npc_guid, std::string const &menu);

	/**
	 * Player applications.
	 */
	void on_map_enter();
	bool move_to_map(std::shared_ptr<Map> map, MapCoords coords = { 0, 0 });
	void update(uint32_t diff) override;
	void sync_with_models() override;

	uint64_t new_unique_id();

	bool is_logged_in() { return _is_logged_in; }
	bool set_logged_in(bool logged_in) { return _is_logged_in.exchange(logged_in); }
private:
	std::shared_ptr<ZoneSession> _session;
	std::weak_ptr<Models::GameAccount> _game_account;
	std::weak_ptr<Models::Character::Character> _character_model;
	std::weak_ptr<PacketHandler> _packet_handler;
	uint32_t _npc_contact_guid{0};
	sol::state _lua_state;
	std::shared_ptr<Assets::Inventory> _inventory;
	uint32_t _max_inventory_size{MAX_INVENTORY_SIZE};
	uint64_t _last_unique_id{0};
	std::atomic<bool> _is_logged_in{false};
};
}
}
}
}

#include "PlayerImpl.hpp"

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP */
