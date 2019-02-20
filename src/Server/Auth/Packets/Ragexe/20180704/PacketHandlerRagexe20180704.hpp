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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
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

#ifndef HORIZON_AUTH_RAGEXE_20180704_PACKETHANDLER_HPP
#define HORIZON_AUTH_RAGEXE_20180704_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/Structs/PACKET_AC_REFUSE_LOGIN4.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerRagexe20180704 : public PacketHandlerRagexe20171213
{
public:
	PacketHandlerRagexe20180704(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerRagexe20180704();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_AUTH_Ragexe_20180704_PACKETHANDLER_HPP */
