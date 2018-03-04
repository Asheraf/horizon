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

#include "Core/Database/MySqlConnection.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Common/Models/Configuration/ZoneServerConfiguration.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Zone/Session/Session.hpp"

#include <string>

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
	void initializeCore();
	void initializeCLICommands();
	void connectWithInterServer();

	zone_server_configuration &getZoneConfig() { return _zone_server_config; }

private:
	zone_server_configuration _zone_server_config;
};
}
}

#define ZoneServer Horizon::Zone::ZoneMain::getInstance()

#endif // HORIZON_ZONE_ZONEMAIN_HPP
