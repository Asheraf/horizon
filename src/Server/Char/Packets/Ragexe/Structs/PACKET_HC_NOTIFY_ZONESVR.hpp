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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ZONESVR_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ZONESVR_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Definitions/Client.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_NOTIFY_ZONESVR : public Packet
{
	PACKET_HC_NOTIFY_ZONESVR(uint16_t packet_id = HC_NOTIFY_ZONESVR) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_NOTIFY_ZONESVR);
		buf << char_id;
		buf.append(map_name, sizeof(map_name));
		buf << ip_address;
		buf << port;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_NOTIFY_ZONESVR & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 28 bytes */
	uint32_t char_id{0};
	char map_name[MAP_NAME_LENGTH_EXT]{0};
	uint32_t ip_address{0};
	uint16_t port{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_NOTIFY_ZONESVR_HPP */
