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

	bool is_in_range_of(std::shared_ptr<Entity> entity, uint8_t range);

	std::shared_ptr<Entity> get_nearby_entity(uint32_t guid);
	
private:
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
