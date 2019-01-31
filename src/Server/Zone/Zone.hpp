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
using namespace Horizon::Zone::Game::Entities;

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
