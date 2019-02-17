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

#ifndef HORIZON_ZONE_RAGEXE_20180314_PACKET_CZ_REQUEST_MOVE2_HPP
#define HORIZON_ZONE_RAGEXE_20180314_PACKET_CZ_REQUEST_MOVE2_HPP

#include "Server/Zone/Packets/Ragexe/20180314/PacketsRagexe20180314.hpp"
#include "Server/Zone/Packets/Ragexe/20180213/Structs/PACKET_CZ_REQUEST_MOVE2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180314
{
struct PACKET_CZ_REQUEST_MOVE2 : public Horizon::Zone::Ragexe20180213::PACKET_CZ_REQUEST_MOVE2
{
	PACKET_CZ_REQUEST_MOVE2(uint16_t packet_id = CZ_REQUEST_MOVE2) : Horizon::Zone::Ragexe20180213::PACKET_CZ_REQUEST_MOVE2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180314_PACKET_CZ_REQUEST_MOVE2_HPP */
