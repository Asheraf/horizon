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

#ifndef HORIZON_AC_ACCEPT_LOGIN_HPP
#define HORIZON_AC_ACCEPT_LOGIN_HPP

#include "Server/Common/Configuration/Horizon.hpp"
#include "Server/Common/Base/NetworkPacket.hpp"

#include <vector>

namespace Horizon
{
namespace Auth
{
class AuthSession;
enum {
#if PACKET_VERSION >= 20170228
	ID_AC_ACCEPT_LOGIN = 0x0ac4
#elif PACKET_VERSION >= 0
	ID_AC_ACCEPT_LOGIN = 0x0069
#endif
};
/**
 * @brief Main object for the aegis packet: AC_ACCEPT_LOGIN
 * Size : -1 @ 0
 *
 */ 
class AC_ACCEPT_LOGIN : public Base::NetworkPacket<AuthSession>
{
/* Size: 47 + (32 * char server count) bytes */
#pragma pack(push, 1)
struct s_ac_accept_login {
	int16_t packet_len{0};         ///< Packet length (variable length)
	int32_t auth_code{0};          ///< Authentication code
	uint32_t aid{0};               ///< Account ID
	uint32_t user_level{0};        ///< User level
	uint32_t last_login_ip{0};     ///< Last login IP
	char last_login_time[26]{0};   ///< Last login timestamp
	uint8_t sex{0};                ///< Account sex
#if PACKET_VERSION >= 20170315
	char twitter_auth_token[16]{0};
	uint8_t twitter_flag{0};
#endif
};

struct s_ac_char_server_list
{
	uint32_t ip{0};            ///< Server IP address
	int16_t port{0};           ///< Server port
	char name[20]{0};          ///< Server name
	uint16_t usercount{0};     ///< Online users
	uint16_t is_new{0};        ///< Server state
	uint16_t type{0};          ///< Server type @ character_server_type
#if PACKET_VERSION >= 20170315
	char unknown2[128]{0};
#endif
};
#pragma pack(pop)
	
public:
	AC_ACCEPT_LOGIN(std::shared_ptr<AuthSession> s);
	virtual ~AC_ACCEPT_LOGIN();
	
	void deliver(int32_t auth_code, uint32_t aid, uint32_t user_level, uint8_t sex);

	ByteBuffer &serialize();

	virtual void handle(ByteBuffer &&buf) override;

	void deserialize(ByteBuffer &buf);

protected:
	s_ac_accept_login _al;
	std::vector<s_ac_char_server_list> _c;
};
}
}
#endif /* HORIZON_AC_ACCEPT_LOGIN_HPP */
