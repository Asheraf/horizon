/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_AUTH_MAIN_HPP
#define HORIZON_AUTH_MAIN_HPP

#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"
#include "Common/Server.hpp"
#include "Common/Models/Configuration/AuthServerConfiguration.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"

#include <string>
#include <Server/Common/Models/ServerData.hpp>

typedef std::unordered_map<int, std::shared_ptr<character_server_data>> CharacterServerMapType;
namespace Horizon
{
namespace Auth
{
/**
 * Main Auth Server Singleton Class.
 */
class AuthMain : public Server
{
public:
	AuthMain();
	~AuthMain();

	static AuthMain *getInstance()
	{
		static AuthMain instance;
		return &instance;
	}

	bool ReadConfig();

	/* Auth Server Configuration */
	struct auth_server_config &get_auth_config() { return _auth_config; }

	void initialize_core();
	/* CLI */
	void initialize_cli_commands();
	bool clicmd_reload_config();

	/* Character Server Handlers */
	void add_character_server(struct character_server_data &serv)
	{
		_character_servers.insert(std::make_pair(serv.id, std::make_shared<character_server_data>(serv)));
	}
	std::shared_ptr<character_server_data> get_character_server(int id)
	{
		auto it = _character_servers.find(id);

		if (it != _character_servers.end())
			return it->second;
		else
			return nullptr;
	}
	std::size_t character_server_count() { return _character_servers.size(); }
	const CharacterServerMapType &get_character_servers() const { return _character_servers; }

	/* Task Scheduler */
	TaskScheduler &get_task_scheduler() { return _task_scheduler; }

protected:
	/* Auth Server Configuration */
	struct auth_server_config _auth_config;
	CharacterServerMapType _character_servers;
	TaskScheduler _task_scheduler;
};
}
}

#define AuthServer Horizon::Auth::AuthMain::getInstance()


#endif /* HORIZON_AUTH_MAIN_HPP */
