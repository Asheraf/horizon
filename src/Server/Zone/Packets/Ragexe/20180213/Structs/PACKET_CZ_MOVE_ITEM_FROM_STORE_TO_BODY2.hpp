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

#ifndef HORIZON_ZONE_RAGEXE_20180213_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2_HPP
#define HORIZON_ZONE_RAGEXE_20180213_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2_HPP

#include "Server/Zone/Packets/Ragexe/20180213/PacketsRagexe20180213.hpp"
#include "Server/Zone/Packets/Ragexe/20180124/Structs/PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180213
{
struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2 : public Horizon::Zone::Ragexe20180124::PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2
{
	PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(uint16_t packet_id = CZ_MOVE_ITEM_FROM_STORE_TO_BODY2) : Horizon::Zone::Ragexe20180124::PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180213_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY2_HPP */
