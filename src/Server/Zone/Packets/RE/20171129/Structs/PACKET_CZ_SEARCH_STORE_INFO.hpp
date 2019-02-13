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

#ifndef HORIZON_ZONE_RE_20171129_PACKET_CZ_SEARCH_STORE_INFO_HPP
#define HORIZON_ZONE_RE_20171129_PACKET_CZ_SEARCH_STORE_INFO_HPP

#include "Server/Zone/Packets/RE/20171129/PacketsRE20171129.hpp"
#include "Server/Zone/Packets/RE/20171122/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20171129
{
struct PACKET_CZ_SEARCH_STORE_INFO : public Horizon::Zone::RE20171122::PACKET_CZ_SEARCH_STORE_INFO
{
	PACKET_CZ_SEARCH_STORE_INFO(uint16_t packet_id = CZ_SEARCH_STORE_INFO) : Horizon::Zone::RE20171122::PACKET_CZ_SEARCH_STORE_INFO(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20171129_PACKET_CZ_SEARCH_STORE_INFO_HPP */
