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

#ifndef HORIZON_CHAR_SHUFFLE_PACKET_LENGTH_TABLE_20100713
#define HORIZON_CHAR_SHUFFLE_PACKET_LENGTH_TABLE_20100713

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Char
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
		std::shared_ptr<CharSocket> sock = get_socket();

#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair<uint16_t, NetworkPacket>(j, k))
		ADD_PKT(0x0829, 6, CH_DELETE_CHAR3(sock));
		ADD_PKT(0x082b, 6, CH_DELETE_CHAR3_CANCEL(sock));
		ADD_PKT(0x0827, 6, CH_DELETE_CHAR3_RESERVED(sock));
		ADD_PKT(0x0841, 19, CH_SELECT_ACCESSIBLE_MAPNAME(sock));
		ADD_PKT(0x082a, 10, HC_DELETE_CHAR3(sock));
		ADD_PKT(0x082c, 14, HC_DELETE_CHAR3_CANCEL(sock));
		ADD_PKT(0x0828, 14, HC_DELETE_CHAR3_RESERVED(sock));
		ADD_PKT(0x0840, -1, HC_NOTIFY_ACCESSIBLE_MAPNAME(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_CHAR_SHUFFLE_PACKET_LENGTH_TABLE_20100713 */