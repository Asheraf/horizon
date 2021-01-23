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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20111122
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20111122

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
		ADD_HPKT(0x0202, 18, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0361, 2, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x022d, 7, CZ_COMMAND_MER);
		ADD_HPKT(0x0436, 6, CZ_ENTER2);
		ADD_HPKT(0x0281, 2, CZ_GANGSI_RANK);
		ADD_HPKT(0x0907, 5, CZ_INVENTORY_TAB);
		ADD_HPKT(0x0362, 8, CZ_ITEM_PICKUP2);
		ADD_HPKT(0x0363, 90, CZ_ITEM_THROW2);
		ADD_HPKT(0x07ec, -1, CZ_JOIN_BATTLE_FIELD);
		ADD_HPKT(0x0365, 2, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2);
		ADD_HPKT(0x0802, 2, CZ_PARTY_BOOKING_REQ_REGISTER);
		ADD_HPKT(0x02c4, 2, CZ_PARTY_JOIN_REQ);
		ADD_HPKT(0x08fb, 6, CZ_PARTY_RECRUIT_CANCEL_VOLUNTEER);
		ADD_HPKT(0x0368, 2, CZ_REQNAME2);
		ADD_HPKT(0x0369, -1, CZ_REQNAME_BYGID2);
		ADD_HPKT(0x0437, 2, CZ_REQUEST_ACT2);
		ADD_HPKT(0x0360, 2, CZ_REQUEST_TIME2);
		ADD_HPKT(0x0811, 2, CZ_REQ_OPEN_BUYING_STORE);
		ADD_HPKT(0x0819, 2, CZ_REQ_TRADE_BUYING_STORE);
		ADD_HPKT(0x0835, 19, CZ_SEARCH_STORE_INFO);
		ADD_HPKT(0x0838, 2, CZ_SEARCH_STORE_INFO_NEXT_PAGE);
		ADD_HPKT(0x083c, 2, CZ_SSILIST_ITEM_CLICK);
		ADD_HPKT(0x0438, 2, CZ_USE_SKILL2);
		ADD_HPKT(0x0366, 12, CZ_USE_SKILL_TOGROUND2);
		ADD_HPKT(0x0367, 4, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2);
		ADD_TPKT(0x0903, -1, ZC_CART_ITEMLIST_EQUIP);
		ADD_TPKT(0x0902, -1, ZC_CART_ITEMLIST_NORMAL);
		ADD_TPKT(0x0901, -1, ZC_INVENTORY_ITEMLIST_EQUIP);
		ADD_TPKT(0x0900, -1, ZC_INVENTORY_ITEMLIST_NORMAL);
		ADD_TPKT(0x0908, 5, ZC_INVENTORY_TAB);
		ADD_TPKT(0x0906, -1, ZC_MICROSCOPE);
		ADD_TPKT(0x0909, 6, ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER);
		ADD_TPKT(0x0905, -1, ZC_STORE_ITEMLIST_EQUIP);
		ADD_TPKT(0x0904, -1, ZC_STORE_ITEMLIST_NORMAL);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20111122 */