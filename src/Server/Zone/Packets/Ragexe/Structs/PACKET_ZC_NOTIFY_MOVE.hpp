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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_MOVE_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_MOVE_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_NOTIFY_MOVE : public Packet
{
	PACKET_ZC_NOTIFY_MOVE(uint16_t packet_id = ZC_NOTIFY_MOVE) : Packet(packet_id) { }

	virtual PacketBuffer serialize(int16_t from_x, int16_t from_y, int16_t to_x, int16_t to_y)
	{
		char packed_pos[6]{0};
		PacketBuffer buf(packet_id);

		buf << guid;
		PackPosition((int8_t *) packed_pos, from_x, from_y, to_x, to_y, 8, 8);
		buf.append(packed_pos, sizeof(packed_pos));
		timestamp = (uint32_t) get_sys_time();
		buf << timestamp;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_NOTIFY_MOVE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	/* Size: 16 bytes */
	uint32_t guid{0};
	uint32_t timestamp{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_MOVE_HPP */
