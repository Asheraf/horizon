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

#ifndef HORIZON_ZONE_RE_20170412_PACKET_CZ_GANGSI_RANK_HPP
#define HORIZON_ZONE_RE_20170412_PACKET_CZ_GANGSI_RANK_HPP

#include "Server/Zone/Packets/RE/20170412/PacketsRE20170412.hpp"
#include "Server/Zone/Packets/RE/20170405/Structs/PACKET_CZ_GANGSI_RANK.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170412
{
struct PACKET_CZ_GANGSI_RANK : public Horizon::Zone::RE20170405::PACKET_CZ_GANGSI_RANK
{
	PACKET_CZ_GANGSI_RANK(uint16_t packet_id = CZ_GANGSI_RANK) : Horizon::Zone::RE20170405::PACKET_CZ_GANGSI_RANK(packet_id) { }

	/* Size: 4 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170412_PACKET_CZ_GANGSI_RANK_HPP */
