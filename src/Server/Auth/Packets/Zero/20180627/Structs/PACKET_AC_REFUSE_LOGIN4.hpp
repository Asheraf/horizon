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

#ifndef HORIZON_AUTH_ZERO_20180627_PACKET_AC_REFUSE_LOGIN4_HPP
#define HORIZON_AUTH_ZERO_20180627_PACKET_AC_REFUSE_LOGIN4_HPP

#include "Server/Auth/Packets/Zero/20180627/PacketsZero20180627.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Zero20180627
{
struct PACKET_AC_REFUSE_LOGIN4 : public Packet
{
	PACKET_AC_REFUSE_LOGIN4(uint16_t packet_id = AC_REFUSE_LOGIN4) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_AC_REFUSE_LOGIN4 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 26 bytes */
};
}
}
}

#endif /* HORIZON_AUTH_ZERO_20180627_PACKET_AC_REFUSE_LOGIN4_HPP */
