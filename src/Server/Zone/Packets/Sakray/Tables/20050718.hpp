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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20050718
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20050718

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
		ADD_PKT(0x024d, 14, CZ_AUCTION_ADD(sock));
		ADD_PKT(0x024e, 6, CZ_AUCTION_ADD_CANCEL(sock));
		ADD_PKT(0x024c, 8, CZ_AUCTION_ADD_ITEM(sock));
		ADD_PKT(0x024f, 10, CZ_AUCTION_BUY(sock));
		ADD_PKT(0x024b, 4, CZ_AUCTION_CREATE(sock));
		ADD_PKT(0x0251, 2, CZ_AUCTION_ITEM_SEARCH(sock));
		ADD_PKT(0x009b, 31, CZ_CHANGE_DIRECTION(sock));
		ADD_PKT(0x0072, 19, CZ_ENTER(sock));
		ADD_PKT(0x009f, 12, CZ_ITEM_PICKUP(sock));
		ADD_PKT(0x00a2, 18, CZ_ITEM_THROW(sock));
		ADD_PKT(0x0247, 8, CZ_MAIL_ADD_ITEM(sock));
		ADD_PKT(0x0243, 6, CZ_MAIL_DELETE(sock));
		ADD_PKT(0x0244, 6, CZ_MAIL_GET_ITEM(sock));
		ADD_PKT(0x023f, 2, CZ_MAIL_GET_LIST(sock));
		ADD_PKT(0x0241, 6, CZ_MAIL_OPEN(sock));
		ADD_PKT(0x0246, 4, CZ_MAIL_RESET_ITEM(sock));
		ADD_PKT(0x0248, 68, CZ_MAIL_SEND(sock));
		ADD_PKT(0x00f5, 7, CZ_MOVE_ITEM_FROM_STORE_TO_BODY(sock));
		ADD_PKT(0x0094, 21, CZ_REQNAME(sock));
		ADD_PKT(0x0089, 7, CZ_REQUEST_ACT(sock));
		ADD_PKT(0x0085, 11, CZ_REQUEST_MOVE(sock));
		ADD_PKT(0x00f7, 13, CZ_REQUEST_TIME(sock));
		ADD_PKT(0x0113, 30, CZ_USE_SKILL(sock));
		ADD_PKT(0x0190, 21, CZ_USE_SKILL_TOGROUND_WITHTALKBOX(sock));
		ADD_PKT(0x0252, -1, ZC_AUCTION_ITEM_REQ_SEARCH(sock));
		ADD_PKT(0x0250, 3, ZC_AUCTION_RESULT(sock));
		ADD_PKT(0x024a, 70, ZC_MAIL_RECEIVE(sock));
		ADD_PKT(0x0245, 7, ZC_MAIL_REQ_GET_ITEM(sock));
		ADD_PKT(0x0240, 8, ZC_MAIL_REQ_GET_LIST(sock));
		ADD_PKT(0x0242, -1, ZC_MAIL_REQ_OPEN(sock));
		ADD_PKT(0x0249, 3, ZC_MAIL_REQ_SEND(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20050718 */