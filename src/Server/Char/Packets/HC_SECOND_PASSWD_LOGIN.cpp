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

#include "HC_SECOND_PASSWD_LOGIN.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_SECOND_PASSWD_LOGIN::HC_SECOND_PASSWD_LOGIN(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_HC_SECOND_PASSWD_LOGIN, s) { }

HC_SECOND_PASSWD_LOGIN::~HC_SECOND_PASSWD_LOGIN() { }

void HC_SECOND_PASSWD_LOGIN::deliver(hc_pincode_state_type state)
{
	std::srand(std::time(0));
	_pincode_seed = rand() % 0xFFFF;
	get_session()->get_session_data()._pincode_seed = _pincode_seed;
	
	_account_id = get_session()->get_session_data()._account_id;
	_state = state;
	
	serialize();
	transmit();
}

void HC_SECOND_PASSWD_LOGIN::deliver(hc_pincode_state_type state, hc_pincode_login_response2 state2)
{
	_state2 = state2;
	deliver(state);
}

ByteBuffer &HC_SECOND_PASSWD_LOGIN::serialize()
{
	buf() << _packet_id;
	buf() << _pincode_seed;
	buf() << _account_id;
	buf() << ((short) _state);
#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
	buf() << (uint8_t) _state2;
#endif
	
	return buf();
}

void HC_SECOND_PASSWD_LOGIN::handle(ByteBuffer &&buf)
{
}

void HC_SECOND_PASSWD_LOGIN::deserialize(ByteBuffer &buf)
{
}

