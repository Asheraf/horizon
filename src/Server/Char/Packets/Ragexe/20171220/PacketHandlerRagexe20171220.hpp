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

#ifndef HORIZON_CHAR_RAGEXE_20171220_PACKETHANDLER_HPP
#define HORIZON_CHAR_RAGEXE_20171220_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_ACCEPT_MAKECHAR.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_SECOND_PASSWD_LOGIN.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_UPDATE_CHARINFO.hpp"
#include "Server/Char/Packets/PacketHandler.hpp"

namespace Horizon
{
namespace Models
{
	namespace Character
	{
		class Character;
	}
}
namespace Char
{
class CharSocket;

class PacketHandlerRagexe20171220 : public PacketHandler
{
public:
	PacketHandlerRagexe20171220(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRagexe20171220();

	virtual void initialize_handlers() override;

	virtual void Send_HC_ACCEPT_ENTER() override;
	virtual void Send_HC_ACCEPT_MAKECHAR(std::shared_ptr<Models::Character::Character> character) override;

};
}
}

#endif /* HORIZON_CHAR_Ragexe_20171220_PACKETHANDLER_HPP */
