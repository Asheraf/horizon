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

#ifndef HORIZON_CHAR_CHARMAIN_H
#define HORIZON_CHAR_CHARMAIN_H

#include "CharSession.hpp"

#include "Logging/Logger.hpp"
#include "Common/Server.hpp"

#include <string>
#include <Core/Database/MySqlConnection.hpp>

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

	void PrintHeader();
	bool ReadConfig();
	void InitializeCLICommands();
	void ConnectWithInterServer();
	void InitializeCore();
private:
	struct {
		bool enabled;
	} logs;
};
}
}

#define CharServer Horizon::Char::CharMain::getInstance()

#endif //HORIZON_CHAR_CHARMAIN_H
