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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20111025
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20111025

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
		ADD_HPKT(0x023b, 5, CZ_ACK_STORE_PASSWORD);
		ADD_HPKT(0x0202, 4, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0361, 2, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x022d, 2, CZ_COMMAND_MER);
		ADD_HPKT(0x0436, 2, CZ_ENTER2);
		ADD_HPKT(0x0281, -1, CZ_GANGSI_RANK);
		ADD_HPKT(0x0363, 19, CZ_ITEM_THROW2);
		ADD_HPKT(0x07ec, 10, CZ_JOIN_BATTLE_FIELD);
		ADD_HPKT(0x0802, 2, CZ_PARTY_BOOKING_REQ_REGISTER);
		ADD_HPKT(0x08f7, 6, CZ_PARTY_RECRUIT_ACK_RECALL);
		ADD_HPKT(0x08ef, -1, CZ_PARTY_RECRUIT_ADD_FILTERLINGLIST);
		ADD_HPKT(0x08e9, 2, CZ_PARTY_RECRUIT_REQ_DELETE);
		ADD_HPKT(0x08e5, 41, CZ_PARTY_RECRUIT_REQ_REGISTER);
		ADD_HPKT(0x08e7, 10, CZ_PARTY_RECRUIT_REQ_SEARCH);
		ADD_HPKT(0x08eb, 39, CZ_PARTY_RECRUIT_REQ_UPDATE);
		ADD_HPKT(0x08f1, 6, CZ_PARTY_RECRUIT_REQ_VOLUNTEER);
		ADD_HPKT(0x08f4, 6, CZ_PARTY_RECRUIT_SHOW_EQUIPMENT);
		ADD_HPKT(0x08f0, -1, CZ_PARTY_RECRUIT_SUB_FILTERLINGLIST);
		ADD_HPKT(0x0368, 6, CZ_REQNAME2);
		ADD_HPKT(0x0369, 7, CZ_REQNAME_BYGID2);
		ADD_HPKT(0x0437, 5, CZ_REQUEST_ACT2);
		ADD_HPKT(0x035f, 6, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0360, 6, CZ_REQUEST_TIME2);
		ADD_HPKT(0x0817, 2, CZ_REQ_CLICK_TO_BUYING_STORE);
		ADD_HPKT(0x0815, -1, CZ_REQ_CLOSE_BUYING_STORE);
		ADD_HPKT(0x0819, -1, CZ_REQ_TRADE_BUYING_STORE);
		ADD_HPKT(0x0835, 6, CZ_SEARCH_STORE_INFO);
		ADD_HPKT(0x0838, 12, CZ_SEARCH_STORE_INFO_NEXT_PAGE);
		ADD_HPKT(0x08f5, 2, CZ_UNKNOWN_BOOKING_SOMMON_MEMBER_08f5);
		ADD_HPKT(0x0438, 2, CZ_USE_SKILL2);
		ADD_HPKT(0x0366, 90, CZ_USE_SKILL_TOGROUND2);
		ADD_HPKT(0x0367, 8, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2);
		ADD_TPKT(0x08ea, 4, ZC_PARTY_RECRUIT_ACK_DELETE);
		ADD_TPKT(0x08e6, 4, ZC_PARTY_RECRUIT_ACK_REGISTER);
		ADD_TPKT(0x08f8, 6, ZC_PARTY_RECRUIT_FAILED_RECALL);
		ADD_TPKT(0x08ee, 6, ZC_PARTY_RECRUIT_NOTIFY_DELETE);
		ADD_TPKT(0x08ec, 73, ZC_PARTY_RECRUIT_NOTIFY_INSERT);
		ADD_TPKT(0x08ed, 43, ZC_PARTY_RECRUIT_NOTIFY_UPDATE);
		ADD_TPKT(0x08f6, 6, ZC_PARTY_RECRUIT_RECALL_COST);
		ADD_TPKT(0x08f2, 12, ZC_PARTY_RECRUIT_VOLUNTEER_INFO);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20111025 */