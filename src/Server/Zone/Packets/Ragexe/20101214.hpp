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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20101214
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20101214

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
		ADD_HPKT(0x023b, 6, CZ_ACK_STORE_PASSWORD);
		ADD_HPKT(0x0361, 6, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x022d, 2, CZ_COMMAND_MER);
		ADD_HPKT(0x0436, 5, CZ_ENTER2);
		ADD_HPKT(0x07e4, -1, CZ_ITEMLISTWIN_RES);
		ADD_HPKT(0x0362, 90, CZ_ITEM_PICKUP2);
		ADD_HPKT(0x0364, 2, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2);
		ADD_HPKT(0x0802, 36, CZ_PARTY_BOOKING_REQ_REGISTER);
		ADD_HPKT(0x0368, 2, CZ_REQNAME2);
		ADD_HPKT(0x035f, 18, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0360, 2, CZ_REQUEST_TIME2);
		ADD_HPKT(0x0815, 5, CZ_REQ_CLOSE_BUYING_STORE);
		ADD_HPKT(0x0835, 2, CZ_SEARCH_STORE_INFO);
		ADD_HPKT(0x0838, 2, CZ_SEARCH_STORE_INFO_NEXT_PAGE);
		ADD_HPKT(0x083c, 2, CZ_SSILIST_ITEM_CLICK);
		ADD_HPKT(0x0438, 2, CZ_USE_SKILL2);
		ADD_HPKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20101214 */