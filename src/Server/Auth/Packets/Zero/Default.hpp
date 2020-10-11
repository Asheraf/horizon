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

#ifndef HORIZON_AUTH_PACKET_LENGTH_TABLE
#define HORIZON_AUTH_PACKET_LENGTH_TABLE

#include "Server/Common/Base/NetworkPacket.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Default.hpp"

#include <utility>
#include <memory>

#include "Server/Auth/Packets/AC_ACCEPT_LOGIN.hpp"
#include "Server/Auth/Packets/AC_ACCEPT_LOGIN2.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_AUTHREFUSE.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_INPUTEKEY.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_NEEDCARDPASS.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_NOTEXIST.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_NOTICE.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_NOTUSEDEKEY.hpp"
#include "Server/Auth/Packets/AC_ACK_EKEY_FAIL_NOTUSESEKEY.hpp"
#include "Server/Auth/Packets/AC_ACK_FIRST_LOGIN.hpp"
#include "Server/Auth/Packets/AC_ACK_GAME_GUARD.hpp"
#include "Server/Auth/Packets/AC_ACK_HASH.hpp"
#include "Server/Auth/Packets/AC_ACK_PT_ID_INFO.hpp"
#include "Server/Auth/Packets/AC_ASK_PNGAMEROOM.hpp"
#include "Server/Auth/Packets/AC_EVENT_RESULT.hpp"
#include "Server/Auth/Packets/AC_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/AC_NOTIFY_ERROR.hpp"
#include "Server/Auth/Packets/AC_OTP_AUTH_ACK.hpp"
#include "Server/Auth/Packets/AC_OTP_USER.hpp"
#include "Server/Auth/Packets/AC_REALNAME_AUTH.hpp"
#include "Server/Auth/Packets/AC_REFUSE_LOGIN.hpp"
#include "Server/Auth/Packets/AC_REFUSE_LOGIN2.hpp"
#include "Server/Auth/Packets/AC_REFUSE_LOGIN3.hpp"
#include "Server/Auth/Packets/AC_REQUEST_SECOND_PASSWORD.hpp"
#include "Server/Auth/Packets/AC_REQ_LOGIN_ACCOUNT_INFO.hpp"
#include "Server/Auth/Packets/AC_REQ_LOGIN_CARDPASS.hpp"
#include "Server/Auth/Packets/AC_REQ_LOGIN_NEWEKEY.hpp"
#include "Server/Auth/Packets/AC_REQ_LOGIN_OLDEKEY.hpp"
#include "Server/Auth/Packets/AC_REQ_MOBILE_OTP.hpp"
#include "Server/Auth/Packets/AC_REQ_NEW_USER.hpp"
#include "Server/Auth/Packets/AC_SHUTDOWN_INFO.hpp"
#include "Server/Auth/Packets/AC_SHUTDOWN_NOTIFY.hpp"
#include "Server/Auth/Packets/CA_ACK_LOGIN_ACCOUNT_INFO.hpp"
#include "Server/Auth/Packets/CA_ACK_LOGIN_CARDPASS.hpp"
#include "Server/Auth/Packets/CA_ACK_LOGIN_NEWEKEY.hpp"
#include "Server/Auth/Packets/CA_ACK_LOGIN_OLDEKEY.hpp"
#include "Server/Auth/Packets/CA_ACK_MOBILE_OTP.hpp"
#include "Server/Auth/Packets/CA_ACK_NEW_USER.hpp"
#include "Server/Auth/Packets/CA_CLIENT_TYPE.hpp"
#include "Server/Auth/Packets/CA_CONNECT_INFO_CHANGED.hpp"
#include "Server/Auth/Packets/CA_EXE_HASHCHECK.hpp"
#include "Server/Auth/Packets/CA_LOGIN.hpp"
#include "Server/Auth/Packets/CA_LOGIN2.hpp"
#include "Server/Auth/Packets/CA_LOGIN3.hpp"
#include "Server/Auth/Packets/CA_LOGIN4.hpp"
#include "Server/Auth/Packets/CA_LOGIN5.hpp"
#include "Server/Auth/Packets/CA_LOGIN6.hpp"
#include "Server/Auth/Packets/CA_LOGIN_HAN.hpp"
#include "Server/Auth/Packets/CA_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/CA_LOGIN_PCBANG.hpp"
#include "Server/Auth/Packets/CA_OTP_AUTH_REQ.hpp"
#include "Server/Auth/Packets/CA_OTP_CODE.hpp"
#include "Server/Auth/Packets/CA_REPLY_PNGAMEROOM.hpp"
#include "Server/Auth/Packets/CA_REQ_GAME_GUARD_CHECK.hpp"
#include "Server/Auth/Packets/CA_REQ_HASH.hpp"
#include "Server/Auth/Packets/CA_SSO_LOGIN_REQ.hpp"


namespace Horizon
{
	typedef std::shared_ptr<Base::NetworkPacket<AuthSocket>> PacketStructPtrType;
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
	PacketLengthTable(std::shared_ptr<AuthSocket> sock)
	: _socket(sock)
	{
#define ADD_PKT(i, j, k) _packet_length_table.insert(i, std::make_pair(j, std::make_shared<k>(sock)))
		ADD_PKT(0x0ac4, -1, AC_ACCEPT_LOGIN);
		ADD_PKT(0x0276, -1, AC_ACCEPT_LOGIN2);
		ADD_PKT(0x026a, 4, AC_ACK_EKEY_FAIL_AUTHREFUSE);
		ADD_PKT(0x026b, 4, AC_ACK_EKEY_FAIL_INPUTEKEY);
		ADD_PKT(0x026d, 4, AC_ACK_EKEY_FAIL_NEEDCARDPASS);
		ADD_PKT(0x0267, 4, AC_ACK_EKEY_FAIL_NOTEXIST);
		ADD_PKT(0x026c, 4, AC_ACK_EKEY_FAIL_NOTICE);
		ADD_PKT(0x0269, 4, AC_ACK_EKEY_FAIL_NOTUSEDEKEY);
		ADD_PKT(0x0268, 4, AC_ACK_EKEY_FAIL_NOTUSESEKEY);
		ADD_PKT(0x026f, 2, AC_ACK_FIRST_LOGIN);
		ADD_PKT(0x0259, 3, AC_ACK_GAME_GUARD);
		ADD_PKT(0x01dc, -1, AC_ACK_HASH);
		ADD_PKT(0x0272, 44, AC_ACK_PT_ID_INFO);
		ADD_PKT(0x01be, 2, AC_ASK_PNGAMEROOM);
		ADD_PKT(0x023d, 6, AC_EVENT_RESULT);
		ADD_PKT(0x0ae3, -1, AC_LOGIN_OTP);
		ADD_PKT(0x01f1, -1, AC_NOTIFY_ERROR);
		ADD_PKT(0x0823, -1, AC_OTP_AUTH_ACK);
		ADD_PKT(0x0821, 2, AC_OTP_USER);
		ADD_PKT(0x08b2, -1, AC_REALNAME_AUTH);
		ADD_PKT(0x006a, 23, AC_REFUSE_LOGIN);
		ADD_PKT(0x083e, 26, AC_REFUSE_LOGIN2);
		ADD_PKT(0x09a5, 7, AC_REFUSE_LOGIN3);
		ADD_PKT(0x02ad, 8, AC_REQUEST_SECOND_PASSWORD);
		ADD_PKT(0x0270, 2, AC_REQ_LOGIN_ACCOUNT_INFO);
		ADD_PKT(0x0263, 11, AC_REQ_LOGIN_CARDPASS);
		ADD_PKT(0x0262, 11, AC_REQ_LOGIN_NEWEKEY);
		ADD_PKT(0x0261, 11, AC_REQ_LOGIN_OLDEKEY);
		ADD_PKT(0x09a2, 6, AC_REQ_MOBILE_OTP);
		ADD_PKT(0x098b, 2, AC_REQ_NEW_USER);
		ADD_PKT(0x08e4, 6, AC_SHUTDOWN_INFO);
		ADD_PKT(0x0986, 10, AC_SHUTDOWN_NOTIFY);
		ADD_PKT(0x0271, 40, CA_ACK_LOGIN_ACCOUNT_INFO);
		ADD_PKT(0x0266, 30, CA_ACK_LOGIN_CARDPASS);
		ADD_PKT(0x0265, 20, CA_ACK_LOGIN_NEWEKEY);
		ADD_PKT(0x0264, 20, CA_ACK_LOGIN_OLDEKEY);
		ADD_PKT(0x09a3, -1, CA_ACK_MOBILE_OTP);
		ADD_PKT(0x098c, 4, CA_ACK_NEW_USER);
		ADD_PKT(0x027f, 8, CA_CLIENT_TYPE);
		ADD_PKT(0x0200, 26, CA_CONNECT_INFO_CHANGED);
		ADD_PKT(0x0204, 18, CA_EXE_HASHCHECK);
		ADD_PKT(0x0064, 55, CA_LOGIN);
		ADD_PKT(0x01dd, 47, CA_LOGIN2);
		ADD_PKT(0x01fa, 48, CA_LOGIN3);
		ADD_PKT(0x027c, 60, CA_LOGIN4);
		ADD_PKT(0x08cc, 109, CA_LOGIN5);
		ADD_PKT(0x0987, -1, CA_LOGIN6);
		ADD_PKT(0x02b0, 85, CA_LOGIN_HAN);
		ADD_PKT(0x0acf, 68, CA_LOGIN_OTP);
		ADD_PKT(0x0277, 84, CA_LOGIN_PCBANG);
		ADD_PKT(0x0822, 9, CA_OTP_AUTH_REQ);
		ADD_PKT(0x0ad0, 11, CA_OTP_CODE);
		ADD_PKT(0x01bf, 3, CA_REPLY_PNGAMEROOM);
		ADD_PKT(0x0258, 2, CA_REQ_GAME_GUARD_CHECK);
		ADD_PKT(0x01db, 2, CA_REQ_HASH);
		ADD_PKT(0x0825, -1, CA_SSO_LOGIN_REQ);
#undef ADD_PKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<AuthSocket> get_socket() { return _socket.lock(); }

	PacketTablePairType get_packet_info(uint16_t packet_id) { return _packet_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, PacketTablePairType> _packet_length_table;
	std::weak_ptr<AuthSocket> _socket;

};
}
#endif /* HORIZON_AUTH_PACKET_LENGTH_TABLE */