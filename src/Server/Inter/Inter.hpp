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

#ifndef HORIZON_INTER_H
#define HORIZON_INTER_H

#include "InterSession.hpp"

#include "Logging/Logger.hpp"
#include "Common/Server.hpp"

#include <string>
#include <Core/Database/MySqlConnection.hpp>

class InterMain : public Server
{
public:
	InterMain();
	~InterMain();

	static InterMain *getInstance()
	{
		static InterMain instance;
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

#define InterServer InterMain::getInstance()

#endif //HORIZON_INTER_H
