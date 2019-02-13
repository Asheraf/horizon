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

#ifndef HORIZON_ZONE_RE_20180704_PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING_HPP
#define HORIZON_ZONE_RE_20180704_PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING_HPP

#include "Server/Zone/Packets/RE/20180704/PacketsRE20180704.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20180704
{
struct PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING : public Packet
{
	PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING(uint16_t packet_id = ZC_NOTIFY_BARGAIN_SALE_SELLING) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING & operator << (PacketBuffer &right)
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

#endif /* HORIZON_ZONE_RE_20180704_PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING_HPP */
