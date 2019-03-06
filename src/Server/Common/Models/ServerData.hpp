/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sxyz (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_SERVERDATA_HPP
#define HORIZON_SERVERDATA_HPP

#include <string>
#include "Horizon.hpp"

enum character_server_type : uint16_t
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
	int id{0};
	std::string name{"Horizon"};
	std::string ip_address{"127.0.0.1"};
	uint16_t port{0};
	int user_count{0};
	character_server_type server_type{CHAR_SERVER_TYPE_NORMAL};
	uint16_t is_new{0};
};

#endif //HORIZON_SERVERDATA_HPP
