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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20090617
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20090617

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
		ADD_HPKT(0x009b, 34, CZ_CHANGE_DIRECTION);
		ADD_HPKT(0x0072, 25, CZ_ENTER);
		ADD_HPKT(0x009f, 20, CZ_ITEM_PICKUP);
		ADD_HPKT(0x02e4, 11, CZ_ITEM_PICKUP_NEW_JAPEN);
		ADD_HPKT(0x00a2, 15, CZ_ITEM_THROW);
		ADD_HPKT(0x00f5, 11, CZ_MOVE_ITEM_FROM_STORE_TO_BODY);
		ADD_HPKT(0x0094, 19, CZ_REQNAME);
		ADD_HPKT(0x0089, 11, CZ_REQUEST_ACT);
		ADD_HPKT(0x0085, 11, CZ_REQUEST_MOVE);
		ADD_HPKT(0x02e5, 9, CZ_REQUEST_MOVE_NEW_JAPEN);
		ADD_HPKT(0x00f7, 22, CZ_REQUEST_TIME);
		ADD_HPKT(0x07dc, 6, CZ_SEEK_PARTY);
		ADD_HPKT(0x07de, 30, CZ_SEEK_PARTY_MEMBER);
		ADD_HPKT(0x02e2, 20, CZ_USE_ITEM_NEW_JAPEN);
		ADD_HPKT(0x0113, 25, CZ_USE_SKILL);
		ADD_HPKT(0x02e3, 25, CZ_USE_SKILL_NEW_JAPEN);
		ADD_HPKT(0x0116, 17, CZ_USE_SKILL_TOGROUND);
		ADD_HPKT(0x0190, 23, CZ_USE_SKILL_TOGROUND_WITHTALKBOX);
		ADD_TPKT(0x07dd, 54, ZC_SEEK_PARTY);
		ADD_TPKT(0x07df, 54, ZC_SEEK_PARTY_MEMBER);
		ADD_TPKT(0x07d9, 268, ZC_SHORTCUT_KEY_LIST_V2);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20090617 */