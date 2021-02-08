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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_LENGTH_TABLE
#define HORIZON_AUTH_RAGEXE_PACKET_LENGTH_TABLE

#include "Core/Multithreading/LockedLookupTable.hpp"
#include "Server/Auth/Packets/HandledPackets.hpp"
#include "Server/Auth/Packets/TransmittedPackets.hpp"

#include <utility>
#include <memory>


namespace Horizon
{
namespace Auth
{
	typedef std::shared_ptr<Base::NetworkPacketHandler<AuthSession>> HPacketStructPtrType;
	typedef std::shared_ptr<Base::NetworkPacketTransmitter<AuthSession>> TPacketStructPtrType;
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
	PacketLengthTable(std::shared_ptr<AuthSession> s)
	: _session(s)
	{
#define ADD_HPKT(i, j, k) _hpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
#define ADD_TPKT(i, j, k) _tpacket_length_table.insert(i, std::make_pair(j, std::make_shared<k>(s)))
		ADD_TPKT(0x0ac4, -1, AC_ACCEPT_LOGIN);
		ADD_TPKT(0x0276, -1, AC_ACCEPT_LOGIN2);
		ADD_TPKT(0x026a, 4, AC_ACK_EKEY_FAIL_AUTHREFUSE);
		ADD_TPKT(0x026b, 4, AC_ACK_EKEY_FAIL_INPUTEKEY);
		ADD_TPKT(0x026d, 4, AC_ACK_EKEY_FAIL_NEEDCARDPASS);
		ADD_TPKT(0x0267, 4, AC_ACK_EKEY_FAIL_NOTEXIST);
		ADD_TPKT(0x026c, 4, AC_ACK_EKEY_FAIL_NOTICE);
		ADD_TPKT(0x0269, 4, AC_ACK_EKEY_FAIL_NOTUSEDEKEY);
		ADD_TPKT(0x0268, 4, AC_ACK_EKEY_FAIL_NOTUSESEKEY);
		ADD_TPKT(0x026f, 2, AC_ACK_FIRST_LOGIN);
		ADD_TPKT(0x0259, 3, AC_ACK_GAME_GUARD);
		ADD_TPKT(0x01dc, -1, AC_ACK_HASH);
		ADD_TPKT(0x0272, 44, AC_ACK_PT_ID_INFO);
		ADD_TPKT(0x01be, 2, AC_ASK_PNGAMEROOM);
		ADD_TPKT(0x023d, 6, AC_EVENT_RESULT);
		ADD_TPKT(0x0ae3, -1, AC_LOGIN_OTP);
		ADD_TPKT(0x01f1, -1, AC_NOTIFY_ERROR);
		ADD_TPKT(0x0823, -1, AC_OTP_AUTH_ACK);
		ADD_TPKT(0x0821, 2, AC_OTP_USER);
		ADD_TPKT(0x08b2, -1, AC_REALNAME_AUTH);
		ADD_TPKT(0x006a, 23, AC_REFUSE_LOGIN);
		ADD_TPKT(0x083e, 26, AC_REFUSE_LOGIN2);
		ADD_TPKT(0x09a5, 7, AC_REFUSE_LOGIN3);
		ADD_TPKT(0x0b02, 26, AC_REFUSE_LOGIN4);
		ADD_TPKT(0x02ad, 8, AC_REQUEST_SECOND_PASSWORD);
		ADD_TPKT(0x0270, 2, AC_REQ_LOGIN_ACCOUNT_INFO);
		ADD_TPKT(0x0263, 11, AC_REQ_LOGIN_CARDPASS);
		ADD_TPKT(0x0262, 11, AC_REQ_LOGIN_NEWEKEY);
		ADD_TPKT(0x0261, 11, AC_REQ_LOGIN_OLDEKEY);
		ADD_TPKT(0x09a2, 6, AC_REQ_MOBILE_OTP);
		ADD_TPKT(0x098b, 2, AC_REQ_NEW_USER);
		ADD_TPKT(0x08e4, 6, AC_SHUTDOWN_INFO);
		ADD_TPKT(0x0986, 10, AC_SHUTDOWN_NOTIFY);
		ADD_HPKT(0x0271, 40, CA_ACK_LOGIN_ACCOUNT_INFO);
		ADD_HPKT(0x0266, 30, CA_ACK_LOGIN_CARDPASS);
		ADD_HPKT(0x0265, 20, CA_ACK_LOGIN_NEWEKEY);
		ADD_HPKT(0x0264, 20, CA_ACK_LOGIN_OLDEKEY);
		ADD_HPKT(0x09a3, -1, CA_ACK_MOBILE_OTP);
		ADD_HPKT(0x098c, 4, CA_ACK_NEW_USER);
		ADD_HPKT(0x027f, 8, CA_CLIENT_TYPE);
		ADD_HPKT(0x0200, 26, CA_CONNECT_INFO_CHANGED);
		ADD_HPKT(0x0204, 18, CA_EXE_HASHCHECK);
		ADD_HPKT(0x0064, 55, CA_LOGIN);
		ADD_HPKT(0x01dd, 47, CA_LOGIN2);
		ADD_HPKT(0x01fa, 48, CA_LOGIN3);
		ADD_HPKT(0x027c, 60, CA_LOGIN4);
		ADD_HPKT(0x08cc, 109, CA_LOGIN5);
		ADD_HPKT(0x0987, -1, CA_LOGIN6);
		ADD_HPKT(0x02b0, 85, CA_LOGIN_HAN);
		ADD_HPKT(0x0acf, 68, CA_LOGIN_OTP);
		ADD_HPKT(0x0277, 84, CA_LOGIN_PCBANG);
		ADD_HPKT(0x0822, 9, CA_OTP_AUTH_REQ);
		ADD_HPKT(0x0ad0, 11, CA_OTP_CODE);
		ADD_HPKT(0x01bf, 3, CA_REPLY_PNGAMEROOM);
		ADD_HPKT(0x0258, 2, CA_REQ_GAME_GUARD_CHECK);
		ADD_HPKT(0x01db, 2, CA_REQ_HASH);
		ADD_HPKT(0x0825, -1, CA_SSO_LOGIN_REQ);
#undef ADD_HPKT
#undef ADD_TPKT
	}

	~PacketLengthTable() { }

	std::shared_ptr<AuthSession> get_session() { return _session.lock(); }

	HPacketTablePairType get_hpacket_info(uint16_t packet_id) { return _hpacket_length_table.at(packet_id); }
	TPacketTablePairType get_tpacket_info(uint16_t packet_id) { return _tpacket_length_table.at(packet_id); }

protected:
	LockedLookupTable<uint16_t, HPacketTablePairType> _hpacket_length_table;
	LockedLookupTable<uint16_t, TPacketTablePairType> _tpacket_length_table;
	std::weak_ptr<AuthSession> _session;

};
}
}
#endif /* HORIZON_AUTH_RAGEXE_PACKET_LENGTH_TABLE */
