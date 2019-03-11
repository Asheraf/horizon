/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
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
