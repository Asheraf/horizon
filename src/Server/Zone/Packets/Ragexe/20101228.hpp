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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20101228
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20101228

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
		ADD_HPKT(0x023b, 8, CZ_ACK_STORE_PASSWORD);
		ADD_HPKT(0x0202, 2, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0361, 10, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x0436, 2, CZ_ENTER2);
		ADD_HPKT(0x0281, 2, CZ_GANGSI_RANK);
		ADD_HPKT(0x07e4, 6, CZ_ITEMLISTWIN_RES);
		ADD_HPKT(0x0363, 12, CZ_ITEM_THROW2);
		ADD_HPKT(0x0365, 6, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2);
		ADD_HPKT(0x0802, 2, CZ_PARTY_BOOKING_REQ_REGISTER);
		ADD_HPKT(0x0368, 6, CZ_REQNAME2);
		ADD_HPKT(0x0369, 26, CZ_REQNAME_BYGID2);
		ADD_HPKT(0x0437, 2, CZ_REQUEST_ACT2);
		ADD_HPKT(0x0817, -1, CZ_REQ_CLICK_TO_BUYING_STORE);
		ADD_HPKT(0x0815, 7, CZ_REQ_CLOSE_BUYING_STORE);
		ADD_HPKT(0x0811, 90, CZ_REQ_OPEN_BUYING_STORE);
		ADD_HPKT(0x0835, 5, CZ_SEARCH_STORE_INFO);
		ADD_HPKT(0x0838, -1, CZ_SEARCH_STORE_INFO_NEXT_PAGE);
		ADD_HPKT(0x0367, 2, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20101228 */