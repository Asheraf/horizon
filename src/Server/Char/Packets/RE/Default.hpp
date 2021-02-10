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

#ifndef HORIZON_CHAR_RE_PACKET_LENGTH_TABLE
#define HORIZON_CHAR_RE_PACKET_LENGTH_TABLE

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Server/Char/Packets/HandledPackets.hpp"
#include "Server/Char/Packets/TransmittedPackets.hpp"

#include <utility>
#include <memory>


namespace Horizon
{
namespace Char
{
	typedef std::shared_ptr<Base::NetworkPacketHandler<CharSession>> HPacketStructPtrType;
	typedef std::shared_ptr<Base::NetworkPacketTransmitter<CharSession>> TPacketStructPtrType;
	typedef std::pair<int16_t, HPacketStructPtrType> HPacketTablePairType;
	typedef std::pair<int16_t, TPacketStructPtrType> TPacketTablePairType;

/**
 * @brief Packet Length Table object that stores
 * the packet length of each packet of this client version.
 * The data is stored in a thread-safe lookup table.
 * RAII techinque ensures that the table is populated on instantiation.
 */
class PacketLengthTable
{
public:
	PacketLengthTable(std::shared_ptr<CharSession> s)
	: _session(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_HPKT(0x08fd, 6, CH_ACK_CHANGE_CHARACTERNAME);
		ADD_HPKT(0x08c5, 6, CH_AVAILABLE_SECOND_PASSWD);
		ADD_HPKT(0x09a1, 2, CH_CHARLIST_REQ);
		ADD_HPKT(0x07e7, 32, CH_CHECKBOT);
		ADD_HPKT(0x0068, 46, CH_DELETE_CHAR);
		ADD_HPKT(0x01fb, 56, CH_DELETE_CHAR2);
		ADD_HPKT(0x0829, 12, CH_DELETE_CHAR3);
		ADD_HPKT(0x082b, 6, CH_DELETE_CHAR3_CANCEL);
		ADD_HPKT(0x098f, -1, CH_DELETE_CHAR3_EXT);
		ADD_HPKT(0x0827, 6, CH_DELETE_CHAR3_RESERVED);
		ADD_HPKT(0x08bc, 10, CH_DELETE_SECOND_PASSWD);
		ADD_HPKT(0x08be, 14, CH_EDIT_SECOND_PASSWD);
		ADD_HPKT(0x0065, 17, CH_ENTER);
		ADD_HPKT(0x0275, 37, CH_ENTER2);
		ADD_HPKT(0x07e5, 4, CH_ENTER_CHECKBOT);
		ADD_HPKT(0x0a39, 36, CH_MAKE_CHAR);
		ADD_HPKT(0x0970, 31, CH_MAKE_CHAR_NOT_STATS);
		ADD_HPKT(0x08ba, 10, CH_MAKE_SECOND_PASSWD);
		ADD_HPKT(0x08c3, 10, CH_NOT_AVAILABLE_SECOND_PASSWD);
		ADD_HPKT(0x08fc, 30, CH_REQ_CHANGE_CHARACTERNAME);
		ADD_HPKT(0x08d4, 8, CH_REQ_CHANGE_CHARACTER_SLOT);
		ADD_HPKT(0x028f, 6, CH_REQ_CHANGE_CHARNAME);
		ADD_HPKT(0x099c, 6, CH_REQ_CHARINFO_PER_PAGE);
		ADD_HPKT(0x028d, 34, CH_REQ_IS_VALID_CHARNAME);
		ADD_HPKT(0x08b8, 10, CH_SECOND_PASSWD_ACK);
		ADD_HPKT(0x0841, 4, CH_SELECT_ACCESSIBLE_MAPNAME);
		ADD_HPKT(0x0066, 3, CH_SELECT_CHAR);
		ADD_HPKT(0x028c, 46, CH_SELECT_CHAR_GOINGTOBEUSED);
		ADD_HPKT(0x0187, 6, CH_UNKNOWN_PING);
		ADD_HPKT(0x08b0, 17, CH_WAITING_LOGIN);
		ADD_TPKT(0x006f, 2, HC_ACCEPT_DELETECHAR);
		ADD_TPKT(0x006b, -1, HC_ACCEPT_ENTER);
		ADD_TPKT(0x082d, -1, HC_ACCEPT_ENTER2);
		ADD_TPKT(0x006d, 157, HC_ACCEPT_MAKECHAR);
		ADD_TPKT(0x08d5, -1, HC_ACK_CHANGE_CHARACTER_SLOT);
		ADD_TPKT(0x0290, 4, HC_ACK_CHANGE_CHARNAME);
		ADD_TPKT(0x099d, -1, HC_ACK_CHARINFO_PER_PAGE);
		ADD_TPKT(0x028e, 4, HC_ACK_IS_VALID_CHARNAME);
		ADD_TPKT(0x08c6, 4, HC_AVAILABLE_SECOND_PASSWD);
		ADD_TPKT(0x020d, -1, HC_BLOCK_CHARACTER);
		ADD_TPKT(0x0448, -1, HC_CHARACTER_LIST);
		ADD_TPKT(0x09a0, 6, HC_CHARLIST_NOTIFY);
		ADD_TPKT(0x028b, -1, HC_CHARNOTBEENSELECTED);
		ADD_TPKT(0x07e8, -1, HC_CHECKBOT);
		ADD_TPKT(0x07e9, 5, HC_CHECKBOT_RESULT);
		ADD_TPKT(0x082a, 10, HC_DELETE_CHAR3);
		ADD_TPKT(0x082c, 10, HC_DELETE_CHAR3_CANCEL);
		ADD_TPKT(0x0828, 14, HC_DELETE_CHAR3_RESERVED);
		ADD_TPKT(0x08bd, 8, HC_DELETE_SECOND_PASSWD);
		ADD_TPKT(0x08bf, 8, HC_EDIT_SECOND_PASSWD);
		ADD_TPKT(0x08bb, 8, HC_MAKE_SECOND_PASSWD);
		ADD_TPKT(0x0840, -1, HC_NOTIFY_ACCESSIBLE_MAPNAME);
		ADD_TPKT(0x0ac5, 156, HC_NOTIFY_ZONESVR);
		ADD_TPKT(0x0071, 28, HC_NOTIFY_ZONESVR);
		ADD_TPKT(0x08c4, 8, HC_NOT_AVAILABLE_SECOND_PASSWD);
		ADD_TPKT(0x099e, 12, HC_QUEUE_ORDER);
		ADD_TPKT(0x0070, 3, HC_REFUSE_DELETECHAR);
		ADD_TPKT(0x006c, 3, HC_REFUSE_ENTER);
		ADD_TPKT(0x006e, 3, HC_REFUSE_MAKECHAR);
		ADD_TPKT(0x02ca, 3, HC_REFUSE_SELECTCHAR);
		ADD_TPKT(0x023e, 8, HC_REQUEST_CHARACTER_PASSWORD);
		ADD_TPKT(0x0ae9, 13, HC_SECOND_PASSWD_LOGIN);
		ADD_TPKT(0x09c2, -1, HC_SECRETSCAN_DATA);
		ADD_TPKT(0x08e3, 157, HC_UPDATE_CHARINFO);
		ADD_TPKT(0x08af, 10, HC_WAITING_LOGIN);
#undef ADD_HPKT
#undef ADD_TPKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<CharSession> get_session() { return _session.lock(); }

	HPacketTablePairType get_hpacket_info(uint16_t packet_id) { return _hpacket_length_table.at(packet_id); }
	TPacketTablePairType get_tpacket_info(uint16_t packet_id) { return _tpacket_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, HPacketTablePairType> _hpacket_length_table;
	LockedLookupTable<uint16_t, TPacketTablePairType> _tpacket_length_table;
	std::weak_ptr<CharSession> _session;

};
}
}
#endif /* HORIZON_CHAR_RE_PACKET_LENGTH_TABLE */
