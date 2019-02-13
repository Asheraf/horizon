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

#ifndef HORIZON_ZONE_RAGEXE_20170830_PACKET_CZ_REQNAME_BYGID2_HPP
#define HORIZON_ZONE_RAGEXE_20170830_PACKET_CZ_REQNAME_BYGID2_HPP

#include "Server/Zone/Packets/Ragexe/20170830/PacketsRagexe20170830.hpp"
#include "Server/Zone/Packets/Ragexe/20170809/Structs/PACKET_CZ_REQNAME_BYGID2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170830
{
struct PACKET_CZ_REQNAME_BYGID2 : public Horizon::Zone::Ragexe20170809::PACKET_CZ_REQNAME_BYGID2
{
	PACKET_CZ_REQNAME_BYGID2(uint16_t packet_id = CZ_REQNAME_BYGID2) : Horizon::Zone::Ragexe20170809::PACKET_CZ_REQNAME_BYGID2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170830_PACKET_CZ_REQNAME_BYGID2_HPP */
