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

#ifndef HORIZON_ZONE_ZERO_20181024_PACKET_ZC_ITEM_PREVIEW_HPP
#define HORIZON_ZONE_ZERO_20181024_PACKET_ZC_ITEM_PREVIEW_HPP

#include "Server/Zone/Packets/Zero/20181024/PacketsZero20181024.hpp"
#include "Server/Zone/Packets/Zero/Structs/PACKET_ZC_ITEM_PREVIEW.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181024
{
struct PACKET_ZC_ITEM_PREVIEW : public Horizon::Zone::Zero::PACKET_ZC_ITEM_PREVIEW
{
	PACKET_ZC_ITEM_PREVIEW(uint16_t packet_id = ZC_ITEM_PREVIEW) : Horizon::Zone::Zero::PACKET_ZC_ITEM_PREVIEW(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero::PACKET_ZC_ITEM_PREVIEW::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero::PACKET_ZC_ITEM_PREVIEW::deserialize(buf);
	}

	virtual Zero::PACKET_ZC_ITEM_PREVIEW & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 40 bytes */
	/* Changed from 39 in version 0 to 40 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181024_PACKET_ZC_ITEM_PREVIEW_HPP */
