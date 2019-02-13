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

#ifndef HORIZON_ZONE_RAGEXE_20180912_PACKET_CZ_NPC_BARTER_PURCHASE_HPP
#define HORIZON_ZONE_RAGEXE_20180912_PACKET_CZ_NPC_BARTER_PURCHASE_HPP

#include "Server/Zone/Packets/Ragexe/20180912/PacketsRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_CZ_NPC_BARTER_PURCHASE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180912
{
struct PACKET_CZ_NPC_BARTER_PURCHASE : public Horizon::Zone::Ragexe::PACKET_CZ_NPC_BARTER_PURCHASE
{
	PACKET_CZ_NPC_BARTER_PURCHASE(uint16_t packet_id = CZ_NPC_BARTER_PURCHASE) : Horizon::Zone::Ragexe::PACKET_CZ_NPC_BARTER_PURCHASE(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180912_PACKET_CZ_NPC_BARTER_PURCHASE_HPP */
