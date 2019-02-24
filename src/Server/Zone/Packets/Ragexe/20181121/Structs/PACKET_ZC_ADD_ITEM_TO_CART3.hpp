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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_ADD_ITEM_TO_CART3_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_ADD_ITEM_TO_CART3_HPP

#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/Structs/PACKET_ZC_ADD_ITEM_TO_CART3.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181121
{
struct PACKET_ZC_ADD_ITEM_TO_CART3 : public Horizon::Zone::Ragexe20180103::PACKET_ZC_ADD_ITEM_TO_CART3
{
	PACKET_ZC_ADD_ITEM_TO_CART3(uint16_t packet_id = ZC_ADD_ITEM_TO_CART3) : Horizon::Zone::Ragexe20180103::PACKET_ZC_ADD_ITEM_TO_CART3(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180103::PACKET_ZC_ADD_ITEM_TO_CART3::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180103::PACKET_ZC_ADD_ITEM_TO_CART3::deserialize(buf);
	}

	virtual Ragexe20180103::PACKET_ZC_ADD_ITEM_TO_CART3 & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 57 bytes */
	/* Changed from 47 in version 20180103 to 57 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_ADD_ITEM_TO_CART3_HPP */
