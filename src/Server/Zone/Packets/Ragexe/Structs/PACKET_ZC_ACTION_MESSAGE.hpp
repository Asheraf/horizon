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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_ACTION_MESSAGE_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_ACTION_MESSAGE_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_ACTION_MESSAGE : public Packet
{
	PACKET_ZC_ACTION_MESSAGE(uint16_t packet_id = ZC_ACTION_MESSAGE) : Packet(packet_id) { }

	virtual PacketBuffer serialize()
	{
		PacketBuffer buf(packet_id);
		buf << message_type;
		return buf;
	}

	virtual void deserialize(PacketBuffer &/*buf*/) { }

	virtual PACKET_ZC_ACTION_MESSAGE & operator << (PacketBuffer &right)
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right)
	{
		return right = serialize();
	}

	/* Size: 4 bytes */
	/// type:
	///     0 = MsgStringTable[242]="Please equip the proper ammunition first."
	///     1 = MsgStringTable[243]="You can't Attack or use Skills because your Weight Limit has been exceeded."
	///     2 = MsgStringTable[244]="You can't use Skills because Weight Limit has been exceeded."
	///     3 = assassin, baby_assassin, assassin_cross => MsgStringTable[1040]="You have equipped throwing daggers."
	///         gunslinger => MsgStringTable[1175]="Bullets have been equipped."
	///         NOT ninja => MsgStringTable[245]="Ammunition has been equipped."
	uint16_t message_type{0};
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_ACTION_MESSAGE_HPP */
