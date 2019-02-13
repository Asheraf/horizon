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

#ifndef HORIZON_ZONE_RAGEXE_20180321_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP
#define HORIZON_ZONE_RAGEXE_20180321_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP

#include "Server/Zone/Packets/Ragexe/20180321/PacketsRagexe20180321.hpp"
#include "Server/Zone/Packets/Ragexe/20180315/Structs/PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180321
{
struct PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE : public Horizon::Zone::Ragexe20180315::PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE
{
	PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE(uint16_t packet_id = CZ_MOVE_ITEM_FROM_BODY_TO_STORE) : Horizon::Zone::Ragexe20180315::PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE(packet_id) { }

	/* Size: 8 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180321_PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE_HPP */
