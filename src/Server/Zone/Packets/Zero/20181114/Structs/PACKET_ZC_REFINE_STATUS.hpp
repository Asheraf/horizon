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

#ifndef HORIZON_ZONE_ZERO_20181114_PACKET_ZC_REFINE_STATUS_HPP
#define HORIZON_ZONE_ZERO_20181114_PACKET_ZC_REFINE_STATUS_HPP

#include "Server/Zone/Packets/Zero/20181114/PacketsZero20181114.hpp"
#include "Server/Zone/Packets/Zero/Structs/PACKET_ZC_REFINE_STATUS.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181114
{
struct PACKET_ZC_REFINE_STATUS : public Horizon::Zone::Zero::PACKET_ZC_REFINE_STATUS
{
	PACKET_ZC_REFINE_STATUS(uint16_t packet_id = ZC_REFINE_STATUS) : Horizon::Zone::Zero::PACKET_ZC_REFINE_STATUS(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero::PACKET_ZC_REFINE_STATUS::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero::PACKET_ZC_REFINE_STATUS::deserialize(buf);
	}

	virtual Zero::PACKET_ZC_REFINE_STATUS & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 32 bytes */
	/* Changed from 30 in version 0 to 32 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181114_PACKET_ZC_REFINE_STATUS_HPP */
