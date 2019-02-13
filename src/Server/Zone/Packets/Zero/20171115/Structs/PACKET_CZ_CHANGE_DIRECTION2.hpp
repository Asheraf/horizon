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

#ifndef HORIZON_ZONE_ZERO_20171115_PACKET_CZ_CHANGE_DIRECTION2_HPP
#define HORIZON_ZONE_ZERO_20171115_PACKET_CZ_CHANGE_DIRECTION2_HPP

#include "Server/Zone/Packets/Zero/20171115/PacketsZero20171115.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171115
{
struct PACKET_CZ_CHANGE_DIRECTION2 : public Packet
{
	PACKET_CZ_CHANGE_DIRECTION2(uint16_t packet_id = CZ_CHANGE_DIRECTION2) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_CZ_CHANGE_DIRECTION2 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171115_PACKET_CZ_CHANGE_DIRECTION2_HPP */
