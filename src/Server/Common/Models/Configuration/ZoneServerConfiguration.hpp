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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_CHARSERVERCONFIGURATION_HPP
#define HORIZON_CHARSERVERCONFIGURATION_HPP

#include <utility>
#include <vector>
#include <string>

struct zone_server_configuration
{
	void set_database_path(std::string const &path) { _db_path = path; }
	std::string &get_database_path() { return _db_path; }

	void set_mapcache_file_name(std::string const &name) { _map_cache_file_name = name; }
	std::string &get_mapcache_file_name() { return _map_cache_file_name; }

	void set_map_container_count(uint32_t threads) { _map_container_count = threads; }
	uint32_t get_map_container_count() { return _map_container_count; }

private:
	std::string _db_path{"db/"};
	std::string _map_cache_file_name{"maps.dat"};
	uint32_t _map_container_count;
};

#endif /* HORIZON_CHARSERVERCONFIGURATION_HPP */
