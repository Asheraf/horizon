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

#ifndef HORIZON_ZONE_ZERO_20171115_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP
#define HORIZON_ZONE_ZERO_20171115_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP

#include "Server/Zone/Packets/Zero/20171115/PacketsZero20171115.hpp"
#include "Server/Zone/Packets/Zero/20171018/Structs/PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171115
{
struct PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM : public Horizon::Zone::Zero20171018::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM
{
	PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(uint16_t packet_id = ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM) : Horizon::Zone::Zero20171018::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171018::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171018::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM::deserialize(buf);
	}

	virtual Zero20171018::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 5 bytes */
	/* Changed from 2 in version 20171018 to 5 */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171115_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP */
