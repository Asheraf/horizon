/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20100309
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20100309

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Zone
{
namespace ShufflePackets
{
/**
 * @brief Shuffle Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * Packets with IDs already existent in the database are over-written.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class ShufflePacketLengthTable : public PacketLengthTable
{
public:
	ShufflePacketLengthTable()
	{
		std::shared_ptr<ZoneSocket> sock = get_socket();

#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair<uint16_t, NetworkPacket>(j, k))
		ADD_PKT(0x0815, 6, CZ_REQ_CLOSE_BUYING_STORE(sock));
		ADD_PKT(0x0819, 10, CZ_REQ_TRADE_BUYING_STORE(sock));
		ADD_PKT(0x0818, -1, ZC_ACK_ITEMLIST_BUYING_STORE(sock));
		ADD_PKT(0x0814, 2, ZC_BUYING_STORE_ENTRY(sock));
		ADD_PKT(0x0816, 6, ZC_DISAPPEAR_BUYING_STORE_ENTRY(sock));
		ADD_PKT(0x081d, 22, ZC_EL_INIT(sock));
		ADD_PKT(0x081e, 8, ZC_EL_PAR_CHANGE(sock));
		ADD_PKT(0x081a, 4, ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER(sock));
		ADD_PKT(0x081c, 6, ZC_ITEM_DELETE_BUYING_STORE(sock));
		ADD_PKT(0x0813, -1, ZC_MYITEMLIST_BUYING_STORE(sock));
		ADD_PKT(0x081b, 4, ZC_UPDATE_ITEM_FROM_BUYING_STORE(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20100309 */