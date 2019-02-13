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

#ifndef HORIZON_ZONE_RAGEXE_20171115_PACKET_ZC_OPEN_UI_HPP
#define HORIZON_ZONE_RAGEXE_20171115_PACKET_ZC_OPEN_UI_HPP

#include "Server/Zone/Packets/Ragexe/20171115/PacketsRagexe20171115.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_OPEN_UI.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20171115
{
struct PACKET_ZC_OPEN_UI : public Horizon::Zone::Ragexe::PACKET_ZC_OPEN_UI
{
	PACKET_ZC_OPEN_UI(uint16_t packet_id = ZC_OPEN_UI) : Horizon::Zone::Ragexe::PACKET_ZC_OPEN_UI(packet_id) { }

	/* Size: 7 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20171115_PACKET_ZC_OPEN_UI_HPP */
