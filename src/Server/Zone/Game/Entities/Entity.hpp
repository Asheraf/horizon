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

#ifndef HORIZON_ZONE_GAME_ENTITY_HPP
#define HORIZON_ZONE_GAME_ENTITY_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Map/MapContainerThread.hpp"
#include "Server/Zone/Game/Map/Script/ScriptManager.hpp"

#include <stdlib.h>
#include <memory>
#include <iostream>

enum entity_task_schedule_group
{
	ENTITY_SCHEDULE_WALK = 1,
	ENTITY_SCHEDULE_SAVE = 2,
};

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
class Map;
class Entity : public std::enable_shared_from_this<Entity>
{
public:
	Entity(uint32_t guid, entity_type type, std::shared_ptr<Map> map, MapCoords map_coords);
	~Entity();

	virtual void initialize();

	bool is_initialized() { return _is_initialized; }

	/**
	 * Movement
	 */
	MapCoords const &dest_coords() const { return _dest_pos; }
	virtual bool move_to_coordinates(uint16_t x, uint16_t y);
	bool is_walking() { return (dest_coords() != MapCoords(0, 0)); }

protected:
	bool schedule_movement(MapCoords mcoords);
	void move();
	virtual void stop_movement() = 0;
	virtual void on_movement_begin() = 0;
	virtual void on_movement_step() = 0;
	virtual void on_movement_end() = 0;
	virtual void sync_with_models() = 0;

	/**
	 * Unit Data
	 */
public:
	uint32_t guid() const { return _guid; }
	void set_guid(uint32_t guid) { _guid = guid; }

	uint16_t job_id() const { return _job_id; }
	void set_job_id(uint16_t job_id) { _job_id = job_id; }

	entity_posture_type posture() const { return _posture; }
	void set_posture(entity_posture_type posture) { _posture = posture; }

	const std::string &name() const { return _name; }
	void set_name(const std::string &name) { _name = name; }

	directions direction() const { return _facing_dir; }
	void set_direction(directions dir) { _facing_dir = dir; }

	std::shared_ptr<Entities::Traits::Status> status() { return _status; }
	void set_status(std::shared_ptr<Entities::Traits::Status> st) { _status = st; }

	void force_movement_stop(bool stop = false) { _instep_movement_stop = stop; }
	/**
	 * Map & Map Container
	 */
	std::shared_ptr<Map> map() { return _map.expired() ? nullptr : _map.lock(); }
	void set_map(std::shared_ptr<Map> map)
	{
		_map = map;
		_map_container_thread = map->container();
		_script_manager = map->container()->get_script_manager();
	}

	std::shared_ptr<MapContainerThread> map_container() { return _map_container_thread.lock(); }
	std::shared_ptr<ScriptManager> script_manager() { return _script_manager.lock(); }

	/**
	 * Entity applications
	 */
	virtual void update(uint64_t diff);
	TaskScheduler &getScheduler() { return _scheduler; }

	entity_type type() const { return _type; }

	template <class T>
	std::shared_ptr<T> downcast()
	{
		return std::dynamic_pointer_cast<T>(shared_from_this());
	}

	/**
	 * Grid applications.
	 */
	MapCoords const &map_coords() const { return _map_coords; }
	void set_map_coords(MapCoords const &coords) { _map_coords = coords; }

	GridCoords const &grid_coords() const { return _grid_coords; }
	void set_grid_coords(GridCoords const &coords) { _grid_coords = coords; }

	bool is_in_range_of(std::shared_ptr<Entity> entity, uint8_t range = MAX_VIEW_RANGE);
	virtual void notify_nearby_players_of_self(entity_viewport_notification_type notif_type);
	std::shared_ptr<Entity> get_nearby_entity(uint32_t guid);

private:
	bool _is_initialized{false}, _instep_movement_stop{false};
	uint32_t _guid{0};
	entity_type _type{ENTITY_UNKNOWN};
	std::weak_ptr<Map> _map;
	MapCoords _map_coords{0, 0};
	GridCoords _grid_coords{0, 0};
	TaskScheduler _scheduler;

	/* Simplified References */
	std::weak_ptr<MapContainerThread> _map_container_thread;
	std::weak_ptr<ScriptManager> _script_manager;

	MapCoords _changed_dest_pos{0, 0}, _dest_pos{0, 0};
	AStar::CoordinateList _walk_path;

	std::shared_ptr<Entities::Traits::Status> _status;

	// General Data
	std::string _name{""};
	uint16_t _job_id{0};
	entity_posture_type _posture{POSTURE_STANDING};
	directions _facing_dir{DIR_SOUTH};
};
}
}

#endif /* HORIZON_ZONE_GAME_ENTITY_HPP */
