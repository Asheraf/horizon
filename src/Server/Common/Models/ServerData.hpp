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

#ifndef HORIZON_CHARACTERSERVER_HPP
#define HORIZON_CHARACTERSERVER_HPP

#include <string>
#include "Horizon.hpp"

enum character_server_types : uint16_t
{
	CHAR_SERVER_TYPE_NORMAL,
	CHAR_SERVER_TYPE_MAINTENANCE,
	CHAR_SERVER_TYPE_OVER18,
	CHAR_SERVER_TYPE_PAYING,
	CHAR_SERVER_TYPE_FREE2PLAY,
	CHAR_SERVER_TYPE_MAX,
};

struct character_server_data
{
	int id;
	std::string name;
	std::string ip_address;
	uint16_t port;
	int user_count;
	character_server_types server_type;
	uint16_t isNew;
};

#endif //HORIZON_CHARACTERSERVER_HPP
