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

#ifndef HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090929
#define HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090929

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
		ADD_PKT(0x07ea, 2, CZ_BATTLE_FIELD_LIST(sock));
		ADD_PKT(0x07ee, 6, CZ_CANCEL_BATTLE_FIELD(sock));
		ADD_PKT(0x07ec, 6, CZ_JOIN_BATTLE_FIELD(sock));
		ADD_PKT(0x07f0, 8, CZ_REQ_BATTLE_STATE_MONITOR(sock));
		ADD_PKT(0x07f1, 15, ZC_ACK_BATTLE_STATE_MONITOR(sock));
		ADD_PKT(0x07eb, -1, ZC_BATTLE_FIELD_LIST(sock));
		ADD_PKT(0x07f3, 3, ZC_BATTLE_JOIN_NOTI_DEFER(sock));
		ADD_PKT(0x07f2, 4, ZC_BATTLE_NOTI_START_STEP(sock));
		ADD_PKT(0x07ef, 8, ZC_CANCEL_BATTLE_FIELD(sock));
		ADD_PKT(0x07ed, 8, ZC_JOIN_BATTLE_FIELD(sock));
#undef ADD_PKT
	}

	~ShufflePacketLengthTable() { }

};
}
}
}
#endif /* HORIZON_ZONE_SHUFFLE_PACKET_LENGTH_TABLE_20090929 */