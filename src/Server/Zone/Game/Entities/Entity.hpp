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

#ifndef HORIZON_ZONE_GAME_ENTITY_HPP
#define HORIZON_ZONE_GAME_ENTITY_HPP

#include "Server/Common/Horizon.hpp"
#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"

#include <stdlib.h>
#include <memory>
#include <iostream>

enum entity_task_schedule_group
{
	ENTITY_SCHEDULE_WALK = 0
};

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Map;
class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(uint32_t guid, entity_types type);
	Entity(uint32_t guid, entity_types type, MapCoords map_coords);
	Entity(uint32_t guid, entity_types type, MapCoords map_coords, GridCoords grid_coords);
	~Entity();

	virtual void initialize();

	bool is_initialized() { return _is_initialized; }
	
	uint32_t get_guid() const { return _guid; }
	void set_guid(uint32_t guid) { _guid = guid; }

	entity_types get_type() const { return _type; }
	void set_type(entity_types type) { _type = type; }

	std::shared_ptr<Map> get_map() { return _map.expired() ? nullptr : _map.lock(); }
	void set_map(std::shared_ptr<Map> map) { _map = map; }

	/* Map Coords */
	MapCoords const &get_map_coords() const { return _map_coords; }
	void set_map_coords(MapCoords const &coords) { _map_coords = coords; }

	/* Grid Coords */
	GridCoords const &get_grid_coords() const { return _grid_coords; }
	void set_grid_coords(GridCoords const &coords) { _grid_coords = coords; }

	/* Update */
	virtual void update(uint32_t diff);

	/* Scheduler */
	TaskScheduler &getScheduler() { return _scheduler; }

	bool is_in_range_of(std::shared_ptr<Entity> entity, uint8_t range = MAX_VIEW_RANGE);

	std::shared_ptr<Entity> get_nearby_entity(uint32_t guid);

	virtual void notify_nearby_players_of_self(entity_viewport_notification_type notif_type);
	
private:
	bool _is_initialized{false};
	uint32_t _guid{0};
	entity_types _type{ENTITY_UNKNOWN};
	MapCoords _map_coords{0, 0};
	GridCoords _grid_coords{0, 0};
	TaskScheduler _scheduler;
	std::weak_ptr<Map> _map;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITY_HPP */
