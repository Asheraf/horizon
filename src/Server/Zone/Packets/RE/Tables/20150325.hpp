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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20150325
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20150325

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
		ADD_PKT(0x0919, 36, CZ_ACK_STORE_PASSWORD(sock));
		ADD_PKT(0x0940, 26, CZ_ADD_FRIENDS(sock));
		ADD_PKT(0x087e, 5, CZ_CHANGE_DIRECTION(sock));
		ADD_PKT(0x0938, 5, CZ_COMMAND_MER(sock));
		ADD_PKT(0x094a, 19, CZ_ENTER(sock));
		ADD_PKT(0x0802, 4, CZ_GANGSI_RANK(sock));
		ADD_PKT(0x0950, -1, CZ_ITEMLISTWIN_RES(sock));
		ADD_PKT(0x092c, 6, CZ_ITEM_PICKUP(sock));
		ADD_PKT(0x0363, 6, CZ_ITEM_THROW(sock));
		ADD_PKT(0x0893, 8, CZ_JOIN_BATTLE_FIELD(sock));
		ADD_PKT(0x087c, 8, CZ_MOVE_ITEM_FROM_BODY_TO_STORE(sock));
		ADD_PKT(0x0969, 8, CZ_MOVE_ITEM_FROM_STORE_TO_BODY(sock));
		ADD_PKT(0x0899, 18, CZ_PARTY_BOOKING_REQ_REGISTER(sock));
		ADD_PKT(0x0202, 26, CZ_PARTY_JOIN_REQ(sock));
		ADD_PKT(0x0891, 6, CZ_REQNAME(sock));
		ADD_PKT(0x085d, 6, CZ_REQNAME_BYGID(sock));
		ADD_PKT(0x08a1, 7, CZ_REQUEST_ACT(sock));
		ADD_PKT(0x0932, 5, CZ_REQUEST_MOVE(sock));
		ADD_PKT(0x0954, 6, CZ_REQUEST_TIME(sock));
		ADD_PKT(0x0819, 6, CZ_REQ_CLICK_TO_BUYING_STORE(sock));
		ADD_PKT(0x0947, 2, CZ_REQ_CLOSE_BUYING_STORE(sock));
		ADD_PKT(0x086f, -1, CZ_REQ_OPEN_BUYING_STORE(sock));
		ADD_PKT(0x0897, -1, CZ_REQ_TRADE_BUYING_STORE(sock));
		ADD_PKT(0x0931, -1, CZ_SEARCH_STORE_INFO(sock));
		ADD_PKT(0x0438, 2, CZ_SEARCH_STORE_INFO_NEXT_PAGE(sock));
		ADD_PKT(0x0883, 12, CZ_SSILIST_ITEM_CLICK(sock));
		ADD_PKT(0x0365, 10, CZ_USE_SKILL(sock));
		ADD_PKT(0x0885, 10, CZ_USE_SKILL_TOGROUND(sock));
		ADD_PKT(0x08a7, 90, CZ_USE_SKILL_TOGROUND_WITHTALKBOX(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20150325 */