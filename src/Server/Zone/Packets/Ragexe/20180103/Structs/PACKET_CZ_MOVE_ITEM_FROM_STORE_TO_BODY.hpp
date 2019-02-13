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

#ifndef HORIZON_ZONE_RAGEXE_20180103_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY_HPP
#define HORIZON_ZONE_RAGEXE_20180103_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY_HPP

#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/20171227/Structs/PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180103
{
struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY : public Horizon::Zone::Ragexe20171227::PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
{
	PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY(uint16_t packet_id = CZ_MOVE_ITEM_FROM_STORE_TO_BODY) : Horizon::Zone::Ragexe20171227::PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY(packet_id) { }

	/* Size: 8 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180103_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY_HPP */
