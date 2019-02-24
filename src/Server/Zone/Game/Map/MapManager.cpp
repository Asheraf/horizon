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
 * Base Author - Sagun Khosla. <sagunxp@gmail.com>
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

#include "MapManager.hpp"
#include "MapThreadContainer.hpp"

#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Core/Multithreading/WorkerThreadPool.hpp"
#include "Server/Zone/Zone.hpp"

#include <algorithm>

using namespace Horizon::Zone::Game;

MapManager::~MapManager()
{
	
}

bool MapManager::initialize()
{
	return LoadMapCache();
}

bool MapManager::LoadMapCache()
{
	Horizon::Libraries::MapCache m;
	std::string db_path = ZoneServer->get_zone_config().get_database_path();

	m.setMapListPath(db_path + "map_list.lua");
	m.setMapCachePath(db_path + ZoneServer->get_zone_config().get_mapcache_file_name());

	if (m.ReadMapListConfig() != MCACHE_CONFIG_OK) {
		ZoneLog->error("Could not read map config file '{}'.", m.getMapListPath().string());
		return false;
	}

	switch (m.ImportFromCacheFile())
	{
		default:
			break;
		case MCACHE_IMPORT_NONEXISTENT_FILE:
			ZoneLog->error("Could not open file '{}'.", m.getMapCachePath().string());
			return false;
		case MCACHE_IMPORT_READ_ERROR:
			ZoneLog->error("Could not read file '{}', rebuilding...", m.getMapCachePath().string());
			return false;
		case MCACHE_IMPORT_INVALID_CHECKSUM:
			ZoneLog->error("File cache file '{}' is corrupted (invalid checksum), rebuilding...", m.getMapCachePath().string());
			return false;
		case MCACHE_IMPORT_DECOMPRESS_ERROR:
			ZoneLog->error("File cache file '{}' could not be decompressed, rebuilding...", m.getMapCachePath().string());
			return false;
		case MCACHE_IMPORT_MAPINFO_ERROR:
			ZoneLog->error("Could not read map information for a map while importing file '{}', rebuilding...", m.getMapCachePath().string());
			return false;
		case MCACHE_IMPORT_CELLINFO_ERROR:
			ZoneLog->error("Could not read cell information for a map while importing file '{}', rebuilding...", m.getMapCachePath().string());
			return false;
	}

	int map_container_count = ZoneServer->get_zone_config().get_map_container_count();
	int container_idx = 0, map_counter = 0, total_maps = 0;
	int mcache_size = m.getMCache()->maps.size();
	int container_max = std::ceil((double) mcache_size / map_container_count);

	ZoneLog->info("Initializing {} map containers with {} maps per container for a total of {} maps...", map_container_count, container_max, mcache_size);

	for (int i = 0; i < map_container_count; i++)
		_map_containers.push_back(std::make_shared<MapThreadContainer>());

	for (auto &i : m.getMCache()->maps) {
		std::shared_ptr<Map> map = std::make_shared<Map>(_map_containers[container_idx], i.second.name(), i.second.width(), i.second.height(), i.second.getCells());
		_map_containers[container_idx]->add_map(std::move(map));
		map_counter++;
		total_maps++;

		if (container_max == map_counter || total_maps == mcache_size) {
			_map_containers[container_idx]->initialize();
			_map_containers[container_idx++]->start();
			map_counter = 0;
		}
	}

	ZoneLog->info("Done initializing '{}' maps.", total_maps);
	
	return true;
}

std::shared_ptr<Map> MapManager::add_player_to_map(std::string map_name, boost::shared_ptr<Entities::Player> p)
{
	for (auto i = _map_containers.begin(); i != _map_containers.end(); i++) {
		std::shared_ptr<Map> map = (*i)->get_map(map_name);
		if (map) {
			(*i)->add_player(map_name, p);
			return map;
		}
	}

	return nullptr;
}

bool MapManager::remove_player_from_map(std::string map_name, boost::shared_ptr<Entities::Player> p)
{
	for (auto i = _map_containers.begin(); i != _map_containers.end(); i++) {
		if ((*i)->get_map(map_name) != nullptr) {
			(*i)->remove_player(p);
			return true;
		}
	}

	return false;
}
