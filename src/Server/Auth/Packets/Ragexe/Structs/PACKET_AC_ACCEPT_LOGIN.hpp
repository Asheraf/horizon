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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_AC_ACCEPT_LOGIN_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_AC_ACCEPT_LOGIN_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_AC_ACCEPT_LOGIN : public Packet
{
	PACKET_AC_ACCEPT_LOGIN(uint16_t packet_id = AC_ACCEPT_LOGIN) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(AC_ACCEPT_LOGIN);
		buf << packet_len;
		buf << auth_code;
		buf << aid;
		buf << user_level;
		buf << last_login_ip;
		buf.append(last_login_time, sizeof(last_login_time));
		buf << sex;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_AC_ACCEPT_LOGIN & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	virtual uint16_t get_length(uint8_t character_server_count = 1)
	{
		return 47 + (32 * character_server_count);
	}

	/* Size: 47 + (32 * char server count) bytes */

	int16_t packet_len{0};         ///< Packet length (variable length)
	int32_t auth_code{0};          ///< Authentication code
	uint32_t aid{0};               ///< Account ID
	uint32_t user_level{0};        ///< User level
	uint32_t last_login_ip{0};     ///< Last login IP
	char last_login_time[26]{0};   ///< Last login timestamp
	uint8_t sex{0};                ///< Account sex

	struct character_server_list
	{
		virtual PacketBuffer serialize(PacketBuffer &buf)
		{
			buf << ip;
			buf << port;
			buf.append(name, sizeof(name));
			buf << usercount;
			buf << is_new;
			buf << type;

			return buf;
		}
		uint32_t ip{0};            ///< Server IP address
		int16_t port{0};           ///< Server port
		char name[20]{0};          ///< Server name
		uint16_t usercount{0};     ///< Online users
		uint16_t is_new{0};        ///< Server state
		uint16_t type{0};          ///< Server type @ character_server_types
	};
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_AC_ACCEPT_LOGIN_HPP */
