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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20040705
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20040705

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
		ADD_HPKT(0x0208, 14, CZ_ACK_REQ_ADD_FRIENDS);
		ADD_HPKT(0x0202, 26, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0203, 10, CZ_DELETE_FRIENDS);
		ADD_HPKT(0x0072, 22, CZ_ENTER);
		ADD_HPKT(0x0085, 8, CZ_REQUEST_MOVE);
		ADD_HPKT(0x0113, 15, CZ_USE_SKILL);
		ADD_HPKT(0x0116, 15, CZ_USE_SKILL_TOGROUND);
		ADD_HPKT(0x0190, 95, CZ_USE_SKILL_TOGROUND_WITHTALKBOX);
		ADD_TPKT(0x0209, 36, ZC_ADD_FRIENDS_LIST);
		ADD_TPKT(0x020a, 10, ZC_DELETE_FRIENDS);
		ADD_TPKT(0x0201, -1, ZC_FRIENDS_LIST);
		ADD_TPKT(0x0206, 11, ZC_FRIENDS_STATE);
		ADD_TPKT(0x0207, 34, ZC_REQ_ADD_FRIENDS);
		ADD_TPKT(0x020e, 24, ZC_STARSKILL);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20040705 */