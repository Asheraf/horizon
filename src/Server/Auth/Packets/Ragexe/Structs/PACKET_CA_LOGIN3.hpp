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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_CA_LOGIN3_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_CA_LOGIN3_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_CA_LOGIN3 : public Packet
{
	PACKET_CA_LOGIN3(uint16_t packet_id = CA_LOGIN3) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> version;
		buf.read(username, sizeof(username));
		buf.read(password_md5, sizeof(password_md5));
		buf >> client_type;
		buf >> client_info;
	}

	virtual PACKET_CA_LOGIN3 & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 48 bytes */

	uint32_t version{0};         ///< Client Version
	char username[24]{0};        ///< Username
	char password_md5[16]{0}; ///< Password hash
	uint8_t client_type{0};      ///< Client Type
	uint8_t client_info{0};      ///< Index of the connection in the clientinfo file (+10 if the command-line contains "pc")
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_CA_LOGIN3_HPP */
