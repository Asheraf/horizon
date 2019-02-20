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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_CZ_INPUT_EDITDLGSTR_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_CZ_INPUT_EDITDLGSTR_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_CZ_INPUT_EDITDLGSTR : public Packet
{
	PACKET_CZ_INPUT_EDITDLGSTR(uint16_t packet_id = CZ_INPUT_EDITDLGSTR) : Packet(packet_id) { }

	~PACKET_CZ_INPUT_EDITDLGSTR()
	{
		if (message != nullptr)
			delete[] message;
	}

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> packet_length;
		buf >> guid;

		int str_len = packet_length - 8;
		message = new char[str_len + 1];
		message[str_len] = '\0';
		buf.read(message, str_len);
	}

	virtual PACKET_CZ_INPUT_EDITDLGSTR & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	uint16_t packet_length{0};
	uint32_t guid{0};
	char *message{nullptr};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_CZ_INPUT_EDITDLGSTR_HPP */
