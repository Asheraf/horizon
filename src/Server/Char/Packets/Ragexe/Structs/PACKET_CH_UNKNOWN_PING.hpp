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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_CH_UNKNOWN_PING_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_CH_UNKNOWN_PING_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_CH_UNKNOWN_PING : public Packet
{
	PACKET_CH_UNKNOWN_PING(uint16_t packet_id = CH_UNKNOWN_PING) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(CH_UNKNOWN_PING);
		buf << account_id;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_CH_UNKNOWN_PING & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 6 bytes */
	uint32_t account_id{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_CH_UNKNOWN_PING_HPP */
