/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_MAPMANAGER_HPP
#define HORIZON_ZONE_GAME_MAPMANAGER_HPP

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Tools/MapCache/MapCache.hpp"
#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"

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

	Map *getMap(std::string const &map) { return _map_data_db.at(map); }

	void update(uint32_t diff);

	TaskScheduler &getScheduler() { return _scheduler; }

private:
	LockedLookupTable<std::string, Map *> _map_data_db;
	TaskScheduler _scheduler;
};
}
}
}

#define MapMgr Horizon::Zone::Game::MapManager::getInstance()

#endif /* HORIZON_GAME_MAP_MAPMGR_HPP */
