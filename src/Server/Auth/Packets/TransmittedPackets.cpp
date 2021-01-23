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


#include "TransmittedPackets.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

/**
 * AC_LOGIN_OTP
 */
void AC_LOGIN_OTP::deliver() { }

ByteBuffer &AC_LOGIN_OTP::serialize()
{
	return buf();
}

/**
 * AC_ACK_FIRST_LOGIN
 */
void AC_ACK_FIRST_LOGIN::deliver() { }

ByteBuffer &AC_ACK_FIRST_LOGIN::serialize()
{
	return buf();
}

/**
 * AC_REQ_LOGIN_NEWEKEY
 */
void AC_REQ_LOGIN_NEWEKEY::deliver() { }

ByteBuffer &AC_REQ_LOGIN_NEWEKEY::serialize()
{
	return buf();
}

/**
 * AC_SHUTDOWN_NOTIFY
 */
void AC_SHUTDOWN_NOTIFY::deliver() { }

ByteBuffer &AC_SHUTDOWN_NOTIFY::serialize()
{
	return buf();
}

/**
 * AC_REQ_LOGIN_ACCOUNT_INFO
 */
void AC_REQ_LOGIN_ACCOUNT_INFO::deliver() { }

ByteBuffer &AC_REQ_LOGIN_ACCOUNT_INFO::serialize()
{
	return buf();
}

/**
 * AC_SHUTDOWN_INFO
 */
void AC_SHUTDOWN_INFO::deliver() { }

ByteBuffer &AC_SHUTDOWN_INFO::serialize()
{
	return buf();
}

/**
 * AC_ACK_GAME_GUARD
 */
void AC_ACK_GAME_GUARD::deliver() { }

ByteBuffer &AC_ACK_GAME_GUARD::serialize()
{
	return buf();
}

/**
 * AC_ACK_HASH
 */
void AC_ACK_HASH::deliver() { }

ByteBuffer &AC_ACK_HASH::serialize()
{
	return buf();
}

/**
 * AC_REQUEST_SECOND_PASSWORD
 */
void AC_REQUEST_SECOND_PASSWORD::deliver() { }

ByteBuffer &AC_REQUEST_SECOND_PASSWORD::serialize()
{
	return buf();
}

/**
 * AC_NOTIFY_ERROR
 */
void AC_NOTIFY_ERROR::deliver() { }

ByteBuffer &AC_NOTIFY_ERROR::serialize()
{
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_NOTICE
 */
void AC_ACK_EKEY_FAIL_NOTICE::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_NOTICE::serialize()
{
	return buf();
}

/**
 * AC_REALNAME_AUTH
 */
void AC_REALNAME_AUTH::deliver() { }

ByteBuffer &AC_REALNAME_AUTH::serialize()
{
	return buf();
}

/**
 * AC_REQ_LOGIN_OLDEKEY
 */
void AC_REQ_LOGIN_OLDEKEY::deliver() { }

ByteBuffer &AC_REQ_LOGIN_OLDEKEY::serialize()
{
	return buf();
}

/**
 * AC_ACCEPT_LOGIN2
 */
void AC_ACCEPT_LOGIN2::deliver() { }

ByteBuffer &AC_ACCEPT_LOGIN2::serialize()
{
	return buf();
}

/**
 * AC_REFUSE_LOGIN
 */
void AC_REFUSE_LOGIN::deliver(login_error_codes error_code, char *block_date, std::size_t bd_size)
{
	_error_code = (uint32_t) error_code;
	
	if (bd_size <= sizeof(_block_date))
		strncpy(_block_date, block_date, bd_size);
	
	serialize();
	
	transmit();
	
	HLog(debug) << "AC_REFUSE_LOGIN sent with error code " << (int) error_code;
}

ByteBuffer &AC_REFUSE_LOGIN::serialize()
{
	buf() << _packet_id;
	buf() << (uint32_t) _error_code;
	buf().append(_block_date, sizeof(_block_date));
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_NEEDCARDPASS
 */
void AC_ACK_EKEY_FAIL_NEEDCARDPASS::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_NEEDCARDPASS::serialize()
{
	return buf();
}

/**
 * AC_OTP_AUTH_ACK
 */
void AC_OTP_AUTH_ACK::deliver() { }

ByteBuffer &AC_OTP_AUTH_ACK::serialize()
{
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_INPUTEKEY
 */
void AC_ACK_EKEY_FAIL_INPUTEKEY::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_INPUTEKEY::serialize()
{
	return buf();
}

/**
 * AC_REQ_LOGIN_CARDPASS
 */
void AC_REQ_LOGIN_CARDPASS::deliver() { }

ByteBuffer &AC_REQ_LOGIN_CARDPASS::serialize()
{
	return buf();
}

/**
 * AC_REQ_NEW_USER
 */
void AC_REQ_NEW_USER::deliver() { }

ByteBuffer &AC_REQ_NEW_USER::serialize()
{
	return buf();
}

/**
 * AC_EVENT_RESULT
 */
void AC_EVENT_RESULT::deliver() { }

ByteBuffer &AC_EVENT_RESULT::serialize()
{
	return buf();
}

/**
 * AC_OTP_USER
 */
void AC_OTP_USER::deliver() { }

ByteBuffer &AC_OTP_USER::serialize()
{
	return buf();
}

/**
 * AC_REQ_MOBILE_OTP
 */
void AC_REQ_MOBILE_OTP::deliver() { }

ByteBuffer &AC_REQ_MOBILE_OTP::serialize()
{
	return buf();
}

/**
 * AC_ASK_PNGAMEROOM
 */
void AC_ASK_PNGAMEROOM::deliver() { }

ByteBuffer &AC_ASK_PNGAMEROOM::serialize()
{
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_AUTHREFUSE
 */
void AC_ACK_EKEY_FAIL_AUTHREFUSE::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_AUTHREFUSE::serialize()
{
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_NOTUSEDEKEY
 */
void AC_ACK_EKEY_FAIL_NOTUSEDEKEY::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_NOTUSEDEKEY::serialize()
{
	return buf();
}

/**
 * AC_ACK_PT_ID_INFO
 */
void AC_ACK_PT_ID_INFO::deliver() { }

ByteBuffer &AC_ACK_PT_ID_INFO::serialize()
{
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_NOTEXIST
 */
void AC_ACK_EKEY_FAIL_NOTEXIST::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_NOTEXIST::serialize()
{
	return buf();
}

/**
 * AC_REFUSE_LOGIN3
 */
void AC_REFUSE_LOGIN3::deliver() { }

ByteBuffer &AC_REFUSE_LOGIN3::serialize()
{
	return buf();
}

/**
 * AC_REFUSE_LOGIN2
 */
void AC_REFUSE_LOGIN2::deliver() { }

ByteBuffer &AC_REFUSE_LOGIN2::serialize()
{
	return buf();
}

/**
 * AC_ACK_EKEY_FAIL_NOTUSESEKEY
 */
void AC_ACK_EKEY_FAIL_NOTUSESEKEY::deliver() { }

ByteBuffer &AC_ACK_EKEY_FAIL_NOTUSESEKEY::serialize()
{
	return buf();
}

/**
 * AC_SSO_LOGIN_ACK
 */
void AC_SSO_LOGIN_ACK::deliver() { }

ByteBuffer &AC_SSO_LOGIN_ACK::serialize()
{
	return buf();
}

/**
 * AC_REFUSE_LOGIN4
 */
void AC_REFUSE_LOGIN4::deliver() { }

ByteBuffer &AC_REFUSE_LOGIN4::serialize()
{
	return buf();
}

/**
 * AC_ACCEPT_LOGIN
 */
void AC_ACCEPT_LOGIN::deliver(int32_t auth_code, uint32_t aid, uint32_t user_level, uint8_t sex)
{
	_al.packet_len = 2 + sizeof(struct s_ac_accept_login) + (sizeof(s_ac_char_server_list) * sAuth->get_auth_config().get_char_servers().size());
	_al.auth_code = auth_code;
	_al.aid = aid;
	_al.user_level = user_level;
	_al.last_login_ip = 0;
	memset(_al.last_login_time, '\0', sizeof(_al.last_login_time));
	_al.sex = sex;
	
	for (auth_config_type::char_server c : sAuth->get_auth_config().get_char_servers()) {
		s_ac_char_server_list sc;
		sc.ip = inet_addr(c._host.c_str());
		sc.port = c._port;
		strncpy(sc.name, c._name.c_str(), sizeof(sc.name));
		sc.usercount = 10;
		sc.is_new = c._is_new;
		sc.type = c._type;
		_c.push_back(sc);
	}
	
	serialize();
	transmit();
}

ByteBuffer &AC_ACCEPT_LOGIN::serialize()
{
	buf() << _packet_id;
	buf() << _al.packet_len;
	buf() << _al.auth_code;
	buf() << _al.aid;
	buf() << _al.user_level;
	buf() << _al.last_login_ip; // not used anymore
	memset(_al.last_login_time, '\0', sizeof(_al.last_login_time));
	buf().append(_al.last_login_time, sizeof(_al.last_login_time)); // not used anymore
	buf() << _al.sex;
	
#if PACKET_VERSION >= 20170315
	buf().append(_al.twitter_auth_token, sizeof(_al.twitter_auth_token));
	buf() << _al.twitter_flag;
#endif
	
	for (s_ac_char_server_list sc : _c) {
		buf() << sc.ip;
		buf() << sc.port;
		buf().append(sc.name, sizeof(sc.name));
		buf() << sc.usercount;
		buf() << sc.is_new;
		buf() << sc.type;
#if PACKET_VERSION >= 20170315
		buf().append(sc.unknown2, sizeof(sc.unknown2));
#endif
	}
	
	HLog(debug) << "Serialized AC_ACCEPT_LOGIN of size " << _al.packet_len << ". Buffer:" << buf().to_string();
	
	return buf();
}

