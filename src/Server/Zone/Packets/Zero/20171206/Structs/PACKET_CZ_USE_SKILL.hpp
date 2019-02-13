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

#ifndef HORIZON_ZONE_ZERO_20171206_PACKET_CZ_USE_SKILL_HPP
#define HORIZON_ZONE_ZERO_20171206_PACKET_CZ_USE_SKILL_HPP

#include "Server/Zone/Packets/Zero/20171206/PacketsZero20171206.hpp"
#include "Server/Zone/Packets/Zero/20171204/Structs/PACKET_CZ_USE_SKILL.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171206
{
struct PACKET_CZ_USE_SKILL : public Horizon::Zone::Zero20171204::PACKET_CZ_USE_SKILL
{
	PACKET_CZ_USE_SKILL(uint16_t packet_id = CZ_USE_SKILL) : Horizon::Zone::Zero20171204::PACKET_CZ_USE_SKILL(packet_id) { }

	/* Size: 10 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171206_PACKET_CZ_USE_SKILL_HPP */
