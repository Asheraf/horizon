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

#ifndef HORIZON_ZONE_RAGEXE_20181031_PACKET_CZ_INVENTORY_EXPAND_CONFIRMED_HPP
#define HORIZON_ZONE_RAGEXE_20181031_PACKET_CZ_INVENTORY_EXPAND_CONFIRMED_HPP

#include "Server/Zone/Packets/Ragexe/20181031/PacketsRagexe20181031.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_CZ_INVENTORY_EXPAND_CONFIRMED.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181031
{
struct PACKET_CZ_INVENTORY_EXPAND_CONFIRMED : public Horizon::Zone::Ragexe::PACKET_CZ_INVENTORY_EXPAND_CONFIRMED
{
	PACKET_CZ_INVENTORY_EXPAND_CONFIRMED(uint16_t packet_id = CZ_INVENTORY_EXPAND_CONFIRMED) : Horizon::Zone::Ragexe::PACKET_CZ_INVENTORY_EXPAND_CONFIRMED(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181031_PACKET_CZ_INVENTORY_EXPAND_CONFIRMED_HPP */
