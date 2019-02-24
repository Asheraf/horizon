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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_RAGEXE_20181128_PACKET_CZ_ITEM_PICKUP_HPP
#define HORIZON_ZONE_RAGEXE_20181128_PACKET_CZ_ITEM_PICKUP_HPP

#include "Server/Zone/Packets/Ragexe/20181128/PacketsRagexe20181128.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ITEM_PICKUP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181128
{
struct PACKET_CZ_ITEM_PICKUP : public Horizon::Zone::Ragexe20181121::PACKET_CZ_ITEM_PICKUP
{
	PACKET_CZ_ITEM_PICKUP(uint16_t packet_id = CZ_ITEM_PICKUP) : Horizon::Zone::Ragexe20181121::PACKET_CZ_ITEM_PICKUP(packet_id) { }

	/* Size: 6 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181128_PACKET_CZ_ITEM_PICKUP_HPP */
