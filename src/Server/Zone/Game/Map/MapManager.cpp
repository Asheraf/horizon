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
 * Base Author - Sagun Khosla. <sagunxp@gmail.com>
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Core/Multithreading/WorkerThreadPool.hpp"
#include "Server/Zone/Zone.hpp"
#include <algorithm>

Horizon::Zone::Game::MapManager::~MapManager()
{
	auto mapdb = _map_data_db.get_map();

	for (auto m : mapdb)
		delete m.second;
}

bool Horizon::Zone::Game::MapManager::initialize()
{
	return LoadMapCache();
}

bool Horizon::Zone::Game::MapManager::LoadMapCache()
{
	Horizon::Libraries::MapCache m;

	m.setMapListPath(ZoneServer->get_zone_config().get_database_path() + "map_list.conf");
	m.setMapCachePath(ZoneServer->get_zone_config().get_database_path().append(ZoneServer->get_zone_config().get_mapcache_file_name()));

	if (m.ReadMapListConfig() != MCACHE_CONFIG_OK) {
		ZoneLog->error("Could not read map config file '{}'.", m.getMapListPath().c_str());
		return false;
	}

	switch (m.ImportFromCacheFile())
	{
		default:
			break;
		case MCACHE_IMPORT_NONEXISTENT_FILE:
			ZoneLog->error("Could not open file '{}'.", m.getMapCachePath().c_str());
			return false;
		case MCACHE_IMPORT_READ_ERROR:
			ZoneLog->error("Could not read file '{}', rebuilding...", m.getMapCachePath().c_str());
			return false;
		case MCACHE_IMPORT_INVALID_CHECKSUM:
			ZoneLog->error("File cache file '{}' is corrupted (invalid checksum), rebuilding...", m.getMapCachePath().c_str());
			return false;
		case MCACHE_IMPORT_DECOMPRESS_ERROR:
			ZoneLog->error("File cache file '{}' could not be decompressed, rebuilding...", m.getMapCachePath().c_str());
			return false;
		case MCACHE_IMPORT_MAPINFO_ERROR:
			ZoneLog->error("Could not read map information for a map while importing file '{}', rebuilding...", m.getMapCachePath().c_str());
			return false;
		case MCACHE_IMPORT_CELLINFO_ERROR:
			ZoneLog->error("Could not read cell information for a map while importing file '{}', rebuilding...", m.getMapCachePath().c_str());
			return false;
	}

	ZoneLog->debug("Initializing grids...");

	for (auto &i : m.getMCache()->maps) {
		Map *map = new Map(i.second.name(), i.second.width(), i.second.height(), i.second.getCells());
		map->ensureAllGrids();
		_map_data_db.insert(i.first, map);
		ZoneLog->info("Initialized grid for map '{}'", i.second.name());
	}

	ZoneLog->info("Done initializing '{}' maps.", _map_data_db.size());
	
	return true;
}

void Horizon::Zone::Game::MapManager::update(uint32_t diff)
{
	auto mapdb = _map_data_db.get_map();

#define MAX_THREADS 8
	WorkerThreadPool pool;
	std::future<typename std::result_of<std::function<void()>()>::type> fut[MAX_THREADS];

	for (auto it = mapdb.begin(); it != mapdb.end();) {
		for (int i = 0; i < MAX_THREADS && it != mapdb.end(); i++, std::advance(it, 1))
			fut[i] = pool.submit([it, diff] () { it->second->update(diff); });

		for (int i = 0; i < MAX_THREADS; i++)
			fut[i].wait();
	}

	_scheduler.Update(diff);
#undef MAX_THREADS
}
