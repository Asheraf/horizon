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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_AC_REFUSE_LOGIN_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_AC_REFUSE_LOGIN_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_AC_REFUSE_LOGIN : public Packet
{
	PACKET_AC_REFUSE_LOGIN(uint16_t packet_id = AC_REFUSE_LOGIN) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(AC_REFUSE_LOGIN);

		buf << error_code;
		buf.append(block_date, sizeof(block_date));

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_AC_REFUSE_LOGIN & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 23 bytes */
	uint8_t error_code{0};       ///< Error code
	char block_date[20]{0};    ///< Ban expiration date
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_AC_REFUSE_LOGIN_HPP */
