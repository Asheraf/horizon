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

#ifndef HORIZON_ZONE_RAGEXE_20170920_PACKET_ZC_OVERWEIGHT_PERCENT_HPP
#define HORIZON_ZONE_RAGEXE_20170920_PACKET_ZC_OVERWEIGHT_PERCENT_HPP

#include "Server/Zone/Packets/Ragexe/20170920/PacketsRagexe20170920.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170920
{
struct PACKET_ZC_OVERWEIGHT_PERCENT : public Packet
{
	PACKET_ZC_OVERWEIGHT_PERCENT(uint16_t packet_id = ZC_OVERWEIGHT_PERCENT) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_OVERWEIGHT_PERCENT & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 6 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170920_PACKET_ZC_OVERWEIGHT_PERCENT_HPP */
