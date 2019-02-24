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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_NPCACK_MAPMOVE_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_NPCACK_MAPMOVE_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_NPCACK_MAPMOVE : public Packet
{
	PACKET_ZC_NPCACK_MAPMOVE(uint16_t packet_id = ZC_NPCACK_MAPMOVE) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);
		buf.append(map_name, sizeof(map_name));
		buf << x << y;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_NPCACK_MAPMOVE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 22 bytes */
	char map_name[MAP_NAME_LENGTH_EXT]{0};
	uint16_t x{0};
	uint16_t y{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_NPCACK_MAPMOVE_HPP */
