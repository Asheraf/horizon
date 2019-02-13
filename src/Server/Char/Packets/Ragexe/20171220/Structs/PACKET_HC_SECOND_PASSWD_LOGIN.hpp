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

#ifndef HORIZON_CHAR_RAGEXE_20171220_PACKET_HC_SECOND_PASSWD_LOGIN_HPP
#define HORIZON_CHAR_RAGEXE_20171220_PACKET_HC_SECOND_PASSWD_LOGIN_HPP

#include "Server/Char/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_SECOND_PASSWD_LOGIN.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe20171220
{
struct PACKET_HC_SECOND_PASSWD_LOGIN : public Horizon::Char::Ragexe::PACKET_HC_SECOND_PASSWD_LOGIN
{
	PACKET_HC_SECOND_PASSWD_LOGIN(uint16_t packet_id = HC_SECOND_PASSWD_LOGIN) : Horizon::Char::Ragexe::PACKET_HC_SECOND_PASSWD_LOGIN(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_HC_SECOND_PASSWD_LOGIN::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_HC_SECOND_PASSWD_LOGIN::deserialize(buf);
	}

	virtual Ragexe::PACKET_HC_SECOND_PASSWD_LOGIN & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 64 bytes */
	/* Changed from 13 in version 0 to 64 */
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_20171220_PACKET_HC_SECOND_PASSWD_LOGIN_HPP */
