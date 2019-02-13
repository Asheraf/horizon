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

#ifndef HORIZON_ZONE_RE_20170906_PACKET_CZ_SEARCH_STORE_INFO_HPP
#define HORIZON_ZONE_RE_20170906_PACKET_CZ_SEARCH_STORE_INFO_HPP

#include "Server/Zone/Packets/RE/20170906/PacketsRE20170906.hpp"
#include "Server/Zone/Packets/RE/20170830/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20170906
{
struct PACKET_CZ_SEARCH_STORE_INFO : public Horizon::Zone::RE20170830::PACKET_CZ_SEARCH_STORE_INFO
{
	PACKET_CZ_SEARCH_STORE_INFO(uint16_t packet_id = CZ_SEARCH_STORE_INFO) : Horizon::Zone::RE20170830::PACKET_CZ_SEARCH_STORE_INFO(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20170906_PACKET_CZ_SEARCH_STORE_INFO_HPP */
