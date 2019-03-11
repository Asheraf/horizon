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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_DELETE_CHAR3_CANCEL_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_DELETE_CHAR3_CANCEL_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_DELETE_CHAR3_CANCEL : public Packet
{
	PACKET_HC_DELETE_CHAR3_CANCEL(uint16_t packet_id = HC_DELETE_CHAR3_CANCEL) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_DELETE_CHAR3_CANCEL);
		buf << character_id;
		buf << result;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_DELETE_CHAR3_CANCEL & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 10 bytes */
	uint32_t character_id{0};
	uint32_t result{0}; // either 1 or 2.
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_DELETE_CHAR3_CANCEL_HPP */
