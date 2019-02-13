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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_CH_ENTER_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_CH_ENTER_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_CH_ENTER : public Packet
{
	PACKET_CH_ENTER(uint16_t packet_id = CH_ENTER) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(CH_ENTER);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> account_id;
		buf >> auth_code;
		buf >> account_level;
		buf >> unknown;
		buf >> gender;
	}

	virtual PACKET_CH_ENTER & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 17 bytes */

	// 0065 <account id>.L <login id1>.L <login id2>.L <???>.W <sex>.B
	uint32_t account_id{0};
	uint32_t auth_code{0};
	uint32_t account_level{0};
	uint16_t unknown{0};
	uint8_t gender{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_CH_ENTER_HPP */
