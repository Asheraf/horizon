/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_ZONE_RAGEXE_PACKET_ZC_EQUIPMENT_ITEMLIST3_HPP
#define HORIZON_ZONE_RAGEXE_PACKET_ZC_EQUIPMENT_ITEMLIST3_HPP


#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "PACKET_ZC_EQUIPMENT_ITEMLIST2.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Common/Definitions/ItemDefinitions.hpp"

#include <memory>

namespace Horizon
{
namespace Zone
{
namespace Ragexe
{
struct PACKET_ZC_EQUIPMENT_ITEMLIST3 : public PACKET_ZC_EQUIPMENT_ITEMLIST2
{
	PACKET_ZC_EQUIPMENT_ITEMLIST3(uint16_t packet_id = ZC_EQUIPMENT_ITEMLIST3) : PACKET_ZC_EQUIPMENT_ITEMLIST2(packet_id) { }

	virtual PacketBuffer serialize(std::vector<std::shared_ptr<const item_entry_data>> const &items) const override
	{
		PacketBuffer buf(packet_id);
		for (auto it = items.begin(); it != items.end(); it++) {
			std::shared_ptr<const item_entry_data> id = *it;
			buf << id->inventory_index;
			buf << ((uint16_t) id->item_id);
			buf << ((uint8_t) id->type);
			buf << ((uint8_t) id->info.is_identified ? 1 : 0);
			buf << ((uint16_t) id->actual_equip_location_mask);
			buf << ((uint16_t) id->current_equip_location_mask);
			buf << ((uint16_t) id->info.is_broken ? 1 : 0);
			buf << id->refine_level;
			for (int i = 0; i < sizeof(id->slot_item_id); i++)
				buf << (uint16_t) id->slot_item_id[i];
			buf << id->hire_expire_date;
			buf << id->bound_type;
		}
		buf.emplace_size();
		return buf;
	}
};
}
}
}

#endif /* HORIZON_ZONE_RAGEXE_PACKET_ZC_EQUIPMENT_ITEMLIST3_HPP */
