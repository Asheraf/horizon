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

#ifndef HORIZON_ZONE_ZERO_20180511_PACKET_CZ_USE_SKILL2_HPP
#define HORIZON_ZONE_ZERO_20180511_PACKET_CZ_USE_SKILL2_HPP

#include "Server/Zone/Packets/Zero/20180511/PacketsZero20180511.hpp"
#include "Server/Zone/Packets/Zero/20171130/Structs/PACKET_CZ_USE_SKILL2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180511
{
struct PACKET_CZ_USE_SKILL2 : public Horizon::Zone::Zero20171130::PACKET_CZ_USE_SKILL2
{
	PACKET_CZ_USE_SKILL2(uint16_t packet_id = CZ_USE_SKILL2) : Horizon::Zone::Zero20171130::PACKET_CZ_USE_SKILL2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180511_PACKET_CZ_USE_SKILL2_HPP */
