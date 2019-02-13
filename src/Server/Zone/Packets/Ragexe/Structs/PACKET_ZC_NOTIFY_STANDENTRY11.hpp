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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_STANDENTRY11_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_STANDENTRY11_HPP

#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NOTIFY_STANDENTRY10.hpp"
#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_NOTIFY_STANDENTRY11 : public PACKET_ZC_NOTIFY_STANDENTRY10
{
	PACKET_ZC_NOTIFY_STANDENTRY11(uint16_t packet_id = ZC_NOTIFY_STANDENTRY11) : PACKET_ZC_NOTIFY_STANDENTRY10(packet_id) { }
	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_NOTIFY_STANDENTRY11_HPP */
