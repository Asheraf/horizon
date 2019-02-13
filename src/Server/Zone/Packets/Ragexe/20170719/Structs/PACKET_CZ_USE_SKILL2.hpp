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

#ifndef HORIZON_ZONE_RAGEXE_20170719_PACKET_CZ_USE_SKILL2_HPP
#define HORIZON_ZONE_RAGEXE_20170719_PACKET_CZ_USE_SKILL2_HPP

#include "Server/Zone/Packets/Ragexe/20170719/PacketsRagexe20170719.hpp"
#include "Server/Zone/Packets/Ragexe/20170517/Structs/PACKET_CZ_USE_SKILL2.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170719
{
struct PACKET_CZ_USE_SKILL2 : public Horizon::Zone::Ragexe20170517::PACKET_CZ_USE_SKILL2
{
	PACKET_CZ_USE_SKILL2(uint16_t packet_id = CZ_USE_SKILL2) : Horizon::Zone::Ragexe20170517::PACKET_CZ_USE_SKILL2(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170719_PACKET_CZ_USE_SKILL2_HPP */
