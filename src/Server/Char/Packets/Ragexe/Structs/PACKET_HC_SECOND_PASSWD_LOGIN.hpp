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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_HC_SECOND_PASSWD_LOGIN_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_HC_SECOND_PASSWD_LOGIN_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Client.hpp"

namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_HC_SECOND_PASSWD_LOGIN : public Packet
{
	PACKET_HC_SECOND_PASSWD_LOGIN(uint16_t packet_id = HC_SECOND_PASSWD_LOGIN) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(HC_SECOND_PASSWD_LOGIN);
		buf << pincode_seed;
		buf << account_id;
		buf << (short) state;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_HC_SECOND_PASSWD_LOGIN & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 13 bytes */
	uint32_t pincode_seed{0};
	uint32_t account_id{0};
	pincode_state state{PINCODE_INCORRECT};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_HC_SECOND_PASSWD_LOGIN_HPP */
