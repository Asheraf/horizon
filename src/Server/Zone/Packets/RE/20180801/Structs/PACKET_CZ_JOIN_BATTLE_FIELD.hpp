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

#ifndef HORIZON_ZONE_RE_20180801_PACKET_CZ_JOIN_BATTLE_FIELD_HPP
#define HORIZON_ZONE_RE_20180801_PACKET_CZ_JOIN_BATTLE_FIELD_HPP

#include "Server/Zone/Packets/RE/20180801/PacketsRE20180801.hpp"
#include "Server/Zone/Packets/RE/20180718/Structs/PACKET_CZ_JOIN_BATTLE_FIELD.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20180801
{
struct PACKET_CZ_JOIN_BATTLE_FIELD : public Horizon::Zone::RE20180718::PACKET_CZ_JOIN_BATTLE_FIELD
{
	PACKET_CZ_JOIN_BATTLE_FIELD(uint16_t packet_id = CZ_JOIN_BATTLE_FIELD) : Horizon::Zone::RE20180718::PACKET_CZ_JOIN_BATTLE_FIELD(packet_id) { }

	/* Size: 8 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20180801_PACKET_CZ_JOIN_BATTLE_FIELD_HPP */
