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

#ifndef HORIZON_ZONE_ZERO_20180425_PACKET_ZC_AUTOSPELLLIST_HPP
#define HORIZON_ZONE_ZERO_20180425_PACKET_ZC_AUTOSPELLLIST_HPP

#include "Server/Zone/Packets/Zero/20180425/PacketsZero20180425.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180425
{
struct PACKET_ZC_AUTOSPELLLIST : public Packet
{
	PACKET_ZC_AUTOSPELLLIST(uint16_t packet_id = ZC_AUTOSPELLLIST) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_AUTOSPELLLIST & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180425_PACKET_ZC_AUTOSPELLLIST_HPP */
