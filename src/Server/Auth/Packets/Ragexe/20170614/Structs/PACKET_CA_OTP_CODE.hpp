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

#ifndef HORIZON_AUTH_RAGEXE_20170614_PACKET_CA_OTP_CODE_HPP
#define HORIZON_AUTH_RAGEXE_20170614_PACKET_CA_OTP_CODE_HPP

#include "Server/Auth/Packets/Ragexe/20170614/PacketsRagexe20170614.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe20170614
{
struct PACKET_CA_OTP_CODE : public Packet
{
	PACKET_CA_OTP_CODE(uint16_t packet_id = CA_OTP_CODE) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_CA_OTP_CODE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 11 bytes */
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_20170614_PACKET_CA_OTP_CODE_HPP */
