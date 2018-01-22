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

#ifndef HORIZON_AUTH_HPP
#define HORIZON_AUTH_HPP

#include "AuthSession.hpp"

#include "Core/Database/MySqlConnection.hpp"
#include "Common/Server.hpp"
#include "Common/Models/Configuration/AuthServerConfiguration.hpp"

#include <string>
#include <Server/Common/Models/ServerData.hpp>

typedef std::unordered_map<uint32_t, std::shared_ptr<AuthSession>> OnlineListType;

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
	/* Account Online List */
	void addOnlineAccount(uint32_t id, std::shared_ptr<AuthSession> session) { account_online_list.insert(std::make_pair(id, session)); }
	std::shared_ptr<AuthSession> getOnlineAccount(uint32_t id)
	{
		auto it = account_online_list.find(id);
		if (it != account_online_list.end())
			return it->second;
		else
			return nullptr;
	}
	void removeOnlineAccount(uint32_t id) { account_online_list.erase(id); }

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
	/**
	 * List of accounts that are connected.
	 */
	OnlineListType account_online_list;
	std::unordered_map<int, std::shared_ptr<character_server_data>> character_servers;
};

#define AuthServer AuthMain::getInstance()

#endif /* HORIZON_AUTH_HPP */
