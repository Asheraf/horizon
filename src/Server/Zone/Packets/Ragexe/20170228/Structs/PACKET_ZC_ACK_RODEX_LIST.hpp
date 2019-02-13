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

#ifndef HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_ACK_RODEX_LIST_HPP
#define HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_ACK_RODEX_LIST_HPP

#include "Server/Zone/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_ACK_RODEX_LIST.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170228
{
struct PACKET_ZC_ACK_RODEX_LIST : public Horizon::Zone::Ragexe::PACKET_ZC_ACK_RODEX_LIST
{
	PACKET_ZC_ACK_RODEX_LIST(uint16_t packet_id = ZC_ACK_RODEX_LIST) : Horizon::Zone::Ragexe::PACKET_ZC_ACK_RODEX_LIST(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170228_PACKET_ZC_ACK_RODEX_LIST_HPP */
