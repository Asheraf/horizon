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

#ifndef HORIZON_ZONE_ZERO_20181128_PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX_HPP
#define HORIZON_ZONE_ZERO_20181128_PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX_HPP

#include "Server/Zone/Packets/Zero/20181128/PacketsZero20181128.hpp"
#include "Server/Zone/Packets/Zero/20181120/Structs/PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20181128
{
struct PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX : public Horizon::Zone::Zero20181120::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX
{
	PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX(uint16_t packet_id = CZ_USE_SKILL_TOGROUND_WITHTALKBOX) : Horizon::Zone::Zero20181120::PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX(packet_id) { }

	/* Size: 90 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20181128_PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX_HPP */
