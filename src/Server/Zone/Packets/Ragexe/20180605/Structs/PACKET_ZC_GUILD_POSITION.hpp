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

#ifndef HORIZON_ZONE_RAGEXE_20180605_PACKET_ZC_GUILD_POSITION_HPP
#define HORIZON_ZONE_RAGEXE_20180605_PACKET_ZC_GUILD_POSITION_HPP

#include "Server/Zone/Packets/Ragexe/20180605/PacketsRagexe20180605.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_GUILD_POSITION.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180605
{
struct PACKET_ZC_GUILD_POSITION : public Horizon::Zone::Ragexe::PACKET_ZC_GUILD_POSITION
{
	PACKET_ZC_GUILD_POSITION(uint16_t packet_id = ZC_GUILD_POSITION) : Horizon::Zone::Ragexe::PACKET_ZC_GUILD_POSITION(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180605_PACKET_ZC_GUILD_POSITION_HPP */
