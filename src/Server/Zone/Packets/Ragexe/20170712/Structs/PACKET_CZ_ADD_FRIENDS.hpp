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

#ifndef HORIZON_ZONE_RAGEXE_20170712_PACKET_CZ_ADD_FRIENDS_HPP
#define HORIZON_ZONE_RAGEXE_20170712_PACKET_CZ_ADD_FRIENDS_HPP

#include "Server/Zone/Packets/Ragexe/20170712/PacketsRagexe20170712.hpp"
#include "Server/Zone/Packets/Ragexe/20170705/Structs/PACKET_CZ_ADD_FRIENDS.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20170712
{
struct PACKET_CZ_ADD_FRIENDS : public Horizon::Zone::Ragexe20170705::PACKET_CZ_ADD_FRIENDS
{
	PACKET_CZ_ADD_FRIENDS(uint16_t packet_id = CZ_ADD_FRIENDS) : Horizon::Zone::Ragexe20170705::PACKET_CZ_ADD_FRIENDS(packet_id) { }

	/* Size: 26 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20170712_PACKET_CZ_ADD_FRIENDS_HPP */
