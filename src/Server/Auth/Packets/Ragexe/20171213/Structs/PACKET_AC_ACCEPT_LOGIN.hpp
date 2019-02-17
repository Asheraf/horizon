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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_AUTH_RAGEXE_20171213_PACKET_AC_ACCEPT_LOGIN_HPP
#define HORIZON_AUTH_RAGEXE_20171213_PACKET_AC_ACCEPT_LOGIN_HPP

#include "Server/Auth/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACCEPT_LOGIN.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe20171213
{
struct PACKET_AC_ACCEPT_LOGIN : public Horizon::Auth::Ragexe::PACKET_AC_ACCEPT_LOGIN
{
	PACKET_AC_ACCEPT_LOGIN(uint16_t packet_id = AC_ACCEPT_LOGIN) : Horizon::Auth::Ragexe::PACKET_AC_ACCEPT_LOGIN(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		PacketBuffer buf(packet_id);

		buf << packet_len;
		buf << auth_code;
		buf << aid;
		buf << user_level;
		buf << last_login_ip;
		buf.append(last_login_time, sizeof(last_login_time));
		buf << sex;
		buf.append(twitter_auth_token, sizeof(twitter_auth_token));
		buf << twitter_flag;

		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) override { }

	virtual Ragexe::PACKET_AC_ACCEPT_LOGIN & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	virtual uint16_t get_length(uint8_t character_server_count = 1) override
	{
		return 64 + (160 * character_server_count);
	}

	char twitter_auth_token[16]{0};
	uint8_t twitter_flag{0};

	struct character_server_list : public Ragexe::PACKET_AC_ACCEPT_LOGIN::character_server_list {
		virtual PacketBuffer serialize(PacketBuffer &buf) override
		{
			Ragexe::PACKET_AC_ACCEPT_LOGIN::character_server_list::serialize(buf);
			buf.append(unknown2, sizeof(unknown2));

			return buf;
		}
		char unknown2[128]{0};
	};
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_20171213_PACKET_AC_ACCEPT_LOGIN_HPP */
