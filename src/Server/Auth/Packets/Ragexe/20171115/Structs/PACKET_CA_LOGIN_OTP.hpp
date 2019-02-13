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

#ifndef HORIZON_AUTH_RAGEXE_20171115_PACKET_CA_LOGIN_OTP_HPP
#define HORIZON_AUTH_RAGEXE_20171115_PACKET_CA_LOGIN_OTP_HPP

#include "Server/Auth/Packets/Ragexe/20171115/PacketsRagexe20171115.hpp"
#include "Server/Auth/Packets/Ragexe/20170705/Structs/PACKET_CA_LOGIN_OTP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe20171115
{
struct PACKET_CA_LOGIN_OTP : public Horizon::Auth::Ragexe20170705::PACKET_CA_LOGIN_OTP
{
	PACKET_CA_LOGIN_OTP(uint16_t packet_id = CA_LOGIN_OTP) : Horizon::Auth::Ragexe20170705::PACKET_CA_LOGIN_OTP(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20170705::PACKET_CA_LOGIN_OTP::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20170705::PACKET_CA_LOGIN_OTP::deserialize(buf);
	}

	virtual Ragexe20170705::PACKET_CA_LOGIN_OTP & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 68 bytes */
	/* Changed from 64 in version 20170705 to 68 */
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_20171115_PACKET_CA_LOGIN_OTP_HPP */
