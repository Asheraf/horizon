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

#ifndef HORIZON_MODELS_CHARACTERS_INVENTORY_HPP
#define HORIZON_MODELS_CHARACTERS_INVENTORY_HPP

#include "Server/Common/Definitions/Horizon.hpp"
#include "Server/Common/Server.hpp"
#include "Common/Definitions/ItemDefinitions.hpp"
#include <mysqlx/xdevapi.h>

namespace Horizon
{
namespace Models
{
namespace Character
{
class Inventory
{
public:
	Inventory(uint32_t char_id) : _character_id(char_id) {}

	~Inventory() {}

	/**
	 * Load all fields from the database into this instance.
	 * @param server
	 * @param char_id
	 * @return
	 */
	bool load(Server *server, uint32_t char_id)
	{
		std::string query = "SELECT `item_id`, `amount`, `equip_location_mask`, `is_identified`, `refine_level`, `element_type`, "
			"`slot_item_id_0`, `slot_item_id_1`, `slot_item_id_2`, `slot_item_id_3`, "
			"`opt_idx0`, `opt_val0`, `opt_idx1`, `opt_val1`, `opt_idx2`, `opt_val2`, `opt_idx3`, `opt_val3`, `opt_idx4`, `opt_val4`, "
			"`hire_expire_date`, `is_favorite`, `bind_type`, `unique_id` FROM `character_inventory` WHERE `char_id` = ? ORDER BY `id`";

		try {
			auto s = server->get_mysql_client()->getSession();
			auto result = s.sql(query).bind(char_id).execute();

			mysqlx::Row record;

			while ((record = result.fetchOne())) {
				item_entry_data id;

				id.item_id = record[0].get<int>();
				id.amount = record[1].get<int>();
				id.current_equip_location_mask = record[2].get<unsigned>();
				id.info.is_identified = record[3].get<int>();
				id.refine_level = record[4].get<int>();
				id.element_type = (item_element_type) record[5].get<int>();

				for (int i = 0; i < MAX_ITEM_SLOTS; i++)
					id.slot_item_id[i] = record[6 + i].get<int>();

				for (int i = 0; i < MAX_ITEM_OPTIONS; i = i + 2) {
					id.option_data[i].index = record[i].get<int>();
					id.option_data[i + 1].value = record[i + 1].get<int>();
				}

				id.hire_expire_date = record[20].get<unsigned>();
				id.is_favorite = record[21].get<int>();
				id.bind_type = (item_bind_type) record[22].get<int>();
				id.unique_id = record[23].get<uint64_t>();

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
	void save(Server *server)
	{
		try {
			auto s = server->get_mysql_client()->getSession();
			auto table = s.getDefaultSchema().getTable("character_inventory");
			auto qdel = table.remove().where("id = :id").bind("id", get_character_id());
			auto qsave = table.insert( "item_id", "amount", "equip_location_mask", "is_identified", "refine_level", "element_type",
									   "slot_item_id_0", "slot_item_id_1", "slot_item_id_2", "slot_item_id_3",
									   "opt_idx0", "opt_val0", "opt_idx1", "opt_val1", "opt_idx2", "opt_val2",
									   "opt_idx3", "opt_val3", "opt_idx4", "opt_val4",
									   "hire_expire_date", "is_favorite", "bind_type", "unique_id");
			for (auto &id : _inventory) {
				qsave.values(id.item_id,
							 id.amount,
							 id.current_equip_location_mask,
							 id.info.is_identified,
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
							 id.is_favorite,
							 (uint8_t) id.bind_type,
							 id.unique_id);
			}
			qsave.execute();
			s.close();
		} catch (const mysqlx::Error &e) {
			CoreLog->warn("Character::Inventory::save: {}", e.what());
		}
	}

	/* Character ID */
	uint32_t get_character_id() const { return _character_id; }
	void set_character_id(uint32_t character_id) { _character_id = character_id; }

	void syncronize_inventory(std::vector<std::shared_ptr<item_entry_data>> const &items)
	{
		_inventory.clear();

		for (auto &it : items) {
			_inventory.push_back(*it);
		}
	}
private:
	uint32_t _character_id{0};
	std::vector<item_entry_data> _inventory;
};
}
}
}
#endif // HORIZON_MODELS_CHARACTERS_INVENTORY_HPP
