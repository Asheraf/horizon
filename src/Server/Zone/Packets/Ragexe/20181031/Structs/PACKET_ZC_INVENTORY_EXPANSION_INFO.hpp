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

#ifndef HORIZON_ZONE_RAGEXE_20181031_PACKET_ZC_INVENTORY_EXPANSION_INFO_HPP
#define HORIZON_ZONE_RAGEXE_20181031_PACKET_ZC_INVENTORY_EXPANSION_INFO_HPP

#include "Server/Zone/Packets/Ragexe/20181031/PacketsRagexe20181031.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_INVENTORY_EXPANSION_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181031
{
struct PACKET_ZC_INVENTORY_EXPANSION_INFO : public Horizon::Zone::Ragexe::PACKET_ZC_INVENTORY_EXPANSION_INFO
{
	PACKET_ZC_INVENTORY_EXPANSION_INFO(uint16_t packet_id = ZC_INVENTORY_EXPANSION_INFO) : Horizon::Zone::Ragexe::PACKET_ZC_INVENTORY_EXPANSION_INFO(packet_id) { }

	/* Size: 4 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181031_PACKET_ZC_INVENTORY_EXPANSION_INFO_HPP */
