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

#ifndef HORIZON_ZONE_RAGEXE_20171206_PACKET_ZC_GROUP_LIST_HPP
#define HORIZON_ZONE_RAGEXE_20171206_PACKET_ZC_GROUP_LIST_HPP

#include "Server/Zone/Packets/Ragexe/20171206/PacketsRagexe20171206.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_GROUP_LIST.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171206
{
struct PACKET_ZC_GROUP_LIST : public Horizon::Zone::Ragexe::PACKET_ZC_GROUP_LIST
{
	PACKET_ZC_GROUP_LIST(uint16_t packet_id = ZC_GROUP_LIST) : Horizon::Zone::Ragexe::PACKET_ZC_GROUP_LIST(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171206_PACKET_ZC_GROUP_LIST_HPP */
