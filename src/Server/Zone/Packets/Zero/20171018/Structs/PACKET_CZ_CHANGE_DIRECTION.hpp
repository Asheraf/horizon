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

#ifndef HORIZON_ZONE_ZERO_20171018_PACKET_CZ_CHANGE_DIRECTION_HPP
#define HORIZON_ZONE_ZERO_20171018_PACKET_CZ_CHANGE_DIRECTION_HPP

#include "Server/Zone/Packets/Zero/20171018/PacketsZero20171018.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171018
{
struct PACKET_CZ_CHANGE_DIRECTION : public Packet
{
	PACKET_CZ_CHANGE_DIRECTION(uint16_t packet_id = CZ_CHANGE_DIRECTION) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_CZ_CHANGE_DIRECTION & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 5 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171018_PACKET_CZ_CHANGE_DIRECTION_HPP */
