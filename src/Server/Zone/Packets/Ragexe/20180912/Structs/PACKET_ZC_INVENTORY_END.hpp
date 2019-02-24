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

#ifndef HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_INVENTORY_END_HPP
#define HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_INVENTORY_END_HPP

#include "Server/Zone/Packets/Ragexe/20180912/PacketsRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/Structs/PACKET_ZC_INVENTORY_END.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180912
{
struct PACKET_ZC_INVENTORY_END : public Horizon::Zone::Ragexe20180829::PACKET_ZC_INVENTORY_END
{
	PACKET_ZC_INVENTORY_END(uint16_t packet_id = ZC_INVENTORY_END) : Horizon::Zone::Ragexe20180829::PACKET_ZC_INVENTORY_END(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180829::PACKET_ZC_INVENTORY_END::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180829::PACKET_ZC_INVENTORY_END::deserialize(buf);
	}

	virtual Ragexe20180829::PACKET_ZC_INVENTORY_END & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 4 bytes */
	/* Changed from 3 in version 20180829 to 4 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180912_PACKET_ZC_INVENTORY_END_HPP */
