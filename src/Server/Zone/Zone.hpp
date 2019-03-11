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

#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Common/Models/Configuration/ZoneServerConfiguration.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

#include <string>

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
class ZoneMain : public Server
{
public:
	ZoneMain();
	~ZoneMain();

	static ZoneMain *getInstance()
	{
		static ZoneMain instance;
		return &instance;
	}

	bool ReadConfig();
	void initialize_core();
	void initialize_cli_commands();
	void update(uint32_t diff);

	zone_server_configuration &get_zone_config() { return _zone_server_config; }

	TaskScheduler &get_task_scheduler() { return _task_scheduler; }

private:
	zone_server_configuration _zone_server_config;
	TaskScheduler _task_scheduler;
};
}
}

#define ZoneServer Horizon::Zone::ZoneMain::getInstance()

#endif // HORIZON_ZONE_ZONEMAIN_HPP
