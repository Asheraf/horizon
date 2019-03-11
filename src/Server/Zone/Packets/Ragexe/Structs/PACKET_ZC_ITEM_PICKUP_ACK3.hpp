/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_ITEM_PICKUP_ACK3_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_ITEM_PICKUP_ACK3_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_ITEM_PICKUP_ACK2.hpp"
#include "Common/Definitions/ItemDefinitions.hpp"

#include "Server/Common/PacketBuffer.hpp"


#include <memory>
namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_ITEM_PICKUP_ACK3 : public PACKET_ZC_ITEM_PICKUP_ACK2
{
	PACKET_ZC_ITEM_PICKUP_ACK3(uint16_t packet_id = ZC_ITEM_PICKUP_ACK3) : PACKET_ZC_ITEM_PICKUP_ACK2(packet_id) { }

	virtual PacketBuffer serialize(item_entry_data const &data, uint16_t amount, item_inventory_addition_notif_type result) override
	{
		PacketBuffer buf(packet_id);

		buf << data.inventory_index;
		buf << amount;
		buf << (uint16_t) data.item_id;
		buf << (uint8_t) (data.info.is_identified ? 1 : 0);
		buf << (uint8_t) (data.info.is_broken ? 1 : 0);
		buf << data.refine_level;

		for (int i = 0; i < MAX_ITEM_SLOTS; i++)
			buf << (uint16_t) data.slot_item_id[i];

		buf << data.actual_equip_location_mask;
		buf << (uint8_t) data.type;
		buf << (uint8_t) result;
		buf << data.hire_expire_date;
		buf << data.bound_type;

		return buf;
	}
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_ITEM_PICKUP_ACK3_HPP */
