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

#ifndef HORIZON_ZONE_ZERO_20181114_PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM_HPP
#define HORIZON_ZONE_ZERO_20181114_PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM_HPP

#include "Server/Zone/Packets/Zero/20181114/PacketsZero20181114.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181114
{
struct PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM : public Packet
{
	PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM(uint16_t packet_id = CZ_REQ_COUNT_BARGAIN_SALE_ITEM) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 10 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181114_PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM_HPP */
