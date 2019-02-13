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

#ifndef HORIZON_ZONE_RAGEXE_20171115_PACKET_CZ_ITEMLISTWIN_RES_HPP
#define HORIZON_ZONE_RAGEXE_20171115_PACKET_CZ_ITEMLISTWIN_RES_HPP

#include "Server/Zone/Packets/Ragexe/20171115/PacketsRagexe20171115.hpp"
#include "Server/Zone/Packets/Ragexe/20171108/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171115
{
struct PACKET_CZ_ITEMLISTWIN_RES : public Horizon::Zone::Ragexe20171108::PACKET_CZ_ITEMLISTWIN_RES
{
	PACKET_CZ_ITEMLISTWIN_RES(uint16_t packet_id = CZ_ITEMLISTWIN_RES) : Horizon::Zone::Ragexe20171108::PACKET_CZ_ITEMLISTWIN_RES(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171115_PACKET_CZ_ITEMLISTWIN_RES_HPP */
