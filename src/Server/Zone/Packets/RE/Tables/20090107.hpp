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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090107
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090107

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
namespace ShufflePackets
{
/**
 * @brief Shuffle Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ShufflePacketLengthTable : public PacketLengthTable
{
public:
	ShufflePacketLengthTable()
	{
		std::shared_ptr<ZoneSocket> sock = get_socket();

#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair<uint16_t, NetworkPacket>(j, k))
		ADD_PKT(0x009b, 34, CZ_CHANGE_DIRECTION(sock));
		ADD_PKT(0x0072, 22, CZ_ENTER(sock));
		ADD_PKT(0x009f, 20, CZ_ITEM_PICKUP(sock));
		ADD_PKT(0x02e4, 11, CZ_ITEM_PICKUP_NEW_JAPEN(sock));
		ADD_PKT(0x00a2, 14, CZ_ITEM_THROW(sock));
		ADD_PKT(0x00f5, 11, CZ_MOVE_ITEM_FROM_STORE_TO_BODY(sock));
		ADD_PKT(0x0094, 19, CZ_REQNAME(sock));
		ADD_PKT(0x0089, 11, CZ_REQUEST_ACT(sock));
		ADD_PKT(0x0085, 10, CZ_REQUEST_MOVE(sock));
		ADD_PKT(0x02e5, 9, CZ_REQUEST_MOVE_NEW_JAPEN(sock));
		ADD_PKT(0x00f7, 17, CZ_REQUEST_TIME(sock));
		ADD_PKT(0x02e2, 20, CZ_USE_ITEM_NEW_JAPEN(sock));
		ADD_PKT(0x0113, 25, CZ_USE_SKILL(sock));
		ADD_PKT(0x02e3, 22, CZ_USE_SKILL_NEW_JAPEN(sock));
		ADD_PKT(0x0116, 17, CZ_USE_SKILL_TOGROUND(sock));
		ADD_PKT(0x0190, 23, CZ_USE_SKILL_TOGROUND_WITHTALKBOX(sock));
		ADD_PKT(0x043f, 8, ZC_MSG_STATE_CHANGE2(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090107 */