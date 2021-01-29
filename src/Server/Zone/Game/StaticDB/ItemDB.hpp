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

#pragma once
#ifndef HORIZON_ZONE_GAME_ITEMDB
#define HORIZON_ZONE_GAME_ITEMDB

#include "Common/Definitions/EntityDefinitions.hpp"
#include "Common/Definitions/ItemDefinitions.hpp"

#include <memory>
#include <cstdio>
#include <map>
#include <cstring>
#include <iostream>
#include <array>

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
class ItemDatabase
{
// bonus values and upgrade chances for refining equipment
struct refine_config {
	int chance[REFINE_CHANCE_TYPE_MAX][MAX_REFINE_LEVEL]{{0}}; // success chance
	int bonus[MAX_REFINE_LEVEL]{0}; // cumulative fixed bonus damage
	int randombonus_max[MAX_REFINE_LEVEL]{0}; // cumulative maximum random bonus damage
};
public:
	ItemDatabase();
	~ItemDatabase() { }

	static ItemDatabase *get_instance()
	{
		static ItemDatabase instance;
		return &instance;
	}

	bool load();
	bool load_refine_db();
	bool load_weapon_target_size_modifiers_db();
	bool load_weapon_attribute_modifiers_db();

	bool add_job_group_to_item(std::string const &group, item_config_data &id, bool enable, std::string const &file_path);

	std::shared_ptr<const item_config_data> get_item_by_id(uint32_t item_id) const { return _item_db.at(item_id); }

	std::shared_ptr<const refine_config> get_refine_config(refine_type type)
	{
		return _refine_db.at(type, std::shared_ptr<refine_config>());
	}

	uint8_t get_weapon_target_size_modifier(item_weapon_type wtype, entity_size_type stype)
	{
		std::shared_ptr<std::array<uint8_t, ESZ_MAX>> arr = _weapon_target_size_modifiers_db.at(wtype);
		return arr != nullptr ? (*arr)[stype] : 0;
	}

	std::string get_weapon_type_name(item_weapon_type type)
	{
		try {
			return _weapontype2name_db[type];
		} catch (std::exception &e) {
			return "Unknown";
		}
	}

private:
	int load_items(sol::table const &item_tbl, std::string file_path);
	bool load_refine_table(refine_type tbl_type, sol::table const &refine_table, std::string table_name, std::string file_path);
	std::array<std::string, IT_WT_MAX> _weapontype2name_db;
	LockedLookupTable<uint32_t, std::shared_ptr<const item_config_data>> _item_db;
	LockedLookupTable<uint32_t, std::shared_ptr<const refine_config>> _refine_db;
	LockedLookupTable<uint32_t, std::shared_ptr<std::array<uint8_t, ESZ_MAX>>> _weapon_target_size_modifiers_db;
	LockedLookupTable<uint32_t, std::shared_ptr<std::array<std::array<uint8_t, IT_ELE_MAX>, IT_ELE_MAX>>> _weapon_attribute_modifiers_db;
};
}
}

#define ItemDB Horizon::Zone::ItemDatabase::get_instance()

#endif /* HORIZON_ZONE_GAME_ITEMDB */
