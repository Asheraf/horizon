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

#include "Core/Database/MySqlConnection.hpp"
#include "Common/Server.hpp"
#include "Common/Models/Configuration/AuthServerConfiguration.hpp"
#include "Server/Auth/Session/Session.hpp"

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
	struct auth_server_config &getAuthConfig() { return _auth_config; }

	void connectWithInterServer();
	void connectionKeepAliveLoop();

	void initializeCore();
	/* CLI */
	void initializeCLICommands();
	bool CLICmd_ReloadConfig();

	void UpdateCharServLoop();
	void UpdateSessionLoop();

	/* Character Server Handlers */
	void addCharacterServer(struct character_server_data &serv)
	{
		_character_servers.insert(std::make_pair(serv.id, std::make_shared<character_server_data>(serv)));
	}

	std::shared_ptr<character_server_data> getCharacterServer(int id)
	{
		auto it = _character_servers.find(id);

		if (it != _character_servers.end())
			return it->second;
		else
			return nullptr;
	}
	std::size_t totalCharacterServers() { return _character_servers.size(); }

	const CharacterServerMapType &getCharacterServers() const { return _character_servers; }

protected:
	/* Auth Server Configuration */
	struct auth_server_config _auth_config;
	CharacterServerMapType _character_servers;
};
}
}

#define AuthServer Horizon::Auth::AuthMain::getInstance()


#endif /* HORIZON_AUTH_MAIN_HPP */
