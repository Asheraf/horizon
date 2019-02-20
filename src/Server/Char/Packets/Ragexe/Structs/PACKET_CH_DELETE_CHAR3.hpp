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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_CH_DELETE_CHAR3_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_CH_DELETE_CHAR3_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_CH_DELETE_CHAR3 : public Packet
{
	PACKET_CH_DELETE_CHAR3(uint16_t packet_id = CH_DELETE_CHAR3) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(CH_DELETE_CHAR3);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> character_id;
		buf.read(birthdate, sizeof(birthdate));
	}

	virtual PACKET_CH_DELETE_CHAR3 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 12 bytes */
	uint32_t character_id{0};
	char birthdate[CLIENT_BIRTHDATE_STRING_LENGTH]{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_CH_DELETE_CHAR3_HPP */
