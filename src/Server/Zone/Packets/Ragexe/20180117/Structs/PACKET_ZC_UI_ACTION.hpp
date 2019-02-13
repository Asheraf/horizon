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

#ifndef HORIZON_ZONE_RAGEXE_20180117_PACKET_ZC_UI_ACTION_HPP
#define HORIZON_ZONE_RAGEXE_20180117_PACKET_ZC_UI_ACTION_HPP

#include "Server/Zone/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_UI_ACTION.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180117
{
struct PACKET_ZC_UI_ACTION : public Horizon::Zone::Ragexe::PACKET_ZC_UI_ACTION
{
	PACKET_ZC_UI_ACTION(uint16_t packet_id = ZC_UI_ACTION) : Horizon::Zone::Ragexe::PACKET_ZC_UI_ACTION(packet_id) { }

	/* Size: 10 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180117_PACKET_ZC_UI_ACTION_HPP */
