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

#ifndef HORIZON_CHAR_H
#define HORIZON_CHAR_H

#include "CharSession.hpp"

#include "Logging/Logger.hpp"
#include "Server/Server.hpp"

#include <string>
#include <Core/Database/MySqlConnection.hpp>

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
private:
	struct {
		bool enabled;
	} logs;
};

#define CharServer CharMain::getInstance()

#endif //HORIZON_CHAR_H
