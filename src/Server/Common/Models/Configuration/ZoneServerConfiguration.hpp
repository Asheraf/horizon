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

#ifndef HORIZON_CHARSERVERCONFIGURATION_HPP
#define HORIZON_CHARSERVERCONFIGURATION_HPP

#include <utility>
#include <vector>
#include <string>

struct zone_server_configuration
{
	void setDatabasePath(std::string const &path) { _db_path = path; }
	std::string &getDatabasePath() { return _db_path; }

	void setMapCacheFileName(std::string const &name) { _map_cache_file_name = name; }
	std::string &getMapCacheFileName() { return _map_cache_file_name; }

private:
	std::string _db_path{"../db/"};
	std::string _map_cache_file_name{"maps.dat"};
};

#endif /* HORIZON_CHARSERVERCONFIGURATION_HPP */
