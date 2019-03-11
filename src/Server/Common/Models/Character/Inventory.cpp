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

#include "Inventory.hpp"

#include "Server/Common/Server.hpp"
#include "Server/Common/Definitions/ItemDefinitions.hpp"

#include <mysqlx/xdevapi.h>

using namespace Horizon::Models::Character;

/**
 * Load all fields from the database into this instance.
 * @param server
 * @param char_id
 * @return
 */
bool Inventory::load(Server *server, uint32_t char_id)
{
	std::string query = "SELECT `inventory_index`, `item_id`, `amount`, `equip_location_mask`, `is_identified`, `refine_level`, `element_type`, "
		"`slot_item_id_0`, `slot_item_id_1`, `slot_item_id_2`, `slot_item_id_3`, "
		"`opt_idx0`, `opt_val0`, `opt_idx1`, `opt_val1`, `opt_idx2`, `opt_val2`, `opt_idx3`, `opt_val3`, `opt_idx4`, `opt_val4`, "
		"`hire_expire_date`, `is_favorite`, `bind_type`, `unique_id` FROM `character_inventory` WHERE `char_id` = ? ORDER BY `id`";

	try {
		auto s = server->get_mysql_client()->getSession();
		auto result = s.sql(query).bind(char_id).execute();

		mysqlx::Row record;

		while ((record = result.fetchOne())) {
			item_entry_data id;

			id.inventory_index = record[0].get<int>();
			id.item_id = record[1].get<int>();
			id.amount = record[2].get<int>();
			id.current_equip_location_mask = record[3].get<unsigned>();
			id.info.is_identified = record[4].get<int>();
			id.refine_level = record[5].get<int>();
			id.element_type = (item_element_type) record[6].get<int>();

			for (int i = 0; i < MAX_ITEM_SLOTS; i++)
				id.slot_item_id[i] = record[7 + i].get<int>();

			for (int i = 0; i < MAX_ITEM_OPTIONS; i++) {
				id.option_data[i].index = record[7 + MAX_ITEM_SLOTS + i].get<int>();
				id.option_data[i].value = record[7 + MAX_ITEM_SLOTS + i + 1].get<int>();
			}

			int offset = 7 + MAX_ITEM_SLOTS + (MAX_ITEM_OPTIONS * 2);
			id.hire_expire_date = record[offset++].get<unsigned>();
			id.info.is_favorite = record[offset++].get<int>();
			id.bind_type = (item_bind_type) record[offset++].get<int>();
			id.unique_id = record[offset++].get<uint64_t>();

			_inventory.push_back(id);
		}
		s.close();
		return true;
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Character::Inventory::load: {}", e.what());
	}

	return false;
}

/**
 * @brief Save this model to the database in its current state.
 * @param[in|out] server   instance of the server object used to borrow mysql connections.
 */
bool Inventory::save(Server *server)
{
	try {
		auto s = server->get_mysql_client()->getSession();
		auto table = s.getDefaultSchema().getTable("character_inventory");

		// Clear all previous data for character.
		table.remove().where("char_id = :char_id").bind("char_id", get_character_id()).execute();
		// Insert current state.
		auto qsave = table.insert( "char_id", "inventory_index", "item_id", "amount", "equip_location_mask",
								   "is_identified", "refine_level", "element_type",
								   "slot_item_id_0", "slot_item_id_1", "slot_item_id_2", "slot_item_id_3",
								   "opt_idx0", "opt_val0", "opt_idx1", "opt_val1", "opt_idx2", "opt_val2",
								   "opt_idx3", "opt_val3", "opt_idx4", "opt_val4",
								   "hire_expire_date", "is_favorite", "bind_type", "unique_id");
		for (auto &id : _inventory) {
			qsave.values(get_character_id(),
						 id.inventory_index,
						 id.item_id,
						 id.amount,
						 id.current_equip_location_mask,
						 id.info.is_identified ? 1 : 0,
						 id.refine_level,
						 (uint8_t) id.element_type,
						 id.slot_item_id[0],
						 id.slot_item_id[1],
						 id.slot_item_id[2],
						 id.slot_item_id[3],
						 id.option_data[0].index,
						 id.option_data[0].value,
						 id.option_data[1].index,
						 id.option_data[1].value,
						 id.option_data[2].index,
						 id.option_data[2].value,
						 id.option_data[3].index,
						 id.option_data[3].value,
						 id.option_data[4].index,
						 id.option_data[4].value,
						 id.hire_expire_date,
						 id.info.is_favorite ? 1 : 0,
						 (uint8_t) id.bind_type,
						 id.unique_id);
		}
		qsave.execute();
		s.close();
		return true;
	} catch (const mysqlx::Error &e) {
		CoreLog->warn("Character::Inventory::save: {}", e.what());
	}
	return false;
}

