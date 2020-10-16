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

#ifndef HORIZON_HC_SECOND_PASSWD_LOGIN_HPP
#define HORIZON_HC_SECOND_PASSWD_LOGIN_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

namespace Horizon
{
namespace Char
{

enum hc_pincode_state_type : uint16_t
{
	PINCODE_CORRECT        = 0,
	PINCODE_REQUEST_PIN    = 1,
	PINCODE_REQUEST_NEW    = 2,
	PINCODE_REQUEST_CHANGE = 3,
	PINCODE_REQUEST_NEW_2  = 4,
	PINCODE_LOGIN_RESTRICT = 5,
	PINCODE_LOGIN_UNUSED   = 6,
	PINCODE_SHOW_BUTTON    = 7,
	PINCODE_INCORRECT      = 8
};

#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
enum hc_pincode_login_response2 {
	PINCODE_LOGIN_FLAG_LOCKED = 0,
	PINCODE_LOGIN_FLAG_CORRECT = 1,
	PINCODE_LOGIN_FLAG_WRONG  = 2,
};
#endif

enum {
#if PACKET_VERSION >= 20180117
	ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#elif PACKET_VERSION >= 20180103
	ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#elif PACKET_VERSION >= 20171220
	ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#elif PACKET_VERSION >= 20110222
	ID_HC_SECOND_PASSWD_LOGIN = 0x08b9
#else
	ID_HC_SECOND_PASSWD_LOGIN = 0x0ae9
#endif
};

class CharSession;

/**
 * @brief Main object for the aegis packet: HC_SECOND_PASSWD_LOGIN
 * Size : 13 @ 0
 *
 */ 
class HC_SECOND_PASSWD_LOGIN : public Base::NetworkPacket<CharSession>
{
public:
	HC_SECOND_PASSWD_LOGIN(std::shared_ptr<CharSession> s);
	virtual ~HC_SECOND_PASSWD_LOGIN();


	void deliver(hc_pincode_state_type state);
	void deliver(hc_pincode_state_type state, hc_pincode_login_response2 state2);
	ByteBuffer &serialize();
	virtual void handle(ByteBuffer &&buf) override;
	void deserialize(ByteBuffer &buf);

	/* Structure Goes Here */
	uint32_t _pincode_seed{0};
	uint32_t _account_id{0};
	hc_pincode_state_type _state{PINCODE_CORRECT};
#if CLIENT_TYPE == 'M' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'R' && PACKET_VERSION >= 20180124 \
|| CLIENT_TYPE == 'Z' && PACKET_VERSION >= 20180131
	hc_pincode_login_response2 _state2{PINCODE_LOGIN_FLAG_WRONG};
#endif
};
}
}

#endif /* HORIZON_HC_SECOND_PASSWD_LOGIN_HPP */
