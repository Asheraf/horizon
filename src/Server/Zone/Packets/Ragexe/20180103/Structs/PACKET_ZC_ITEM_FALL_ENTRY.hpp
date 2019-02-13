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

#ifndef HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ITEM_FALL_ENTRY_HPP
#define HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ITEM_FALL_ENTRY_HPP

#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/20170913/Structs/PACKET_ZC_ITEM_FALL_ENTRY.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180103
{
struct PACKET_ZC_ITEM_FALL_ENTRY : public Horizon::Zone::Ragexe20170913::PACKET_ZC_ITEM_FALL_ENTRY
{
	PACKET_ZC_ITEM_FALL_ENTRY(uint16_t packet_id = ZC_ITEM_FALL_ENTRY) : Horizon::Zone::Ragexe20170913::PACKET_ZC_ITEM_FALL_ENTRY(packet_id) { }

	/* Size: 22 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ITEM_FALL_ENTRY_HPP */
