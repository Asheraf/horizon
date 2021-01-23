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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20120221
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20120221

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
		ADD_HPKT(0x0974, 2, CZ_CANCEL_MERGE_ITEM);
		ADD_HPKT(0x022d, 6, CZ_COMMAND_MER);
		ADD_HPKT(0x0363, 18, CZ_ITEM_THROW2);
		ADD_HPKT(0x0368, 6, CZ_REQNAME2);
		ADD_HPKT(0x0369, 7, CZ_REQNAME_BYGID2);
		ADD_HPKT(0x0437, 5, CZ_REQUEST_ACT2);
		ADD_HPKT(0x035f, 6, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0360, 5, CZ_REQUEST_TIME2);
		ADD_HPKT(0x0815, -1, CZ_REQ_CLOSE_BUYING_STORE);
		ADD_HPKT(0x096e, 6, CZ_REQ_MERGE_ITEM);
		ADD_HPKT(0x0811, -1, CZ_REQ_OPEN_BUYING_STORE);
		ADD_HPKT(0x0819, -1, CZ_REQ_TRADE_BUYING_STORE);
		ADD_HPKT(0x0838, 12, CZ_SEARCH_STORE_INFO_NEXT_PAGE);
		ADD_HPKT(0x083c, 10, CZ_SSILIST_ITEM_CLICK);
		ADD_HPKT(0x0438, 10, CZ_USE_SKILL2);
		ADD_HPKT(0x0366, 90, CZ_USE_SKILL_TOGROUND2);
		ADD_TPKT(0x096f, 7, ZC_ACK_MERGE_ITEM);
		ADD_TPKT(0x0977, 15, ZC_HP_INFO);
		ADD_TPKT(0x0976, -1, ZC_STORE_ITEMLIST_EQUIP_V2);
		ADD_TPKT(0x0975, -1, ZC_STORE_ITEMLIST_NORMAL_V2);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20120221 */