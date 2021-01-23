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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20041129
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20041129

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
		ADD_HPKT(0x009b, 2, CZ_CHANGE_DIRECTION);
		ADD_HPKT(0x0072, 26, CZ_ENTER);
		ADD_HPKT(0x009f, 20, CZ_ITEM_PICKUP);
		ADD_HPKT(0x00a2, 9, CZ_ITEM_THROW);
		ADD_HPKT(0x00f5, 32, CZ_MOVE_ITEM_FROM_STORE_TO_BODY);
		ADD_HPKT(0x0094, 20, CZ_REQNAME);
		ADD_HPKT(0x0193, 21, CZ_REQNAME_BYGID);
		ADD_HPKT(0x0089, 9, CZ_REQUEST_ACT);
		ADD_HPKT(0x00f3, 23, CZ_REQUEST_CHAT);
		ADD_HPKT(0x0085, -1, CZ_REQUEST_MOVE);
		ADD_HPKT(0x00f7, 11, CZ_REQUEST_TIME);
		ADD_HPKT(0x0222, 6, CZ_REQ_WEAPONREFINE);
		ADD_HPKT(0x0113, 114, CZ_USE_SKILL);
		ADD_HPKT(0x0116, 20, CZ_USE_SKILL_TOGROUND);
		ADD_HPKT(0x0190, 17, CZ_USE_SKILL_TOGROUND_WITHTALKBOX);
		ADD_TPKT(0x0223, 8, ZC_ACK_WEAPONREFINE);
		ADD_TPKT(0x0221, -1, ZC_NOTIFY_WEAPONITEMLIST);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20041129 */