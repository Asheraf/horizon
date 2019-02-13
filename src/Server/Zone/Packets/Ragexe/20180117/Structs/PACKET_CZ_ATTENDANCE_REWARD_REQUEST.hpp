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

#ifndef HORIZON_ZONE_RAGEXE_20180117_PACKET_CZ_ATTENDANCE_REWARD_REQUEST_HPP
#define HORIZON_ZONE_RAGEXE_20180117_PACKET_CZ_ATTENDANCE_REWARD_REQUEST_HPP

#include "Server/Zone/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_CZ_ATTENDANCE_REWARD_REQUEST.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180117
{
struct PACKET_CZ_ATTENDANCE_REWARD_REQUEST : public Horizon::Zone::Ragexe::PACKET_CZ_ATTENDANCE_REWARD_REQUEST
{
	PACKET_CZ_ATTENDANCE_REWARD_REQUEST(uint16_t packet_id = CZ_ATTENDANCE_REWARD_REQUEST) : Horizon::Zone::Ragexe::PACKET_CZ_ATTENDANCE_REWARD_REQUEST(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180117_PACKET_CZ_ATTENDANCE_REWARD_REQUEST_HPP */
