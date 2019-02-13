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

#ifndef HORIZON_ZONE_RE_20170712_PACKET_CZ_CHANGE_DIRECTION_HPP
#define HORIZON_ZONE_RE_20170712_PACKET_CZ_CHANGE_DIRECTION_HPP

#include "Server/Zone/Packets/RE/20170712/PacketsRE20170712.hpp"
#include "Server/Zone/Packets/RE/20170705/Structs/PACKET_CZ_CHANGE_DIRECTION.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170712
{
struct PACKET_CZ_CHANGE_DIRECTION : public Horizon::Zone::RE20170705::PACKET_CZ_CHANGE_DIRECTION
{
	PACKET_CZ_CHANGE_DIRECTION(uint16_t packet_id = CZ_CHANGE_DIRECTION) : Horizon::Zone::RE20170705::PACKET_CZ_CHANGE_DIRECTION(packet_id) { }

	/* Size: 5 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170712_PACKET_CZ_CHANGE_DIRECTION_HPP */
