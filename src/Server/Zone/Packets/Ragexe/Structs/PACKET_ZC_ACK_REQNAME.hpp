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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_ACK_REQNAME_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_ACK_REQNAME_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Client.hpp"

namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_ACK_REQNAME : public Packet
{
	PACKET_ZC_ACK_REQNAME(uint16_t packet_id = ZC_ACK_REQNAME) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);

		buf << guid;
		buf.append(name, sizeof(name));

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_ACK_REQNAME & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 30 bytes */
	uint32_t guid{0};
	char name[MAX_UNIT_NAME_LENGTH]{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_ACK_REQNAME_HPP */
