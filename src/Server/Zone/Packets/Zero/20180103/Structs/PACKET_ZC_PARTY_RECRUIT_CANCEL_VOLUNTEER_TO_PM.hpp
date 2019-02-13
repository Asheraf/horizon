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

#ifndef HORIZON_ZONE_ZERO_20180103_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP
#define HORIZON_ZONE_ZERO_20180103_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP

#include "Server/Zone/Packets/Zero/20180103/PacketsZero20180103.hpp"
#include "Server/Zone/Packets/Zero/20171121/Structs/PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180103
{
struct PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM : public Horizon::Zone::Zero20171121::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM
{
	PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(uint16_t packet_id = ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM) : Horizon::Zone::Zero20171121::PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180103_PACKET_ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM_HPP */
