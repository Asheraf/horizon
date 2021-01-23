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

#ifndef HORIZON_ZONE_ZONEMAIN_HPP
#define HORIZON_ZONE_ZONEMAIN_HPP

#include "Core/Logging/Logger.hpp"
#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

#include <string>
#include <boost/asio/deadline_timer.hpp>

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
		}
	}
}

namespace Horizon
{
namespace Zone
{
struct s_zone_server_configuration
{
	boost::filesystem::path &get_mapcache_path() { return _mapcache_path; }
	void set_mapcache_path(boost::filesystem::path p) { _mapcache_path = p; }
	
	boost::filesystem::path &get_static_db_path() { return _static_db_path; }
	void set_static_db_path(boost::filesystem::path p) { _static_db_path = p; }
	
	boost::filesystem::path _static_db_path;
	boost::filesystem::path _mapcache_path;
};

class ZoneServer : public Server
{
public:
	ZoneServer();
	~ZoneServer();

	static ZoneServer *getInstance()
	{
		static ZoneServer instance;
		return &instance;
	}

	bool read_config();
	void initialize_core();
	void initialize_cli_commands();
	void update(uint64_t diff);

	s_zone_server_configuration &zone_config() { return _zone_server_config; }

	TaskScheduler &get_task_scheduler() { return _task_scheduler; }

private:
	s_zone_server_configuration _zone_server_config;
	TaskScheduler _task_scheduler;
	boost::asio::deadline_timer _update_timer;
};
}
}

#define sZone Horizon::Zone::ZoneServer::getInstance()

#endif // HORIZON_ZONE_ZONEMAIN_HPP
