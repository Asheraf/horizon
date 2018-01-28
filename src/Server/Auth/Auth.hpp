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

#ifndef HORIZON_AUTH_MAIN_HPP
#define HORIZON_AUTH_MAIN_HPP

#include "AuthSession.hpp"

#include "Core/Database/MySqlConnection.hpp"
#include "Common/Server.hpp"
#include "Common/Models/Configuration/AuthServerConfiguration.hpp"

#include <string>
#include <Server/Common/Models/ServerData.hpp>

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

	void PrintHeader();
	bool ReadConfig();

	/* Auth Server Configuration */
	struct auth_server_config &getAuthConfig() { return auth_config; }

	void ConnectWithInterServer();

	void InitializeCore();
	/* CLI */
	void InitializeCLICommands();
	bool CLICmd_ReloadConfig();

	/* Character Server Handlers */
	void addCharacterServer(struct character_server_data &serv) { character_servers.insert(std::make_pair(serv.id, std::make_shared<character_server_data>(serv))); }
	std::shared_ptr<character_server_data> getCharacterServer(int id)
	{
		auto it = character_servers.find(id);

		if (it != character_servers.end())
			return it->second;
		else
			return nullptr;
	}
	std::size_t totalCharacterServers() { return character_servers.size(); }

protected:
	/* Auth Server Configuration */
	struct auth_server_config auth_config;
	std::unordered_map<int, std::shared_ptr<character_server_data>> character_servers;
};
}
}

#define AuthServer Horizon::Auth::AuthMain::getInstance()


#endif /* HORIZON_AUTH_MAIN_HPP */
