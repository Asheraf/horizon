/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_RAGEXE_20180605_PACKET_ZC_UPDATE_MISSION_HUNT_EX_HPP
#define HORIZON_ZONE_RAGEXE_20180605_PACKET_ZC_UPDATE_MISSION_HUNT_EX_HPP

#include "Server/Zone/Packets/Ragexe/20180605/PacketsRagexe20180605.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_UPDATE_MISSION_HUNT_EX.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180605
{
struct PACKET_ZC_UPDATE_MISSION_HUNT_EX : public Horizon::Zone::Ragexe::PACKET_ZC_UPDATE_MISSION_HUNT_EX
{
	PACKET_ZC_UPDATE_MISSION_HUNT_EX(uint16_t packet_id = ZC_UPDATE_MISSION_HUNT_EX) : Horizon::Zone::Ragexe::PACKET_ZC_UPDATE_MISSION_HUNT_EX(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180605_PACKET_ZC_UPDATE_MISSION_HUNT_EX_HPP */
