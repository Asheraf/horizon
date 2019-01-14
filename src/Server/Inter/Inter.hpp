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

#ifndef HORIZON_INTER_INTERMAIN_H
#define HORIZON_INTER_INTERMAIN_H

#include "Core/Database/MySqlConnection.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Common/Server.hpp"
#include "Server/Inter/Socket/InterSocket.hpp"

#include <string>

namespace Horizon
{
namespace Inter
{
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

	void initialize_core();
	
	bool ReadConfig();
	bool CLICmd_SendAuthPacket();
	void initialize_cli_commands();
private:
	struct {
		bool enabled;
	} logs;
};
}
}

#define InterServer Horizon::Inter::InterMain::getInstance()

#endif //HORIZON_INTER_H
