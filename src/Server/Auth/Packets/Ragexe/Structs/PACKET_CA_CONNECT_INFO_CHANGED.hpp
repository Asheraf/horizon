/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_AUTH_RAGEXE_PACKET_CA_CONNECT_INFO_CHANGED_HPP
#define HORIZON_AUTH_RAGEXE_PACKET_CA_CONNECT_INFO_CHANGED_HPP


#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe
{
struct PACKET_CA_CONNECT_INFO_CHANGED : public Packet
{
	PACKET_CA_CONNECT_INFO_CHANGED(uint16_t packet_id = CA_CONNECT_INFO_CHANGED) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		return PacketBuffer(packet_id);
	}

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf.read(username, sizeof(username));
	}

	virtual PACKET_CA_CONNECT_INFO_CHANGED & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 26 bytes */
	char username[24]{0};            ///< account.userid
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_PACKET_CA_CONNECT_INFO_CHANGED_HPP */
