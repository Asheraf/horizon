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

#ifndef HORIZON_ZONE_ZERO_20180627_PACKET_CZ_SEARCH_STORE_INFO_HPP
#define HORIZON_ZONE_ZERO_20180627_PACKET_CZ_SEARCH_STORE_INFO_HPP

#include "Server/Zone/Packets/Zero/20180627/PacketsZero20180627.hpp"
#include "Server/Zone/Packets/Zero/20180605/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Zero20180627
{
struct PACKET_CZ_SEARCH_STORE_INFO : public Horizon::Zone::Zero20180605::PACKET_CZ_SEARCH_STORE_INFO
{
	PACKET_CZ_SEARCH_STORE_INFO(uint16_t packet_id = CZ_SEARCH_STORE_INFO) : Horizon::Zone::Zero20180605::PACKET_CZ_SEARCH_STORE_INFO(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_ZERO_20180627_PACKET_CZ_SEARCH_STORE_INFO_HPP */
