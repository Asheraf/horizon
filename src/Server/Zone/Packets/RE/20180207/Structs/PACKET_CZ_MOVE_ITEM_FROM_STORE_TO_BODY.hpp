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

#ifndef HORIZON_ZONE_RE_20180207_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY_HPP
#define HORIZON_ZONE_RE_20180207_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY_HPP

#include "Server/Zone/Packets/RE/20180207/PacketsRE20180207.hpp"
#include "Server/Zone/Packets/RE/20180124/Structs/PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20180207
{
struct PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY : public Horizon::Zone::RE20180124::PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY
{
	PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY(uint16_t packet_id = CZ_MOVE_ITEM_FROM_STORE_TO_BODY) : Horizon::Zone::RE20180124::PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY(packet_id) { }

	/* Size: 8 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20180207_PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY_HPP */
