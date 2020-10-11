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

#include "AC_ACCEPT_LOGIN.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"

#include <string.h>

using namespace Horizon;

AC_ACCEPT_LOGIN::AC_ACCEPT_LOGIN(std::shared_ptr<AuthSocket> sock)
 : Base::NetworkPacket<AuthSocket>(ID_AC_ACCEPT_LOGIN, sock) { }

AC_ACCEPT_LOGIN::~AC_ACCEPT_LOGIN() { }

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

void AC_ACCEPT_LOGIN::handle(ByteBuffer &&buf)
{
}

void AC_ACCEPT_LOGIN::deserialize(ByteBuffer &buf)
{
}

