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

#ifndef HORIZON_ZONE_RAGEXE_20180801_PACKET_ZC_EQUIPWIN_MICROSCOPE_V7_HPP
#define HORIZON_ZONE_RAGEXE_20180801_PACKET_ZC_EQUIPWIN_MICROSCOPE_V7_HPP

#include "Server/Zone/Packets/Ragexe/20180801/PacketsRagexe20180801.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_EQUIPWIN_MICROSCOPE_V7.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180801
{
struct PACKET_ZC_EQUIPWIN_MICROSCOPE_V7 : public Horizon::Zone::Ragexe::PACKET_ZC_EQUIPWIN_MICROSCOPE_V7
{
	PACKET_ZC_EQUIPWIN_MICROSCOPE_V7(uint16_t packet_id = ZC_EQUIPWIN_MICROSCOPE_V7) : Horizon::Zone::Ragexe::PACKET_ZC_EQUIPWIN_MICROSCOPE_V7(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180801_PACKET_ZC_EQUIPWIN_MICROSCOPE_V7_HPP */
