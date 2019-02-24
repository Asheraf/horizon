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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_MAKECHAR_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_MAKECHAR_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_ACCEPT_MAKECHAR : public Packet
{
	PACKET_HC_ACCEPT_MAKECHAR(uint16_t packet_id = HC_ACCEPT_MAKECHAR) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);
		character.serialize(buf);
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_ACCEPT_MAKECHAR & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 108 bytes */
	PACKET_HC_ACCEPT_ENTER::character_list_data character;
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_ACCEPT_MAKECHAR_HPP */
