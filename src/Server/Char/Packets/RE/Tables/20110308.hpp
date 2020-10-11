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

#ifndef HORIZON_CHAR_SHUFFLE_PACKET_LENGTH_TABLE_20110308
#define HORIZON_CHAR_SHUFFLE_PACKET_LENGTH_TABLE_20110308

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
		ADD_PKT(0x08c5, 6, CH_AVAILABLE_SECOND_PASSWD(sock));
		ADD_PKT(0x08bc, 10, CH_DELETE_SECOND_PASSWD(sock));
		ADD_PKT(0x08be, 14, CH_EDIT_SECOND_PASSWD(sock));
		ADD_PKT(0x08ba, 10, CH_MAKE_SECOND_PASSWD(sock));
		ADD_PKT(0x08c3, 10, CH_NOT_AVAILABLE_SECOND_PASSWD(sock));
		ADD_PKT(0x08b8, 10, CH_SECOND_PASSWD_ACK(sock));
		ADD_PKT(0x08bf, 8, HC_EDIT_SECOND_PASSWD(sock));
		ADD_PKT(0x08bb, 8, HC_MAKE_SECOND_PASSWD(sock));
		ADD_PKT(0x08c4, 8, HC_NOT_AVAILABLE_SECOND_PASSWD(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_CHAR_SHUFFLE_PACKET_LENGTH_TABLE_20110308 */