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

#ifndef HORIZON_AUTH_ZERO_20171113_PACKET_CA_LOGIN_OTP_HPP
#define HORIZON_AUTH_ZERO_20171113_PACKET_CA_LOGIN_OTP_HPP

#include "Server/Auth/Packets/Zero/20171113/PacketsZero20171113.hpp"
#include "Server/Auth/Packets/Zero/20171018/Structs/PACKET_CA_LOGIN_OTP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Zero20171113
{
struct PACKET_CA_LOGIN_OTP : public Horizon::Auth::Zero20171018::PACKET_CA_LOGIN_OTP
{
	PACKET_CA_LOGIN_OTP(uint16_t packet_id = CA_LOGIN_OTP) : Horizon::Auth::Zero20171018::PACKET_CA_LOGIN_OTP(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Zero20171018::PACKET_CA_LOGIN_OTP::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Zero20171018::PACKET_CA_LOGIN_OTP::deserialize(buf);
	}

	virtual Zero20171018::PACKET_CA_LOGIN_OTP & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: 68 bytes */
	/* Changed from 64 in version 20171018 to 68 */
};
}
}
}

#endif /* HORIZON_AUTH_ZERO_20171113_PACKET_CA_LOGIN_OTP_HPP */
