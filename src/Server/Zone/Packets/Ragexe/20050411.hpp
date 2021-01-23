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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20050411
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20050411

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
		ADD_HPKT(0x009b, 32, CZ_CHANGE_DIRECTION);
		ADD_HPKT(0x0072, 14, CZ_ENTER);
		ADD_HPKT(0x009f, 18, CZ_ITEM_PICKUP);
		ADD_HPKT(0x00a2, 10, CZ_ITEM_THROW);
		ADD_HPKT(0x00f5, 14, CZ_MOVE_ITEM_FROM_STORE_TO_BODY);
		ADD_HPKT(0x0094, 25, CZ_REQNAME);
		ADD_HPKT(0x0089, 14, CZ_REQUEST_ACT);
		ADD_HPKT(0x0085, 18, CZ_REQUEST_MOVE);
		ADD_HPKT(0x00f7, 12, CZ_REQUEST_TIME);
		ADD_HPKT(0x0113, 29, CZ_USE_SKILL);
		ADD_HPKT(0x0116, 19, CZ_USE_SKILL_TOGROUND);
		ADD_HPKT(0x0190, 9, CZ_USE_SKILL_TOGROUND_WITHTALKBOX);
		ADD_TPKT(0x022c, 64, ZC_NOTIFY_MOVEENTRY3);
		ADD_TPKT(0x022b, 57, ZC_NOTIFY_NEWENTRY3);
		ADD_TPKT(0x022a, 58, ZC_NOTIFY_STANDENTRY3);
		ADD_TPKT(0x0229, 15, ZC_STATE_CHANGE3);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20050411 */