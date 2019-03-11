/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#ifndef HORIZON_AUTH_RAGEXE_20171213_PACKETHANDLER_HPP
#define HORIZON_AUTH_RAGEXE_20171213_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/Structs/PACKET_AC_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/Structs/PACKET_AC_ACCEPT_LOGIN.hpp"
#include "Server/Auth/Packets/PacketHandler.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerRagexe20171213 : public PacketHandler
{
public:
	PacketHandlerRagexe20171213(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerRagexe20171213();

	virtual void initialize_handlers() override;

	virtual void Send_AC_ACCEPT_LOGIN() override;
};
}
}

#endif /* HORIZON_AUTH_Ragexe_20171213_PACKETHANDLER_HPP */
