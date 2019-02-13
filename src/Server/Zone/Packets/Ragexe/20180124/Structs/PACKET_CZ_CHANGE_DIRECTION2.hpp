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

#ifndef HORIZON_ZONE_RAGEXE_20180124_PACKET_CZ_CHANGE_DIRECTION2_HPP
#define HORIZON_ZONE_RAGEXE_20180124_PACKET_CZ_CHANGE_DIRECTION2_HPP

#include "Server/Zone/Packets/Ragexe/20180124/PacketsRagexe20180124.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/Structs/PACKET_CZ_CHANGE_DIRECTION2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180124
{
struct PACKET_CZ_CHANGE_DIRECTION2 : public Horizon::Zone::Ragexe20180103::PACKET_CZ_CHANGE_DIRECTION2
{
	PACKET_CZ_CHANGE_DIRECTION2(uint16_t packet_id = CZ_CHANGE_DIRECTION2) : Horizon::Zone::Ragexe20180103::PACKET_CZ_CHANGE_DIRECTION2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180124_PACKET_CZ_CHANGE_DIRECTION2_HPP */
