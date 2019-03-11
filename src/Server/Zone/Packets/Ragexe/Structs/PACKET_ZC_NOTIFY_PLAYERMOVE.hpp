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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_PLAYERMOVE_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_PLAYERMOVE_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_NOTIFY_PLAYERMOVE : public Packet
{
	PACKET_ZC_NOTIFY_PLAYERMOVE(uint16_t packet_id = ZC_NOTIFY_PLAYERMOVE) : Packet(packet_id) { }

	virtual PacketBuffer serialize(int16_t from_x, int16_t from_y, int16_t to_x, int16_t to_y)
	{
		PackPosition(packed_pos, from_x, from_y, to_x, to_y, 8, 8);

		PacketBuffer buf(packet_id);
		timestamp = get_sys_time();
		buf << timestamp;
		buf.append((char *) packed_pos, sizeof(packed_pos));
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_NOTIFY_PLAYERMOVE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	/* Size: 12 bytes */
	unsigned int timestamp{0};
	int8_t packed_pos[6]{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_PLAYERMOVE_HPP */
