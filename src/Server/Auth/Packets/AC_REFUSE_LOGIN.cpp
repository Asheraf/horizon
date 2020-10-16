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

#include "AC_REFUSE_LOGIN.hpp"
#include "Server/Auth/Session/AuthSession.hpp"

using namespace Horizon::Auth;
using namespace Horizon::Base;

AC_REFUSE_LOGIN::AC_REFUSE_LOGIN(std::shared_ptr<AuthSession> s)
 : NetworkPacket<AuthSession>(ID_AC_REFUSE_LOGIN, s) { }

AC_REFUSE_LOGIN::~AC_REFUSE_LOGIN() { }

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

void AC_REFUSE_LOGIN::handle(ByteBuffer &&buf)
{
}

void AC_REFUSE_LOGIN::deserialize(ByteBuffer &buf)
{
}
