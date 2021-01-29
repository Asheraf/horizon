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

#ifndef HORIZON_ZONECLIENTINTERFACE_HPP
#define HORIZON_ZONECLIENTINTERFACE_HPP

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Interfaces/ClientInterface.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include "Server/Zone/Packets/TransmittedPackets.hpp"

namespace Horizon
{
namespace Zone
{
namespace Entities
{
namespace Traits
{
	class Status;
}
}
class Entity;
class ZoneSession;
class ZoneClientInterface : public ClientInterface<ZoneSession>
{
public:
	ZoneClientInterface(std::shared_ptr<ZoneSession> s);
	~ZoneClientInterface();
	
	bool login(uint32_t account_id, uint32_t char_id, uint32_t auth_code, uint32_t client_time, uint8_t gender);
	bool restart(uint8_t type);
	bool disconnect(uint8_t type);
	
	bool walk_to_coordinates(uint16_t x, uint16_t y, uint8_t dir);
	
	bool notify_time();
	bool notify_entity_name(uint32_t guid);
	
	/* NPC */
	uint32_t get_npc_contact_guid() { return _npc_contact_guid; }
	void set_npc_contact_guid(uint32_t guid) { _npc_contact_guid = guid; }
	
	/* Movement */
	bool notify_player_movement(MapCoords from, MapCoords to);
	bool notify_stop_movement(int32_t guid, int16_t x, int16_t y);
	
	entity_viewport_entry create_viewport_entry(std::shared_ptr<Entity> entity);
	bool notify_viewport_add_entity(entity_viewport_entry entry);
	bool notify_viewport_remove_entity(std::shared_ptr<Entity> entity, entity_viewport_notification_type type);
	bool notify_movement_stop(int32_t guid, int16_t x, int16_t y);
	bool notify_viewport_moving_entity(entity_viewport_entry entry);
	
	void notify_npc_dialog(uint32_t npc_guid, std::string dialog);
	void notify_npc_next_dialog(uint32_t npc_guid);
	void notify_npc_close_dialog(uint32_t npc_guid);
	void notify_npc_menu_list(uint32_t npc_guid, std::string const &menu);
	
	/* Status */
	void notify_initial_status(std::shared_ptr<Entities::Traits::Status> status);
	bool notify_appearance_update(entity_appearance_type type, int32_t id);
	// 0x00b0
	bool notify_complex_attribute_update(status_point_type type, int32_t value);
	// 0x00bc
	bool notify_status_attribute_update(status_point_type type, int32_t value, bool success);
	// 0x00be
	bool notify_required_attribute_update(status_point_type type, int32_t value);
	// 0x0121
	bool notify_cart_weight_update();
	// 0x013a
	bool notify_attack_range_update(int32_t value);
	// 0x0acb
	bool notify_experience_update(status_point_type type, int32_t value);
	// 0x00b1
	bool notify_zeny_update();
	
	bool increase_status_point(status_point_type type, uint8_t amount);

	bool notify_move_to_map(std::string map_name, int16_t x, int16_t y);

	bool notify_chat(std::string message);

	void parse_chat_message(std::string message);
	
	void notify_map_enter();

	bool notify_map_properties(zc_map_properties properties);

protected:
	uint32_t _npc_contact_guid{0};
};
}
}

#endif /* HORIZON_ZONECLIENTINTERFACE_HPP */
