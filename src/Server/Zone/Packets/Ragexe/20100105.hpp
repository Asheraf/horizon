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

#ifndef HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20100105
#define HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20100105

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
		ADD_HPKT(0x023b, 36, CZ_ACK_STORE_PASSWORD);
		ADD_HPKT(0x0202, 26, CZ_ADD_FRIENDS);
		ADD_HPKT(0x0361, -1, CZ_CHANGE_DIRECTION2);
		ADD_HPKT(0x022d, 5, CZ_COMMAND_MER);
		ADD_HPKT(0x0436, 19, CZ_ENTER2);
		ADD_HPKT(0x07d4, 4, CZ_ES_CANCEL);
		ADD_HPKT(0x07d3, 4, CZ_ES_CHOOSE);
		ADD_HPKT(0x07d1, 2, CZ_ES_GET_LIST);
		ADD_HPKT(0x0281, 4, CZ_GANGSI_RANK);
		ADD_HPKT(0x02f6, -1, CZ_IRMAIL_LIST);
		ADD_HPKT(0x02f3, -1, CZ_IRMAIL_SEND);
		ADD_HPKT(0x07e4, -1, CZ_ITEMLISTWIN_RES);
		ADD_HPKT(0x0362, -1, CZ_ITEM_PICKUP2);
		ADD_HPKT(0x0363, -1, CZ_ITEM_THROW2);
		ADD_HPKT(0x07ec, 8, CZ_JOIN_BATTLE_FIELD);
		ADD_HPKT(0x0364, -1, CZ_MOVE_ITEM_FROM_BODY_TO_STORE2);
		ADD_HPKT(0x0365, -1, CZ_MOVE_ITEM_FROM_STORE_TO_BODY2);
		ADD_HPKT(0x0802, 18, CZ_PARTY_BOOKING_REQ_REGISTER);
		ADD_HPKT(0x02c4, 26, CZ_PARTY_JOIN_REQ);
		ADD_HPKT(0x0288, 10, CZ_PC_BUY_CASH_POINT_ITEM);
		ADD_HPKT(0x0368, -1, CZ_REQNAME2);
		ADD_HPKT(0x0369, -1, CZ_REQNAME_BYGID2);
		ADD_HPKT(0x0437, 7, CZ_REQUEST_ACT2);
		ADD_HPKT(0x035f, -1, CZ_REQUEST_MOVE2);
		ADD_HPKT(0x0360, -1, CZ_REQUEST_TIME2);
		ADD_HPKT(0x07f0, 8, CZ_REQ_BATTLE_STATE_MONITOR);
		ADD_HPKT(0x0438, 10, CZ_USE_SKILL2);
		ADD_HPKT(0x0366, -1, CZ_USE_SKILL_TOGROUND2);
		ADD_HPKT(0x0367, -1, CZ_USE_SKILL_TOGROUND_WITHTALKBOX2);
		ADD_TPKT(0x07f1, 15, ZC_ACK_BATTLE_STATE_MONITOR);
		ADD_TPKT(0x0158, -1, ZC_ACK_OPEN_MEMBER_INFO);
		ADD_TPKT(0x07f3, 4, ZC_BATTLE_JOIN_NOTI_DEFER);
		ADD_TPKT(0x07f2, 6, ZC_BATTLE_NOTI_START_STEP);
		ADD_TPKT(0x07d6, 4, ZC_ES_GOTO);
		ADD_TPKT(0x07d2, -1, ZC_ES_LIST);
		ADD_TPKT(0x07d5, 4, ZC_ES_READY);
		ADD_TPKT(0x07d0, 6, ZC_ES_RESULT);
		ADD_TPKT(0x02f5, -1, ZC_IRMAIL_NOTIFY);
		ADD_TPKT(0x02f4, -1, ZC_IRMAIL_SEND_RES);
		ADD_TPKT(0x00aa, 7, ZC_REQ_WEAR_EQUIP_ACK);
		ADD_TPKT(0x0442, 8, ZC_SKILL_SELECT_REQUEST);
#undef ADD_TPKT
#undef ADD_HPKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_ZONE_CLIENT_PACKET_LENGTH_TABLE_20100105 */