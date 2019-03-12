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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V6_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V6_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V5.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Common/Definitions/ItemDefinitions.hpp"

#include <memory>

namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V6 : public PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V5
{
	PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V6(uint16_t packet_id = ZC_INVENTORY_ITEMLIST_EQUIP_V6) : PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V5(packet_id) { }

	//! @brief Serialize equipments to buffer.
	//! @param items[in] A vector of const shared pointers to the inventory items.
	//! @return A new PacketBuffer with serialized contents of the same.
	virtual PacketBuffer serialize(std::vector<std::shared_ptr<const item_entry_data>> const &items) const override
	{
		PacketBuffer buf(packet_id);
		for (auto it = items.begin(); it != items.end(); it++) {
			std::shared_ptr<const item_entry_data> id = *it;
			uint8_t config = 0;
			buf << id->inventory_index;
			buf << ((uint16_t) id->item_id);
			buf << ((uint8_t) id->type);
			buf << id->actual_equip_location_mask;
			buf << id->current_equip_location_mask;
			buf << id->refine_level;
			for (int i = 0; i < MAX_ITEM_SLOTS; i++)
				buf << (uint16_t) id->slot_item_id[i];
			buf << id->hire_expire_date;
			buf << (uint16_t) id->bind_type;
			buf << id->sprite_id;

			buf << id->option_count;

			for (int i = 0; i < MAX_ITEM_OPTIONS; i++) {
				buf << id->option_data[i].index;
				buf << id->option_data[i].value;
				buf << id->option_data[i].param;
			}

			config |= id->info.is_identified;
			config |= id->info.is_broken << 1;
			config |= id->info.is_favorite << 2;
			buf << config;
		}
		buf.emplace_size();
		return buf;
	}
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_INVENTORY_ITEMLIST_EQUIP_V6_HPP */
