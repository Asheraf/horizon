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

#ifndef HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO_HPP
#define HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO_HPP

#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe20180103
{
struct PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO : public Horizon::Zone::Ragexe::PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO
{
	PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO(uint16_t packet_id = ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO) : Horizon::Zone::Ragexe::PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO(packet_id) { }

	virtual PacketBuffer serialize() override
	{
		return Ragexe::PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO::serialize();
	}

	virtual void deserialize(PacketBuffer &buf) override
	{
		Ragexe::PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO::deserialize(buf);
	}

	virtual Ragexe::PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO & operator << (PacketBuffer &right) override
	{
		deserialize(right);
		return *this;
	}

	virtual PacketBuffer operator >> (PacketBuffer &right) override
	{
		return right = serialize();
	}

	/* Size: 10 bytes */
	/* Changed from 12 in version 0 to 10 */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_20180103_PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO_HPP */
