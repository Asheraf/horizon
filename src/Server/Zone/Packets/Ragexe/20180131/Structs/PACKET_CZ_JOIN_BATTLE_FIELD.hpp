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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_RAGEXE_20180131_PACKET_CZ_JOIN_BATTLE_FIELD_HPP
#define HORIZON_ZONE_RAGEXE_20180131_PACKET_CZ_JOIN_BATTLE_FIELD_HPP

#include "Server/Zone/Packets/Ragexe/20180131/PacketsRagexe20180131.hpp"
#include "Server/Zone/Packets/Ragexe/20180124/Structs/PACKET_CZ_JOIN_BATTLE_FIELD.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180131
{
struct PACKET_CZ_JOIN_BATTLE_FIELD : public Horizon::Zone::Ragexe20180124::PACKET_CZ_JOIN_BATTLE_FIELD
{
	PACKET_CZ_JOIN_BATTLE_FIELD(uint16_t packet_id = CZ_JOIN_BATTLE_FIELD) : Horizon::Zone::Ragexe20180124::PACKET_CZ_JOIN_BATTLE_FIELD(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180124::PACKET_CZ_JOIN_BATTLE_FIELD::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180124::PACKET_CZ_JOIN_BATTLE_FIELD::deserialize(buf);
	}

	virtual Ragexe20180124::PACKET_CZ_JOIN_BATTLE_FIELD & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 8 bytes */
	/* Changed from 2 in version 20180124 to 8 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180131_PACKET_CZ_JOIN_BATTLE_FIELD_HPP */
