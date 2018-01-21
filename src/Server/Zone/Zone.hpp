/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#ifndef HORIZON_ZONE_H
#define HORIZON_ZONE_H

#include "ZoneSession.hpp"

#include "Logging/Logger.hpp"
#include "Common/Server.hpp"

#include <string>
#include <Core/Database/MySqlConnection.hpp>

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

	void PrintHeader();
	bool ReadConfig();
	void InitializeCLICommands();
private:
	struct {
		bool enabled;
	} logs;
};

#define ZoneServer ZoneMain::getInstance()

#endif //HORIZON_ZONE_H
