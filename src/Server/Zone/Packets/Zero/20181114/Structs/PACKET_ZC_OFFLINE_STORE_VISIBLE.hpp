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

#ifndef HORIZON_ZONE_ZERO_20181114_PACKET_ZC_OFFLINE_STORE_VISIBLE_HPP
#define HORIZON_ZONE_ZERO_20181114_PACKET_ZC_OFFLINE_STORE_VISIBLE_HPP

#include "Server/Zone/Packets/Zero/20181114/PacketsZero20181114.hpp"
#include "Server/Zone/Packets/Zero/20180822/Structs/PACKET_ZC_OFFLINE_STORE_VISIBLE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181114
{
struct PACKET_ZC_OFFLINE_STORE_VISIBLE : public Horizon::Zone::Zero20180822::PACKET_ZC_OFFLINE_STORE_VISIBLE
{
	PACKET_ZC_OFFLINE_STORE_VISIBLE(uint16_t packet_id = ZC_OFFLINE_STORE_VISIBLE) : Horizon::Zone::Zero20180822::PACKET_ZC_OFFLINE_STORE_VISIBLE(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20180822::PACKET_ZC_OFFLINE_STORE_VISIBLE::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20180822::PACKET_ZC_OFFLINE_STORE_VISIBLE::deserialize(buf);
	}

	virtual Zero20180822::PACKET_ZC_OFFLINE_STORE_VISIBLE & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 63 bytes */
	/* Changed from 59 in version 20180822 to 63 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181114_PACKET_ZC_OFFLINE_STORE_VISIBLE_HPP */
