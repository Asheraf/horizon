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

#ifndef HORIZON_ZONE_RAGEXE_20180621_PACKET_CZ_CHANGE_DIRECTION_HPP
#define HORIZON_ZONE_RAGEXE_20180621_PACKET_CZ_CHANGE_DIRECTION_HPP

#include "Server/Zone/Packets/Ragexe/20180621/PacketsRagexe20180621.hpp"
#include "Server/Zone/Packets/Ragexe/20180620/Structs/PACKET_CZ_CHANGE_DIRECTION.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180621
{
struct PACKET_CZ_CHANGE_DIRECTION : public Horizon::Zone::Ragexe20180620::PACKET_CZ_CHANGE_DIRECTION
{
	PACKET_CZ_CHANGE_DIRECTION(uint16_t packet_id = CZ_CHANGE_DIRECTION) : Horizon::Zone::Ragexe20180620::PACKET_CZ_CHANGE_DIRECTION(packet_id) { }

	/* Size: 5 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180621_PACKET_CZ_CHANGE_DIRECTION_HPP */
