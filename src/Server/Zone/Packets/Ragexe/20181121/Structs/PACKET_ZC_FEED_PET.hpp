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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_FEED_PET_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_FEED_PET_HPP

#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/Structs/PACKET_ZC_FEED_PET.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20181121
{
struct PACKET_ZC_FEED_PET : public Horizon::Zone::Ragexe20180103::PACKET_ZC_FEED_PET
{
	PACKET_ZC_FEED_PET(uint16_t packet_id = ZC_FEED_PET) : Horizon::Zone::Ragexe20180103::PACKET_ZC_FEED_PET(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe20180103::PACKET_ZC_FEED_PET::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe20180103::PACKET_ZC_FEED_PET::deserialize(buf);
	}

	virtual Ragexe20180103::PACKET_ZC_FEED_PET & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 7 bytes */
	/* Changed from 5 in version 20180103 to 7 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20181121_PACKET_ZC_FEED_PET_HPP */
