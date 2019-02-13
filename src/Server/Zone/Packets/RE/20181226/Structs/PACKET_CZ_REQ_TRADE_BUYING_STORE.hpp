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

#ifndef HORIZON_ZONE_RE_20181226_PACKET_CZ_REQ_TRADE_BUYING_STORE_HPP
#define HORIZON_ZONE_RE_20181226_PACKET_CZ_REQ_TRADE_BUYING_STORE_HPP

#include "Server/Zone/Packets/RE/20181226/PacketsRE20181226.hpp"
#include "Server/Zone/Packets/RE/20181219/Structs/PACKET_CZ_REQ_TRADE_BUYING_STORE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace RE20181226
{
struct PACKET_CZ_REQ_TRADE_BUYING_STORE : public Horizon::Zone::RE20181219::PACKET_CZ_REQ_TRADE_BUYING_STORE
{
	PACKET_CZ_REQ_TRADE_BUYING_STORE(uint16_t packet_id = CZ_REQ_TRADE_BUYING_STORE) : Horizon::Zone::RE20181219::PACKET_CZ_REQ_TRADE_BUYING_STORE(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RE_20181226_PACKET_CZ_REQ_TRADE_BUYING_STORE_HPP */
