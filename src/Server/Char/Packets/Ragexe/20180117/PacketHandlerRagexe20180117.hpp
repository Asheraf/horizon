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

#ifndef HORIZON_CHAR_RAGEXE_20180117_PACKETHANDLER_HPP
#define HORIZON_CHAR_RAGEXE_20180117_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/Ragexe/20180117/Structs/PACKET_HC_SECOND_PASSWD_LOGIN.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketHandlerRagexe20180103.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRagexe20180117 : public PacketHandlerRagexe20180103
{
public:
	PacketHandlerRagexe20180117(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRagexe20180117();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_Ragexe_20180117_PACKETHANDLER_HPP */
