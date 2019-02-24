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

#ifndef HORIZON_ZONE_RAGEXE_20181031_PACKET_CZ_ITEMLISTWIN_RES_HPP
#define HORIZON_ZONE_RAGEXE_20181031_PACKET_CZ_ITEMLISTWIN_RES_HPP

#include "Server/Zone/Packets/Ragexe/20181031/PacketsRagexe20181031.hpp"
#include "Server/Zone/Packets/Ragexe/20181024/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181031
{
struct PACKET_CZ_ITEMLISTWIN_RES : public Horizon::Zone::Ragexe20181024::PACKET_CZ_ITEMLISTWIN_RES
{
	PACKET_CZ_ITEMLISTWIN_RES(uint16_t packet_id = CZ_ITEMLISTWIN_RES) : Horizon::Zone::Ragexe20181024::PACKET_CZ_ITEMLISTWIN_RES(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181031_PACKET_CZ_ITEMLISTWIN_RES_HPP */
