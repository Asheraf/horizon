/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20050718
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20050718

#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
/**
 * @brief Client Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ClientPacketLengthTable : public PacketLengthTable
{
public:
	ClientPacketLengthTable(std::shared_ptr<ZoneSession> s)
	: PacketLengthTable(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x024d, 14, CZ_AUCTION_ADD);
		ADD_HPKT(0x024e, 6, CZ_AUCTION_ADD_CANCEL);
		ADD_HPKT(0x024c, 8, CZ_AUCTION_ADD_ITEM);
		ADD_HPKT(0x024f, 10, CZ_AUCTION_BUY);
		ADD_HPKT(0x024b, 4, CZ_AUCTION_CREATE);
		ADD_HPKT(0x0251, 2, CZ_AUCTION_ITEM_SEARCH);
		ADD_HPKT(0x009b, 33, CZ_CHANGE_DIRECTION);
		ADD_HPKT(0x0072, 20, CZ_ENTER);
		ADD_HPKT(0x009f, 17, CZ_ITEM_PICKUP);
		ADD_HPKT(0x00a2, 12, CZ_ITEM_THROW);
		ADD_HPKT(0x0247, 8, CZ_MAIL_ADD_ITEM);
		ADD_HPKT(0x0243, 6, CZ_MAIL_DELETE);
		ADD_HPKT(0x0244, 6, CZ_MAIL_GET_ITEM);
		ADD_HPKT(0x023f, 2, CZ_MAIL_GET_LIST);
		ADD_HPKT(0x0241, 6, CZ_MAIL_OPEN);
		ADD_HPKT(0x0246, 4, CZ_MAIL_RESET_ITEM);
		ADD_HPKT(0x0248, 68, CZ_MAIL_SEND);
		ADD_HPKT(0x00f5, 10, CZ_MOVE_ITEM_FROM_STORE_TO_BODY);
		ADD_HPKT(0x0094, 16, CZ_REQNAME);
		ADD_HPKT(0x0089, 10, CZ_REQUEST_ACT);
		ADD_HPKT(0x0085, 13, CZ_REQUEST_MOVE);
		ADD_HPKT(0x00f7, 26, CZ_REQUEST_TIME);
		ADD_HPKT(0x0113, 23, CZ_USE_SKILL);
		ADD_HPKT(0x0116, 14, CZ_USE_SKILL_TOGROUND);
		ADD_HPKT(0x0190, 9, CZ_USE_SKILL_TOGROUND_WITHTALKBOX);
		ADD_TPKT(0x0252, -1, ZC_AUCTION_ITEM_REQ_SEARCH);
		ADD_TPKT(0x0250, 3, ZC_AUCTION_RESULT);
		ADD_TPKT(0x024a, 70, ZC_MAIL_RECEIVE);
		ADD_TPKT(0x0245, 7, ZC_MAIL_REQ_GET_ITEM);
		ADD_TPKT(0x0240, 8, ZC_MAIL_REQ_GET_LIST);
		ADD_TPKT(0x0242, -1, ZC_MAIL_REQ_OPEN);
		ADD_TPKT(0x0249, 3, ZC_MAIL_REQ_SEND);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20050718 */