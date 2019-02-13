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

#ifndef HORIZON_CHAR_RAGEXE_PACKET_CH_MAKE_CHAR_HPP
#define HORIZON_CHAR_RAGEXE_PACKET_CH_MAKE_CHAR_HPP


#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe
{
struct PACKET_CH_MAKE_CHAR : public Packet
{
	PACKET_CH_MAKE_CHAR(uint16_t packet_id = CH_MAKE_CHAR) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(CH_MAKE_CHAR);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf.read(name, sizeof(name));
		buf >> slot;
		buf >> hair_color;
		buf >> hair_style;
		buf >> job_id;
		buf.read(unknown_bytes, sizeof(unknown_bytes));
		buf >> gender;
	}

	virtual PACKET_CH_MAKE_CHAR & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 36 bytes */
	// S 0a39 <name>.24B <slot>.B <hair color>.W <hair style>.W <starting job class ID>.W <Unknown>.(W or 2 B's)??? <sex>.B
	char name[MAX_UNIT_NAME_LENGTH]{0};
	uint8_t slot{0};
	uint16_t hair_color{0};
	uint16_t hair_style{0};
	uint16_t job_id{0};
	char unknown_bytes[2]{0};
	uint8_t gender{0};
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_PACKET_CH_MAKE_CHAR_HPP */
