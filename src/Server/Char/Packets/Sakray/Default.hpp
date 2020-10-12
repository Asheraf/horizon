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

#ifndef HORIZON_CHAR_PACKET_LENGTH_TABLE
#define HORIZON_CHAR_PACKET_LENGTH_TABLE

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Default.hpp"

#include <utility>
#include <memory>

#include "Server/Char/Packets/CH_DELETE_CHAR.hpp"
#include "Server/Char/Packets/CH_DELETE_CHAR2.hpp"
#include "Server/Char/Packets/CH_ENTER.hpp"
#include "Server/Char/Packets/CH_MAKE_CHAR.hpp"
#include "Server/Char/Packets/CH_REQ_CHANGE_CHARNAME.hpp"
#include "Server/Char/Packets/CH_REQ_IS_VALID_CHARNAME.hpp"
#include "Server/Char/Packets/CH_SELECT_CHAR.hpp"
#include "Server/Char/Packets/CH_SELECT_CHAR_GOINGTOBEUSED.hpp"
#include "Server/Char/Packets/CH_UNKNOWN_PING.hpp"
#include "Server/Char/Packets/HC_ACCEPT_DELETECHAR.hpp"
#include "Server/Char/Packets/HC_ACCEPT_ENTER.hpp"
#include "Server/Char/Packets/HC_ACCEPT_MAKECHAR.hpp"
#include "Server/Char/Packets/HC_ACK_CHANGE_CHARNAME.hpp"
#include "Server/Char/Packets/HC_ACK_IS_VALID_CHARNAME.hpp"
#include "Server/Char/Packets/HC_BLOCK_CHARACTER.hpp"
#include "Server/Char/Packets/HC_CHARNOTBEENSELECTED.hpp"
#include "Server/Char/Packets/HC_NOTIFY_ZONESVR.hpp"
#include "Server/Char/Packets/HC_REFUSE_DELETECHAR.hpp"
#include "Server/Char/Packets/HC_REFUSE_ENTER.hpp"
#include "Server/Char/Packets/HC_REFUSE_MAKECHAR.hpp"
#include "Server/Char/Packets/HC_REFUSE_SELECTCHAR.hpp"
#include "Server/Char/Packets/HC_REQUEST_CHARACTER_PASSWORD.hpp"


namespace Horizon
{
namespace Char
{
	typedef std::shared_ptr<Base::NetworkPacket<CharSocket>> PacketStructPtrType;
	typedef std::pair<uint16_t, PacketStructPtrType> PacketTablePairType;

/**
 * @brief Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class PacketLengthTable
{
public:
	PacketLengthTable(std::shared_ptr<CharSocket> sock)
	: _socket(sock)
	{
#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair(j, std::make_shared<k>(sock)))
		ADD_PKT(0x0068, 46, CH_DELETE_CHAR);
		ADD_PKT(0x01fb, 56, CH_DELETE_CHAR2);
		ADD_PKT(0x0065, 17, CH_ENTER);
		ADD_PKT(0x0067, 37, CH_MAKE_CHAR);
		ADD_PKT(0x028f, 6, CH_REQ_CHANGE_CHARNAME);
		ADD_PKT(0x028d, 34, CH_REQ_IS_VALID_CHARNAME);
		ADD_PKT(0x0066, 3, CH_SELECT_CHAR);
		ADD_PKT(0x028c, 46, CH_SELECT_CHAR_GOINGTOBEUSED);
		ADD_PKT(0x0187, 6, CH_UNKNOWN_PING);
		ADD_PKT(0x006f, 2, HC_ACCEPT_DELETECHAR);
		ADD_PKT(0x006b, -1, HC_ACCEPT_ENTER);
		ADD_PKT(0x006d, 110, HC_ACCEPT_MAKECHAR);
		ADD_PKT(0x0290, 4, HC_ACK_CHANGE_CHARNAME);
		ADD_PKT(0x028e, 4, HC_ACK_IS_VALID_CHARNAME);
		ADD_PKT(0x020d, -1, HC_BLOCK_CHARACTER);
		ADD_PKT(0x028b, -1, HC_CHARNOTBEENSELECTED);
		ADD_PKT(0x0071, 28, HC_NOTIFY_ZONESVR);
		ADD_PKT(0x0070, 3, HC_REFUSE_DELETECHAR);
		ADD_PKT(0x006c, 3, HC_REFUSE_ENTER);
		ADD_PKT(0x006e, 3, HC_REFUSE_MAKECHAR);
		ADD_PKT(0x02ca, 3, HC_REFUSE_SELECTCHAR);
		ADD_PKT(0x023e, 8, HC_REQUEST_CHARACTER_PASSWORD);
#undef ADD_PKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<CharSocket> get_socket() { return _socket.lock(); }

	PacketTablePairType get_packet_info(uint16_t packet_id) { return _packet_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, PacketTablePairType> _packet_length_table;
	std::weak_ptr<CharSocket> _socket;

};
}
}
#endif /* HORIZON_CHAR_PACKET_LENGTH_TABLE */