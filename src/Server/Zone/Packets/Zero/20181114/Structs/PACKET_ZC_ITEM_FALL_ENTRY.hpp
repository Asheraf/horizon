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

#ifndef HORIZON_ZONE_ZERO_20181114_PACKET_ZC_ITEM_FALL_ENTRY_HPP
#define HORIZON_ZONE_ZERO_20181114_PACKET_ZC_ITEM_FALL_ENTRY_HPP

#include "Server/Zone/Packets/Zero/20181114/PacketsZero20181114.hpp"
#include "Server/Zone/Packets/Zero/Structs/PACKET_ZC_ITEM_FALL_ENTRY.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181114
{
struct PACKET_ZC_ITEM_FALL_ENTRY : public Horizon::Zone::Zero::PACKET_ZC_ITEM_FALL_ENTRY
{
	PACKET_ZC_ITEM_FALL_ENTRY(uint16_t packet_id = ZC_ITEM_FALL_ENTRY) : Horizon::Zone::Zero::PACKET_ZC_ITEM_FALL_ENTRY(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero::PACKET_ZC_ITEM_FALL_ENTRY::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero::PACKET_ZC_ITEM_FALL_ENTRY::deserialize(buf);
	}

	virtual Zero::PACKET_ZC_ITEM_FALL_ENTRY & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 24 bytes */
	/* Changed from 22 in version 0 to 24 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181114_PACKET_ZC_ITEM_FALL_ENTRY_HPP */
