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

#ifndef HORIZON_AUTH_RAGEXE_PACKETS_HPP
#define HORIZON_AUTH_RAGEXE_PACKETS_HPP

namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
enum packets
{
	AC_ACCEPT_LOGIN = 0x0069,
	AC_ACCEPT_LOGIN2 = 0x0276,
	AC_ACK_EKEY_FAIL_AUTHREFUSE = 0x026a,
	AC_ACK_EKEY_FAIL_INPUTEKEY = 0x026b,
	AC_ACK_EKEY_FAIL_NEEDCARDPASS = 0x026d,
	AC_ACK_EKEY_FAIL_NOTEXIST = 0x0267,
	AC_ACK_EKEY_FAIL_NOTICE = 0x026c,
	AC_ACK_EKEY_FAIL_NOTUSEDEKEY = 0x0269,
	AC_ACK_EKEY_FAIL_NOTUSESEKEY = 0x0268,
	AC_ACK_FIRST_LOGIN = 0x026f,
	AC_ACK_GAME_GUARD = 0x0259,
	AC_ACK_HASH = 0x01dc,
	AC_ACK_PT_ID_INFO = 0x0272,
	AC_ASK_PNGAMEROOM = 0x01be,
	AC_EVENT_RESULT = 0x023d,
	AC_LOGIN_OTP = 0x0ae3,
	AC_NOTIFY_ERROR = 0x01f1,
	AC_OTP_AUTH_ACK = 0x0823,
	AC_OTP_USER = 0x0821,
	AC_REALNAME_AUTH = 0x08b2,
	AC_REFUSE_LOGIN = 0x006a,
	AC_REFUSE_LOGIN2 = 0x083e,
	AC_REFUSE_LOGIN3 = 0x09a5,
	AC_REFUSE_LOGIN4 = 0x0b02,
	AC_REQUEST_SECOND_PASSWORD = 0x02ad,
	AC_REQ_LOGIN_ACCOUNT_INFO = 0x0270,
	AC_REQ_LOGIN_CARDPASS = 0x0263,
	AC_REQ_LOGIN_NEWEKEY = 0x0262,
	AC_REQ_LOGIN_OLDEKEY = 0x0261,
	AC_REQ_MOBILE_OTP = 0x09a2,
	AC_REQ_NEW_USER = 0x098b,
	AC_SHUTDOWN_INFO = 0x08e4,
	AC_SHUTDOWN_NOTIFY = 0x0986,
	CA_ACK_LOGIN_ACCOUNT_INFO = 0x0271,
	CA_ACK_LOGIN_CARDPASS = 0x0266,
	CA_ACK_LOGIN_NEWEKEY = 0x0265,
	CA_ACK_LOGIN_OLDEKEY = 0x0264,
	CA_ACK_MOBILE_OTP = 0x09a3,
	CA_ACK_NEW_USER = 0x098c,
	CA_CLIENT_TYPE = 0x027f,
	CA_CONNECT_INFO_CHANGED = 0x0200,
	CA_EXE_HASHCHECK = 0x0204,
	CA_LOGIN = 0x0064,
	CA_LOGIN2 = 0x01dd,
	CA_LOGIN3 = 0x01fa,
	CA_LOGIN4 = 0x027c,
	CA_LOGIN5 = 0x08cc,
	CA_LOGIN6 = 0x0987,
	CA_LOGIN_HAN = 0x02b0,
	CA_LOGIN_OTP = 0x0acf,
	CA_LOGIN_PCBANG = 0x0277,
	CA_OTP_AUTH_REQ = 0x0822,
	CA_REPLY_PNGAMEROOM = 0x01bf,
	CA_REQ_GAME_GUARD_CHECK = 0x0258,
	CA_REQ_HASH = 0x01db,
	CA_SSO_LOGIN_REQ = 0x0825,
};
}
}
}
#endif /* HORIZON_AUTH_RAGEXE_PACKETS_HPP */
