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

#ifndef HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE_20060109
#define HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE_20060109

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include "Default.hpp"

#include <utility>

namespace Horizon
{
namespace Auth
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
	ClientPacketLengthTable(std::shared_ptr<AuthSession> s)
	: PacketLengthTable(s)
	{
#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_PKT(0x026a, 4, AC_ACK_EKEY_FAIL_AUTHREFUSE);
		ADD_PKT(0x026b, 4, AC_ACK_EKEY_FAIL_INPUTEKEY);
		ADD_PKT(0x026d, 4, AC_ACK_EKEY_FAIL_NEEDCARDPASS);
		ADD_PKT(0x0267, 4, AC_ACK_EKEY_FAIL_NOTEXIST);
		ADD_PKT(0x026c, 4, AC_ACK_EKEY_FAIL_NOTICE);
		ADD_PKT(0x0269, 4, AC_ACK_EKEY_FAIL_NOTUSEDEKEY);
		ADD_PKT(0x0268, 4, AC_ACK_EKEY_FAIL_NOTUSESEKEY);
		ADD_PKT(0x026f, 2, AC_ACK_FIRST_LOGIN);
		ADD_PKT(0x0272, 44, AC_ACK_PT_ID_INFO);
		ADD_PKT(0x0270, 2, AC_REQ_LOGIN_ACCOUNT_INFO);
		ADD_PKT(0x0263, 11, AC_REQ_LOGIN_CARDPASS);
		ADD_PKT(0x0262, 11, AC_REQ_LOGIN_NEWEKEY);
		ADD_PKT(0x0261, 11, AC_REQ_LOGIN_OLDEKEY);
		ADD_PKT(0x0271, 38, CA_ACK_LOGIN_ACCOUNT_INFO);
		ADD_PKT(0x0266, 30, CA_ACK_LOGIN_CARDPASS);
		ADD_PKT(0x0265, 20, CA_ACK_LOGIN_NEWEKEY);
		ADD_PKT(0x0264, 20, CA_ACK_LOGIN_OLDEKEY);
#undef ADD_PKT
	}

	~ClientPacketLengthTable() { }

};
}
}
#endif /* HORIZON_AUTH_CLIENT_PACKET_LENGTH_TABLE_20060109 */
