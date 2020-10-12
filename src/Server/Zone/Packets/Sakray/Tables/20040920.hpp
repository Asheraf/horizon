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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20040920
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20040920

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
		ADD_PKT(0x009b, 10, CZ_CHANGE_DIRECTION(sock));
		ADD_PKT(0x0072, 18, CZ_ENTER(sock));
		ADD_PKT(0x00a2, 10, CZ_ITEM_THROW(sock));
		ADD_PKT(0x00f5, 32, CZ_MOVE_ITEM_FROM_STORE_TO_BODY(sock));
		ADD_PKT(0x0094, 19, CZ_REQNAME(sock));
		ADD_PKT(0x0193, 12, CZ_REQNAME_BYGID(sock));
		ADD_PKT(0x0089, 14, CZ_REQUEST_ACT(sock));
		ADD_PKT(0x00f3, 18, CZ_REQUEST_CHAT(sock));
		ADD_PKT(0x0085, 9, CZ_REQUEST_MOVE(sock));
		ADD_PKT(0x007e, 25, CZ_REQUEST_TIME(sock));
		ADD_PKT(0x0113, 14, CZ_USE_SKILL(sock));
		ADD_PKT(0x0116, 14, CZ_USE_SKILL_TOGROUND(sock));
		ADD_PKT(0x0190, 14, CZ_USE_SKILL_TOGROUND_WITHTALKBOX(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20040920 */