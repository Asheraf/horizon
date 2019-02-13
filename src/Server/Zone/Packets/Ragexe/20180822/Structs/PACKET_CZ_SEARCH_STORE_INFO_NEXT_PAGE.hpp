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

#ifndef HORIZON_ZONE_RAGEXE_20180822_PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE_HPP
#define HORIZON_ZONE_RAGEXE_20180822_PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE_HPP

#include "Server/Zone/Packets/Ragexe/20180822/PacketsRagexe20180822.hpp"
#include "Server/Zone/Packets/Ragexe/20180808/Structs/PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180822
{
struct PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE : public Horizon::Zone::Ragexe20180808::PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE
{
	PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE(uint16_t packet_id = CZ_SEARCH_STORE_INFO_NEXT_PAGE) : Horizon::Zone::Ragexe20180808::PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180822_PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE_HPP */
