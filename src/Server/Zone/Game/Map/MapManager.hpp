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

#ifndef HORIZON_ZONE_GAME_MAPMANAGER_HPP
#define HORIZON_ZONE_GAME_MAPMANAGER_HPP

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Tools/MapCache/MapCache.hpp"
#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "MapThreadContainer.hpp"

#include <boost/smart_ptr.hpp>
#include <vector>

enum mapmgr_task_schedule_group
{
	MAPMGR_TASK_MAP_UPDATE = 0
};

namespace Horizon
{
namespace Zone
{
namespace Game
{

namespace Entities
{
	class Player;
}

class Map;

class MapManager
{
public:
	MapManager() { };
	~MapManager();

	static MapManager *getInstance()
	{
		static MapManager map_mgr;
		return &map_mgr;
	}

	bool initialize();
	bool LoadMapCache();

	std::shared_ptr<Map> add_player_to_map(std::string map_name, boost::shared_ptr<Entities::Player> p);
	bool remove_player_from_map(std::string map_name, boost::shared_ptr<Entities::Player> p);

	std::shared_ptr<Map> get_map(std::string map_name) const
	{
		for (auto i = _map_containers.begin(); i != _map_containers.end(); i++) {
			std::shared_ptr<Map> map = (*i)->get_map(map_name);
			if (map) return map;
		}
		
		return nullptr;
	}

	TaskScheduler &getScheduler() { return _scheduler; }

private:
	TaskScheduler _scheduler;
	std::vector<std::shared_ptr<MapThreadContainer>> _map_containers;
};
}
}
}

#define MapMgr Horizon::Zone::Game::MapManager::getInstance()

#endif /* HORIZON_GAME_MAP_MAPMGR_HPP */
