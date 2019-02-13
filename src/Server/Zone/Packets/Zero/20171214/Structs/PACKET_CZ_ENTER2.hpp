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

#ifndef HORIZON_ZONE_ZERO_20171214_PACKET_CZ_ENTER2_HPP
#define HORIZON_ZONE_ZERO_20171214_PACKET_CZ_ENTER2_HPP

#include "Server/Zone/Packets/Zero/20171214/PacketsZero20171214.hpp"
#include "Server/Zone/Packets/Zero/20171130/Structs/PACKET_CZ_ENTER2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20171214
{
struct PACKET_CZ_ENTER2 : public Horizon::Zone::Zero20171130::PACKET_CZ_ENTER2
{
	PACKET_CZ_ENTER2(uint16_t packet_id = CZ_ENTER2) : Horizon::Zone::Zero20171130::PACKET_CZ_ENTER2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20171214_PACKET_CZ_ENTER2_HPP */
