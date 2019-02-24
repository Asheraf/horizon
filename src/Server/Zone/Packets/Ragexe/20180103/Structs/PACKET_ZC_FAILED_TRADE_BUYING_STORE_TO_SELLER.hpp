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

#ifndef HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER_HPP
#define HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER_HPP

#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180103
{
struct PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER : public Horizon::Zone::Ragexe::PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER
{
	PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER(uint16_t packet_id = ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER) : Horizon::Zone::Ragexe::PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 6 bytes */
	/* Changed from 8 in version 0 to 6 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER_HPP */
