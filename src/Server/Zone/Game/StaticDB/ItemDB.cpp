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

#include "ItemDB.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Common/Definitions/LuaDefinitionSync.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Zone.hpp"
#include <chrono>

using namespace Horizon::Zone;

ItemDatabase::ItemDatabase()
: _item_db(2500), _weapon_target_size_modifiers_db(50)
{
	_weapontype2name_db[IT_WT_FIST]     = "Fist";
	_weapontype2name_db[IT_WT_DAGGER]   = "Dagger";
	_weapontype2name_db[IT_WT_1HSWORD]  = "OneHandedSword";
	_weapontype2name_db[IT_WT_2HSWORD]  = "TwoHandedSword";
	_weapontype2name_db[IT_WT_1HSPEAR]  = "OneHandedSpear";
	_weapontype2name_db[IT_WT_2HSPEAR]  = "TwoHandedSpear";
	_weapontype2name_db[IT_WT_1HAXE]    = "OneHandedAxe";
	_weapontype2name_db[IT_WT_2HAXE]    = "TwoHandedAxe";
	_weapontype2name_db[IT_WT_1HMACE]   = "OneHandedMace";
	_weapontype2name_db[IT_WT_2HMACE]   = "TwoHandedMace";
	_weapontype2name_db[IT_WT_STAFF]    = "OneHandedStaff";
	_weapontype2name_db[IT_WT_BOW]      = "Bow";
	_weapontype2name_db[IT_WT_KNUCKLE]  = "Knuckle";
	_weapontype2name_db[IT_WT_MUSICAL]  = "MusicalInstrument";
	_weapontype2name_db[IT_WT_WHIP]     = "Whip";
	_weapontype2name_db[IT_WT_BOOK]     = "Book";
	_weapontype2name_db[IT_WT_KATAR]    = "Katar";
	_weapontype2name_db[IT_WT_REVOLVER] = "Revolver";
	_weapontype2name_db[IT_WT_RIFLE]    = "Rifle";
	_weapontype2name_db[IT_WT_GATLING]  = "GatlingGun";
	_weapontype2name_db[IT_WT_SHOTGUN]  = "Shotgun";
	_weapontype2name_db[IT_WT_GRENADE]  = "GrenadeLauncher";
	_weapontype2name_db[IT_WT_HUUMA]    = "FuumaShuriken";
	_weapontype2name_db[IT_WT_2HSTAFF]  = "TwoHandedStaff";
}

bool ItemDatabase::load()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);
	lua.open_libraries(sol::lib::package);

	sync_entity_definitions(lua);
	sync_item_definitions(lua);

	int total_entries = 0;

	std::string file_path = sZone->zone_config().get_static_db_path().string() + "item_db.lua";

	sol::protected_function_result safe_res = lua.safe_script_file(file_path);
	
	if (!safe_res.valid()) {
		sol::error err = safe_res;
		HLog(error) << err.what();
		return false;
	}
	
	sol::table item_tbl = lua.get<sol::table>("item_db");
	total_entries = load_items(item_tbl, file_path);
	auto stop = std::chrono::high_resolution_clock::now();
	HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "' (" << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "µs, Max Collisions: " << _item_db.max_collisions() << ").";

	return true;
}

bool ItemDatabase::add_job_group_to_item(std::string const &group, item_config_data &id, bool enable, std::string const &file_path)
{
	if (group.compare("All") == 0) {
		// This is left empty as an empty job_ids vector mean every job.
		id.requirements.job_ids.clear();
		return true;
	} else if (group.compare("NormalJobs") == 0) {
		for (int i = JOB_BASE_START; i < JOB_BASE_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_2_1_START; i < JOB_2_1_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_2_2_START; i < JOB_2_2_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
	} else if (group.compare("NormalBabyJobs") == 0) {
		for (int i = JOB_BABY_BASE_START; i < JOB_BABY_BASE_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_BABY_2_1_START; i < JOB_BABY_2_1_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_BABY_2_2_START; i < JOB_BABY_2_2_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
	} else if (group.compare("TransJobs") == 0) {
		for (int i = JOB_TRANS_BASE_START; i < JOB_TRANS_BASE_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_TRANS_2_1_START; i < JOB_TRANS_2_1_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_TRANS_2_2_START; i < JOB_TRANS_2_2_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
	} else if (group.compare("ThirdJobs") == 0) {
		for (int i = JOB_3_1_START; i < JOB_3_1_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_3_2_START; i < JOB_3_2_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
	} else if (group.compare("ThirdTransJobs") == 0) {
		for (int i = JOB_TRANS_3_1_START; i < JOB_TRANS_3_1_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_TRANS_3_2_START; i < JOB_TRANS_3_2_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
	} else if (group.compare("ThirdBabyJobs") == 0) {
		for (int i = JOB_BABY_3_1_START; i < JOB_BABY_3_1_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
		for (int i = JOB_BABY_3_2_START; i < JOB_BABY_3_2_END; i++) {
			if (enable)
				id.requirements.job_ids.push_back(i);
			else
				std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [i] (uint32_t id) { return i == id; });
		}
	} else if (group.compare("ExtendedJobs") == 0) {
		if (enable) {
			id.requirements.job_ids.push_back(JOB_SUPER_NOVICE);
			id.requirements.job_ids.push_back(JOB_GUNSLINGER);
			id.requirements.job_ids.push_back(JOB_NINJA);
			id.requirements.job_ids.push_back(JOB_TAEKWON);
			id.requirements.job_ids.push_back(JOB_STAR_GLADIATOR);
			id.requirements.job_ids.push_back(JOB_STAR_GLADIATOR2);
			id.requirements.job_ids.push_back(JOB_SOUL_LINKER);
			id.requirements.job_ids.push_back(JOB_GANGSI);
			id.requirements.job_ids.push_back(JOB_DEATH_KNIGHT);
			id.requirements.job_ids.push_back(JOB_DARK_COLLECTOR);
			id.requirements.job_ids.push_back(JOB_SUPER_NOVICE_E);
			id.requirements.job_ids.push_back(JOB_SUPER_BABY_E);
			id.requirements.job_ids.push_back(JOB_KAGEROU);
			id.requirements.job_ids.push_back(JOB_OBORO);
			id.requirements.job_ids.push_back(JOB_REBELLION);
		} else {
			std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [] (uint32_t id)
			   {
				   if (id == JOB_SUPER_NOVICE)
					   return true;
				   if (id == JOB_GUNSLINGER)
					   return true;
				   if (id == JOB_NINJA)
					   return true;
				   if (id == JOB_TAEKWON)
					   return true;
				   if (id == JOB_STAR_GLADIATOR)
					   return true;
				   if (id == JOB_STAR_GLADIATOR2)
					   return true;
				   if (id == JOB_SOUL_LINKER)
					   return true;
				   if (id == JOB_GANGSI)
					   return true;
				   if (id == JOB_DEATH_KNIGHT)
					   return true;
				   if (id == JOB_DARK_COLLECTOR)
					   return true;
				   if (id == JOB_SUPER_NOVICE_E)
					   return true;
				   if (id == JOB_SUPER_BABY_E)
					   return true;
				   if (id == JOB_KAGEROU)
					   return true;
				   if (id == JOB_OBORO)
					   return true;
				   if (id == JOB_REBELLION)
					   return true;

				   return false;
			   });
		}
	} else {
		HLog(error) << "Invalid Job Range '" << group << "' specified for entry in file '" << file_path << "', skipping...";
		return false;
	}

	return true;
}

int ItemDatabase::load_items(sol::table const &item_tbl, std::string file_path)
{
	int entry = 0;
	item_tbl.for_each([this, &entry, &file_path](sol::object const &key, sol::object const &value) {
		uint32_t t_int = 0;
		sol::table tbl = value.as<sol::table>();
		std::string t_str;
		item_config_data id;

		entry++;

		if (key.get_type() != sol::type::string) {
			HLog(error) << "Invalid key type for entry " << entry << " in '" << file_path << "'.";
			return;
		}

		id.key_name = key.as<std::string>();

		id.item_id = tbl.get_or("Id", 0);
		if (id.item_id == 0) {
			HLog(error) << "ItemDB::load_items: Invalid or non-existent mandatory field 'Id' for item '" << id.key_name << "' in '" << file_path << "'. Skipping...";
			return;
		}

		id.name = tbl.get_or("Name", std::string(""));
		if (id.name.empty()) {
			HLog(error) << "ItemDB::load_items: Invalid or non-existent mandatory field 'Name' for entry " << id.item_id << " in '" << file_path << "'. Skipping...";
			return;
		}

		id.type = (item_type) tbl.get_or("Type", (uint16_t) IT_TYPE_ETC);

		if (id.type == IT_TYPE_WEAPON)
			id.sub_type.weapon_t = (item_weapon_type) tbl.get_or("Subtype", (int) IT_WT_FIST);
		else if (id.type == IT_TYPE_AMMO)
			id.sub_type.ammo_t = (item_ammunition_type) tbl.get_or("Subtype", (int) IT_AT_NONE);

		id.value_buy = tbl.get_or("Buy", -1);
		id.value_sell = tbl.get_or("Sell", -1);

		if (id.value_buy == -1 && id.value_sell == -1)
			id.value_buy = id.value_sell = 0;
		else if (id.value_buy == -1)
			id.value_buy = id.value_sell * 2;
		else if (id.value_sell == -1)
			id.value_sell = id.value_buy / 2;

		// Discount / Overcharge zeny exploit check.
		if (id.value_buy / 124.0 < id.value_sell / 75.0) {
			HLog(warning) << "Buying/Selling [" << id.value_buy << "/" << id.value_sell << "] price of item " << id.item_id << " (" << id.name << ") "
						"allows Zeny making exploit through buying/selling at discounted/overcharged prices! File '" << file_path << "'.\n";
		}

		id.weight = tbl.get_or("Weight", 0);
		id.attack = tbl.get_or("Atk", 0);
		id.magic_atk = tbl.get_or("Matk", 0);
		id.defense = tbl.get_or("Def", 0);
		id.attack_range = tbl.get_or("Range", 0);
		id.card_slot_count = tbl.get_or("Slots", 0);
		t_int = tbl.get_or("WeaponLv", 1);

		if (id.type == IT_TYPE_WEAPON)
			id.level.weapon = t_int;
		else
			id.level.armor = t_int;

		sol::optional<sol::object> maybe_job_tbl = tbl.get<sol::optional<sol::object>>("Job");
		if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::table) {
			sol::table job_tbl = maybe_job_tbl.value().as<sol::table>();
			job_tbl.for_each([this, &id, &file_path] (sol::object const &key, sol::object const &value)
			{
				bool enable = value.as<bool>();

				if (key.get_type() == sol::type::string) {
					std::string job_name = key.as<std::string>();
					if (!add_job_group_to_item(job_name, id, enable, file_path))
						return;
				} else if (key.get_type() == sol::type::number) {
					int job_id = key.as<int>();

					if (enable) {
						id.requirements.job_ids.push_back(job_id);
					} else {
						std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [job_id] (uint32_t id) { return job_id == id; });
					}
				}
			});
		} else if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::string) {
			std::string job_name = maybe_job_tbl.value().as<std::string>();
			if (!add_job_group_to_item(job_name, id, true, file_path))
				return;
		} else if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::number) {
			id.requirements.job_ids.push_back(maybe_job_tbl.value().as<uint32_t>());
		}

		id.requirements.gender = (item_gender_type) tbl.get_or("Gender", (char) IT_GENDER_ANY);

		sol::optional<sol::object> location = tbl.get<sol::optional<sol::object>>("Loc");

		if (location) {
			sol::object loc = location.value();

			if (loc.get_type() == sol::type::table) {
				loc.as<sol::table>().for_each([&id, &file_path] (sol::object const &key, sol::object const &value) {
					if (value.get_type() != sol::type::number) {
						HLog(warning) <<"Invalid type for 'Loc' in entry '" << id.key_name << "' in file '" << file_path << "'";
						return;
					}

					id.equip_location_mask |= value.as<int>();
				});
			} else if (loc.get_type() == sol::type::number) {
				id.equip_location_mask |= loc.as<int>();
			}
		}

		sol::optional<sol::object> maybe_elv = tbl.get<sol::optional<sol::object>>("EquipLv");

		if (maybe_elv) {
			if (maybe_elv.value().get_type() == sol::type::table) {
				sol::table elv = maybe_elv.value();
				id.requirements.min_lv = elv.get_or(0, 0);
				id.requirements.max_lv = elv.get_or(1, 0);
			} else if (maybe_elv.value().get_type() == sol::type::number) {
				id.requirements.min_lv = maybe_elv.value().as<int32_t>();
			} else {
				id.requirements.min_lv = id.requirements.max_lv = 0;
			}
		} else {
			id.requirements.min_lv = id.requirements.max_lv = 0;
		}

		id.config.refineable = tbl.get_or("Refine", false);
		id.config.allow_item_options = tbl.get_or("EnableOptions", true);
		id.config.show_drop_effect = tbl.get_or("ShowDropEffect", false);
		id.config.show_drop_effect = tbl.get_or("DropEffectMode", 0);

		id.sprite_id = tbl.get_or("ViewSprite", 0);
		id.default_script = tbl.get_or("Script", std::string(""));
		id.equip_script = tbl.get_or("OnEquipScript", std::string(""));
		id.unequip_script = tbl.get_or("OnUnequipScript", std::string(""));

		_item_db.insert(id.item_id, std::make_shared<item_config_data>(id));
	});

	return _item_db.size();
}

bool ItemDatabase::load_refine_db()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);

	int total_entries = 0;

	std::string file_path = sZone->zone_config().get_static_db_path().string() + "refine_db.lua";

	try {
		lua.script_file(file_path);
		struct {
			refine_type type;
			std::string tbl_name;
		} refine_tbls[] = {
			{ REFINE_TYPE_ARMOR, "Armors", },
			{ REFINE_TYPE_WEAPON1, "WeaponLevel1", },
			{ REFINE_TYPE_WEAPON2, "WeaponLevel2", },
			{ REFINE_TYPE_WEAPON3, "WeaponLevel3", },
			{ REFINE_TYPE_WEAPON4, "WeaponLevel4" }
		};
		for (auto &tbl : refine_tbls) {
			if (load_refine_table(tbl.type, lua.get<sol::table>(tbl.tbl_name), tbl.tbl_name, file_path))
				total_entries++;
		}
		auto stop = std::chrono::high_resolution_clock::now();
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "' (" << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "µs).";
	} catch(const std::exception &e) {
		HLog(error) << e.what() << " in file '" << file_path << "'";
		return false;
	}

	return true;
}

bool ItemDatabase::load_refine_table(refine_type type, sol::table const &refine_table, std::string table_name, std::string file_path)
{
	uint32_t bonus_per_level = 0, rand_bonus_start_lv = 0, rand_bonus_val = 0;
	refine_config cfg;

	bonus_per_level = refine_table.get_or("StatsPerLevel", 0);
	rand_bonus_start_lv = refine_table.get_or("RandomBonusStartLevel", 0);
	rand_bonus_val = refine_table.get_or("RandomBonusValue", 0);

	sol::optional<sol::table> maybe_rates = refine_table.get<sol::optional<sol::table>>("Rates");

	if (maybe_rates) {
		if (maybe_rates.value().get_type() != sol::type::table) {
			HLog(error) << "Invalid type for entry 'Rates' table '" << table_name << "' in file '" << file_path << "'. Skipping...";
			return false;
		}

		sol::table rates_tbl = maybe_rates.value();

		for (int i = 0; i < MAX_REFINE_LEVEL; i++) {
			sol::optional<sol::table> maybe_level_tbl = rates_tbl.get<sol::optional<sol::table>>(i + 1);
			if (maybe_level_tbl) {
				sol::table level_tbl = maybe_level_tbl.value();
				cfg.bonus[i] = bonus_per_level + level_tbl.get_or("Bonus", 0);
				cfg.chance[REFINE_CHANCE_TYPE_NORMAL][i] = level_tbl.get_or("NormalChance", 100);
				cfg.chance[REFINE_CHANCE_TYPE_ENRICHED][i] = level_tbl.get_or("EnrichedChance", i + 1 > 10 ? 0 : 100); // enriched ores up to +10 only.
				cfg.chance[REFINE_CHANCE_TYPE_E_NORMAL][i] = level_tbl.get_or("EventNormalChance", 100);
				cfg.chance[REFINE_CHANCE_TYPE_E_ENRICHED][i] = level_tbl.get_or("EventEnrichedChance", i + 1 > 10 ? 0 : 100); // enriched ores up to +10 only.
				if (i + 1 >= rand_bonus_start_lv)
					cfg.randombonus_max[i] = (rand_bonus_val * (i - rand_bonus_start_lv + 2));
			} else {
				// Defaults.
				cfg.bonus[i] = bonus_per_level;
				cfg.chance[REFINE_CHANCE_TYPE_NORMAL][i] = cfg.chance[REFINE_CHANCE_TYPE_E_NORMAL][i] = 100;
				cfg.chance[REFINE_CHANCE_TYPE_ENRICHED][i] = cfg.chance[REFINE_CHANCE_TYPE_E_ENRICHED][i] = i + 1 > 10 ? 0 : 100; // enriched ores up to +10 only.
			}
		}
	} else {
		HLog(error) << "Non-existent configuration for entry 'Rates' table '" << table_name << "' in file '" << file_path << "'. Skipping...";
		return false;
	}

	_refine_db.insert(type, std::make_shared<refine_config>(cfg));

	return true;
}

bool ItemDatabase::load_weapon_target_size_modifiers_db()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);

	sync_item_definitions(lua);

	int total_entries = 0;

	std::string file_path = sZone->zone_config().get_static_db_path().string() + "weapon_target_size_modifiers.lua";

	try {
		lua.script_file(file_path);

		sol::table size_mod_tbl = lua["weapon_target_size_modifiers"];

		for (int i = IT_WT_FIST; i < IT_WT_MAX; i++) {
			std::shared_ptr<std::array<uint8_t, ESZ_MAX>> arr = std::make_shared<std::array<uint8_t, ESZ_MAX>>();
			for (int j = ESZ_SMALL; j < ESZ_MAX; j++) {
				std::string size = j == ESZ_SMALL ? "Small" : j == ESZ_MEDIUM ? "Medium" : "Large";
				try {
					(*arr)[j] = size_mod_tbl[i][size];
				} catch (std::exception &err) {
					HLog(error) << "Weapon target size modifier was not found for weapon type " << get_weapon_type_name((item_weapon_type) i) << " size " << size << ", defaulting to 100%...";
					(*arr)[j] = 100;
				}
			}
			_weapon_target_size_modifiers_db.insert((item_weapon_type) i, arr);
			total_entries++;
		}
		auto stop = std::chrono::high_resolution_clock::now();
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "' (" << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "µs.";
	} catch(const std::exception &e) {
		HLog(error) << e.what() << " in file '" << file_path << "'";
		return false;
	}

	return true;
}

bool ItemDatabase::load_weapon_attribute_modifiers_db()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);

	sync_item_definitions(lua);
	
	int total_entries = 0;

	std::string file_path = sZone->zone_config().get_static_db_path().string() + "weapon_attribute_modifiers.lua";

	try {
		lua.script_file(file_path);

		sol::table attr_mod_tbl = lua["weapon_attribute_modifiers"];

		struct {
			item_element_type type;
			std::string ele_name;
		} attr_s[] = {
			{ IT_ELE_NEUTRAL, "Neutral" },
			{ IT_ELE_WATER, "Water" },
			{ IT_ELE_EARTH, "Earth" },
			{ IT_ELE_FIRE, "Fire" },
			{ IT_ELE_WIND, "Wind" },
			{ IT_ELE_POISON, "Poison" },
			{ IT_ELE_HOLY, "Holy" },
			{ IT_ELE_DARK, "Dark" },
			{ IT_ELE_GHOST, "Ghost" },
			{ IT_ELE_UNDEAD, "Undead" },
		};

		for (int i = IT_LVL_WEAPON1; i < IT_LVL_MAX; i++) {
			std::shared_ptr<std::array<std::array<uint8_t, IT_ELE_MAX>, IT_ELE_MAX>> arr = std::make_shared<std::array<std::array<uint8_t, IT_ELE_MAX>, IT_ELE_MAX>>();
			for (int j = IT_ELE_NEUTRAL; j < IT_ELE_MAX; j++) {
				for (int k = IT_ELE_NEUTRAL; k < IT_ELE_MAX; k++) {
					try {
						(*arr)[j][k] = attr_mod_tbl[i][j][k + 1];
					} catch (std::exception &err) {
						HLog(error) << "Weapon target attribute modifier was not found for weapon type " << get_weapon_type_name((item_weapon_type) i) << " attribute [" << attr_s[j].ele_name << "][" << attr_s[k].ele_name << "], defaulting to 100%...";
						(*arr)[j][k] = 100;
					}
					total_entries++;
				}
			}
			_weapon_attribute_modifiers_db.insert((item_level_type) i, arr);
		}
		auto stop = std::chrono::high_resolution_clock::now();
		HLog(info) << "Loaded " << total_entries << " entries from '" << file_path << "' (" << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << "µs).";
	} catch(const std::exception &e) {
		HLog(error) << e.what() << " in file '" << file_path << "'.";
		return false;
	}

	return true;
}
