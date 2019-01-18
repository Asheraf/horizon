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

#ifndef HORIZON_CHAR_CHARMAIN_HPP
#define HORIZON_CHAR_CHARMAIN_HPP

#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Common/Models/Configuration/CharServerConfiguration.hpp"
#include <string>

namespace Horizon
{
namespace Char
{
class CharMain : public Server
{
public:
	CharMain();
	~CharMain();

	static CharMain *getInstance()
	{
		static CharMain instance;
		return &instance;
	}
	
	bool ReadConfig();
	void initialize_cli_commands();
	void establish_inter_connection();
	void initialize_core();

	character_server_configuration &getCharConfig() { return _char_server_config; }

	TaskScheduler &get_task_scheduler() { return _task_scheduler; }

private:
	character_server_configuration _char_server_config;
	TaskScheduler _task_scheduler;
};
}
}

#define CharServer Horizon::Char::CharMain::getInstance()

#endif //HORIZON_CHAR_CHARMAIN_HPP
