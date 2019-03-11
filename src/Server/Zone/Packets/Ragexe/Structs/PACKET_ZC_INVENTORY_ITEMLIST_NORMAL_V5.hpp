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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_INVENTORY_ITEMLIST_NORMAL_V5_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_INVENTORY_ITEMLIST_NORMAL_V5_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "PACKET_ZC_NORMAL_ITEMLIST3.hpp"
#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_INVENTORY_ITEMLIST_NORMAL_V5 : public PACKET_ZC_NORMAL_ITEMLIST3
{
	PACKET_ZC_INVENTORY_ITEMLIST_NORMAL_V5(uint16_t packet_id = ZC_INVENTORY_ITEMLIST_NORMAL_V5) : PACKET_ZC_NORMAL_ITEMLIST3(packet_id) { }

	virtual PacketBuffer serialize(std::vector<std::shared_ptr<const item_entry_data>> const &items) const override
	{
		PacketBuffer buf(packet_id);
		for (auto it = items.begin(); it != items.end(); it++) {
			std::shared_ptr<const item_entry_data> id = *it;
			uint8_t config = 0;

			buf << id->inventory_index;
			buf << ((uint16_t) id->item_id);
			buf << ((uint8_t) id->type);
			buf << id->amount;
			buf << id->current_equip_location_mask;

			for (int i = 0; i < MAX_ITEM_SLOTS; i++)
				buf << (uint16_t) id->slot_item_id[i];

			buf << id->hire_expire_date;

			config |= id->info.is_identified;
			config |= id->info.is_favorite << 1;
			buf << config;
		}
		buf.emplace_size();
		return buf;
	}
	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_INVENTORY_ITEMLIST_NORMAL_V5_HPP */
