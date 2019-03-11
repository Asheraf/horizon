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

#ifndef HORIZON_ZONE_RAGEXE_20180307_PACKET_CZ_REQ_CLOSE_BUYING_STORE_HPP
#define HORIZON_ZONE_RAGEXE_20180307_PACKET_CZ_REQ_CLOSE_BUYING_STORE_HPP

#include "Server/Zone/Packets/Ragexe/20180307/PacketsRagexe20180307.hpp"
#include "Server/Zone/Packets/Ragexe/20180221/Structs/PACKET_CZ_REQ_CLOSE_BUYING_STORE.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180307
{
struct PACKET_CZ_REQ_CLOSE_BUYING_STORE : public Horizon::Zone::Ragexe20180221::PACKET_CZ_REQ_CLOSE_BUYING_STORE
{
	PACKET_CZ_REQ_CLOSE_BUYING_STORE(uint16_t packet_id = CZ_REQ_CLOSE_BUYING_STORE) : Horizon::Zone::Ragexe20180221::PACKET_CZ_REQ_CLOSE_BUYING_STORE(packet_id) { }

	/* Size: 2 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180307_PACKET_CZ_REQ_CLOSE_BUYING_STORE_HPP */
