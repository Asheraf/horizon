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

#ifndef HORIZON_ZONE_RE_20181205_PACKET_CZ_COMMAND_MER_HPP
#define HORIZON_ZONE_RE_20181205_PACKET_CZ_COMMAND_MER_HPP

#include "Server/Zone/Packets/RE/20181205/PacketsRE20181205.hpp"
#include "Server/Zone/Packets/RE/20181128/Structs/PACKET_CZ_COMMAND_MER.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20181205
{
struct PACKET_CZ_COMMAND_MER : public Horizon::Zone::RE20181128::PACKET_CZ_COMMAND_MER
{
	PACKET_CZ_COMMAND_MER(uint16_t packet_id = CZ_COMMAND_MER) : Horizon::Zone::RE20181128::PACKET_CZ_COMMAND_MER(packet_id) { }

	/* Size: 5 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20181205_PACKET_CZ_COMMAND_MER_HPP */
