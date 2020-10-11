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

#ifndef HORIZON_CHAR_CHARMAIN_HPP
#define HORIZON_CHAR_CHARMAIN_HPP

#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Common/Configuration/CharServerConfiguration.hpp"
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

	void initialize_core();

	character_server_configuration &get_char_config() { return _char_server_config; }

	TaskScheduler &get_task_scheduler() { return _task_scheduler; }

private:
	character_server_configuration _char_server_config;
	TaskScheduler _task_scheduler;
};
}
}

#define CharServer Horizon::Char::CharMain::getInstance()

#endif //HORIZON_CHAR_CHARMAIN_HPP
