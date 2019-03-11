/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

/* This is an auto-generated file, please do not edit manually. */

#ifndef HORIZON_AUTH_PACKETS_PACKETHANDLERFACTORY_HPP
#define HORIZON_AUTH_PACKETS_PACKETHANDLERFACTORY_HPP

#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"
#include <stdint.h>
#include <memory>

namespace Horizon
{
namespace Auth
{
class AuthSocket;
class PacketHandler;
class PacketHandlerFactory
{
public:
	PacketHandlerFactory();
	~PacketHandlerFactory();
	/**
	 * @brief Build a PacketHandler instance for a client (player) connection.
	 * @param[in|out] session    shared_ptr to a Session instance.
	 * @return shared pointer to a new instance of Horizon::Auth::PacketHandler.
	 */
	static std::shared_ptr<PacketHandler> create_packet_handler(std::shared_ptr<AuthSocket> socket, client_type client_type, uint32_t packet_ver);
};
}
}
#endif /* HORIZON_AUTH_PACKETS_PACKETHANDLERFACTORY_HPP*/
