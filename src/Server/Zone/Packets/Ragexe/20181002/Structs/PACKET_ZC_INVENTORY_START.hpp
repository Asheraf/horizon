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

#ifndef HORIZON_ZONE_RAGEXE_20181002_PACKET_ZC_INVENTORY_START_HPP
#define HORIZON_ZONE_RAGEXE_20181002_PACKET_ZC_INVENTORY_START_HPP

#include "Server/Zone/Packets/Ragexe/20181002/PacketsRagexe20181002.hpp"
#include "Server/Zone/Packets/Ragexe/20180912/Structs/PACKET_ZC_INVENTORY_START.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181002
{
struct PACKET_ZC_INVENTORY_START : public Horizon::Zone::Ragexe20180912::PACKET_ZC_INVENTORY_START
{
	PACKET_ZC_INVENTORY_START(uint16_t packet_id = ZC_INVENTORY_START) : Horizon::Zone::Ragexe20180912::PACKET_ZC_INVENTORY_START(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180912::PACKET_ZC_INVENTORY_START::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180912::PACKET_ZC_INVENTORY_START::deserialize(buf);
	}

	virtual Ragexe20180912::PACKET_ZC_INVENTORY_START & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override 
	{
		return right = serialize();
	}

	/* Size: -1 bytes */
	/* Changed from 27 in version 20180912 to -1 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181002_PACKET_ZC_INVENTORY_START_HPP */
