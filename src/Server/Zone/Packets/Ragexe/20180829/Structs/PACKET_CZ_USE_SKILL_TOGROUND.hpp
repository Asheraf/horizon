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

#ifndef HORIZON_ZONE_RAGEXE_20180829_PACKET_CZ_USE_SKILL_TOGROUND_HPP
#define HORIZON_ZONE_RAGEXE_20180829_PACKET_CZ_USE_SKILL_TOGROUND_HPP

#include "Server/Zone/Packets/Ragexe/20180829/PacketsRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/Structs/PACKET_CZ_USE_SKILL_TOGROUND.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180829
{
struct PACKET_CZ_USE_SKILL_TOGROUND : public Horizon::Zone::Ragexe20180822::PACKET_CZ_USE_SKILL_TOGROUND
{
	PACKET_CZ_USE_SKILL_TOGROUND(uint16_t packet_id = CZ_USE_SKILL_TOGROUND) : Horizon::Zone::Ragexe20180822::PACKET_CZ_USE_SKILL_TOGROUND(packet_id) { }

	/* Size: 10 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180829_PACKET_CZ_USE_SKILL_TOGROUND_HPP */
