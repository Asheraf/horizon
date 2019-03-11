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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_CZ_USE_ITEM_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_CZ_USE_ITEM_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_CZ_USE_ITEM : public Packet
{
	PACKET_CZ_USE_ITEM(uint16_t packet_id = CZ_USE_ITEM) : Packet(packet_id) { }

	virtual void deserialize(PacketBuffer &buf)
	{
		buf >> packet_id;
		buf >> inventory_index;
		buf >> guid;
	}

	virtual PACKET_CZ_USE_ITEM & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	/* Size: 8 bytes */
	uint16_t inventory_index{0};
	uint32_t guid{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_CZ_USE_ITEM_HPP */
