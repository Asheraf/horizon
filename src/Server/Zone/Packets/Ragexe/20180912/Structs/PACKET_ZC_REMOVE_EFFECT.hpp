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

#ifndef HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_REMOVE_EFFECT_HPP
#define HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_REMOVE_EFFECT_HPP

#include "Server/Zone/Packets/Ragexe/20180912/PacketsRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_REMOVE_EFFECT.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180912
{
struct PACKET_ZC_REMOVE_EFFECT : public Horizon::Zone::Ragexe::PACKET_ZC_REMOVE_EFFECT
{
	PACKET_ZC_REMOVE_EFFECT(uint16_t packet_id = ZC_REMOVE_EFFECT) : Horizon::Zone::Ragexe::PACKET_ZC_REMOVE_EFFECT(packet_id) { }

	/* Size: 10 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_REMOVE_EFFECT_HPP */
