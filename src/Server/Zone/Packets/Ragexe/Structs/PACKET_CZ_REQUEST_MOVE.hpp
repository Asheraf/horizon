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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_CZ_REQUEST_MOVE_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_CZ_REQUEST_MOVE_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"
#include "Utility/Utility.hpp"

namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_CZ_REQUEST_MOVE : public Packet
{
	PACKET_CZ_REQUEST_MOVE(uint16_t packet_id = CZ_REQUEST_MOVE) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		char packed_pos[3]{0};
		buf >> packet_id;
		buf.read(packed_pos, sizeof(packed_pos));
		UnpackPosition((uint8_t *) packed_pos, &x, &y, &dir);
	}

	virtual PACKET_CZ_REQUEST_MOVE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 5 bytes */
	uint16_t x{0}, y{0};
	uint8_t dir{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_CZ_REQUEST_MOVE_HPP */
