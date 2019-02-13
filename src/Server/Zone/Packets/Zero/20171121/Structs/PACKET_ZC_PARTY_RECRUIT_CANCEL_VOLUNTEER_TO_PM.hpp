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

#ifndef HORIZON_ZONE_ZERO_20171121_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP
#define HORIZON_ZONE_ZERO_20171121_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP

#include "Server/Zone/Packets/Zero/20171121/PacketsZero20171121.hpp"
#include "Server/Zone/Packets/Zero/20171115/Structs/PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171121
{
struct PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM : public Horizon::Zone::Zero20171115::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM
{
	PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(uint16_t packet_id = ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM) : Horizon::Zone::Zero20171115::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171115::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171115::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::deserialize(buf);
	}

	virtual Zero20171115::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 2 bytes */
	/* Changed from 5 in version 20171115 to 2 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171121_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP */
