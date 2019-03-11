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
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Zone.hpp"
#include <chrono>

using namespace Horizon::Zone::Game;

ItemDatabase::ItemDatabase()
: _item_db(2500), _weapon_target_size_modifiers_db(50)
{
	_weapontype2name_db[IT_WT_FIST] = "Fist";
	_weapontype2name_db[IT_WT_DAGGER] = "Dagger";
	_weapontype2name_db[IT_WT_1HSWORD] = "One_Handed_Sword";
	_weapontype2name_db[IT_WT_2HSWORD] = "Two_Handed_Sword";
	_weapontype2name_db[IT_WT_1HSPEAR] = "One_Handed_Spear";
	_weapontype2name_db[IT_WT_2HSPEAR] = "Two_Handed_Spear";
	_weapontype2name_db[IT_WT_1HAXE] = "One_Handed_Axe";
	_weapontype2name_db[IT_WT_2HAXE] = "Two_Handed_Axe";
	_weapontype2name_db[IT_WT_1HMACE] = "One_Handed_Mace";
	_weapontype2name_db[IT_WT_2HMACE] = "Two_Handed_Mace";
	_weapontype2name_db[IT_WT_STAFF] = "One_Handed_Staff";
	_weapontype2name_db[IT_WT_BOW] = "Bow";
	_weapontype2name_db[IT_WT_KNUCKLE] = "Knuckle";
	_weapontype2name_db[IT_WT_MUSICAL] = "Musical_Instrument";
	_weapontype2name_db[IT_WT_WHIP] = "Whip";
	_weapontype2name_db[IT_WT_BOOK] = "Book";
	_weapontype2name_db[IT_WT_KATAR] = "Katar";
	_weapontype2name_db[IT_WT_REVOLVER] = "Revolver";
	_weapontype2name_db[IT_WT_RIFLE] = "Rifle";
	_weapontype2name_db[IT_WT_GATLING] = "Gatling_Gun";
	_weapontype2name_db[IT_WT_SHOTGUN] = "Shotgun";
	_weapontype2name_db[IT_WT_GRENADE] = "Grenade_Launcher";
	_weapontype2name_db[IT_WT_HUUMA] = "Fuuma_Shuriken";
	_weapontype2name_db[IT_WT_2HSTAFF] = "Two_Handed_Staff";
}

bool ItemDatabase::load()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);

	int total_entries = 0;

	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "item_db.lua";

	try {
		lua.script_file(file_path);
		sol::table item_tbl = lua.get<sol::table>("item_db");
		total_entries = load_items(item_tbl, file_path);
		auto stop = std::chrono::high_resolution_clock::now();
		ZoneLog->info("Loaded {} entries from '{}' ({}µs, Max Collisions: {}).", total_entries, file_path, std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count(), _item_db.max_collisions());
	} catch(const std::exception &e) {
		ZoneLog->error("ItemDB::load: {}", e.what());
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

		if (key.get_type() != sol::type::number) {
			ZoneLog->error("Invalid key type for entry {} in '{}'.", entry, file_path);
			return;
		}

		id.item_id = key.as<uint32_t>();

		id.aegis_name = tbl.get_or("AegisName", std::string(""));
		if (id.aegis_name.empty()) {
			ZoneLog->error("ItemDB::load_items: Invalid or non-existent mandatory field 'AegisName' for entry {} in '{}'. Skipping...", id.item_id, file_path);
			return;
		}

		id.name = tbl.get_or("Name", std::string(""));
		if (id.name.empty()) {
			ZoneLog->error("ItemDB::load_items: Invalid or non-existent mandatory field 'Name' for entry {} in '{}'. Skipping...", id.item_id, file_path);
			return;
		}

		t_str = tbl.get_or("Type", std::string(""));
		if (!t_str.empty()) {
			if (t_str.compare("HEALING") == 0) {
				id.type = IT_TYPE_HEALING;
			} else if (t_str.compare("UNKNOWN") == 0) {
				id.type = IT_TYPE_UNKNOWN;
			} else if (t_str.compare("USABLE") == 0) {
				id.type = IT_TYPE_USABLE;
			} else if (t_str.compare("ETC") == 0) {
				id.type = IT_TYPE_ETC;
			} else if (t_str.compare("WEAPON") == 0) {
				id.type = IT_TYPE_WEAPON;
			} else if (t_str.compare("ARMOR") == 0) {
				id.type = IT_TYPE_ARMOR;
			} else if (t_str.compare("CARD") == 0) {
				id.type = IT_TYPE_CARD;
			} else if (t_str.compare("PET_EGG") == 0) {
				id.type = IT_TYPE_PET_EGG;
			} else if (t_str.compare("PET_ARMOR") == 0) {
				id.type = IT_TYPE_PET_ARMOR;
			} else if (t_str.compare("UNKNOWN2") == 0) {
				id.type = IT_TYPE_UNKNOWN2;
			} else if (t_str.compare("AMMO") == 0) {
				id.type = IT_TYPE_AMMO;
			} else if (t_str.compare("CONSUMPTION_DELAY") == 0) {
				id.type = IT_TYPE_USABLE;
				id.config.consumption_delay = 1;
			} else if (t_str.compare("CASH") == 0) {
				id.type = IT_TYPE_CASH;
			} else {
				ZoneLog->error("Invalid value for field 'Type' in item '{}' file '{}', defaulting to 'IT_TYPE_ETC'.", id.item_id, file_path);
				id.type = IT_TYPE_ETC;
			}
		} else {
			id.type = IT_TYPE_ETC;
		}

		t_str = tbl.get_or("Subtype", std::string(""));
		if (!t_str.empty()) {
			switch (id.type)
			{
				case IT_TYPE_WEAPON:
					if (t_str.compare("DAGGER") == 0) { id.sub_type.weapon_t = IT_WT_DAGGER; }
					else if (t_str.compare("1HSWORD") == 0) { id.sub_type.weapon_t = IT_WT_1HSWORD; }
					else if (t_str.compare("2HSWORD") == 0) { id.sub_type.weapon_t = IT_WT_2HSWORD; }
					else if (t_str.compare("1HSPEAR") == 0) { id.sub_type.weapon_t = IT_WT_1HSPEAR; }
					else if (t_str.compare("2HSPEAR") == 0) { id.sub_type.weapon_t = IT_WT_2HSPEAR; }
					else if (t_str.compare("1HAXE") == 0) { id.sub_type.weapon_t = IT_WT_1HAXE; }
					else if (t_str.compare("2HAXE") == 0) { id.sub_type.weapon_t = IT_WT_2HAXE; }
					else if (t_str.compare("1HMACE") == 0) { id.sub_type.weapon_t = IT_WT_1HMACE; }
					else if (t_str.compare("2HMACE") == 0) { id.sub_type.weapon_t = IT_WT_2HMACE; }
					else if (t_str.compare("STAFF") == 0) { id.sub_type.weapon_t = IT_WT_STAFF; }
					else if (t_str.compare("BOW") == 0) { id.sub_type.weapon_t = IT_WT_BOW; }
					else if (t_str.compare("KNUCKLE") == 0) { id.sub_type.weapon_t = IT_WT_KNUCKLE; }
					else if (t_str.compare("MUSICAL") == 0) { id.sub_type.weapon_t = IT_WT_MUSICAL; }
					else if (t_str.compare("WHIP") == 0) { id.sub_type.weapon_t = IT_WT_WHIP; }
					else if (t_str.compare("BOOK") == 0) { id.sub_type.weapon_t = IT_WT_BOOK; }
					else if (t_str.compare("KATAR") == 0) { id.sub_type.weapon_t = IT_WT_KATAR; }
					else if (t_str.compare("REVOLVER") == 0) { id.sub_type.weapon_t = IT_WT_REVOLVER; }
					else if (t_str.compare("RIFLE") == 0) { id.sub_type.weapon_t = IT_WT_RIFLE; }
					else if (t_str.compare("GATLING") == 0) { id.sub_type.weapon_t = IT_WT_GATLING; }
					else if (t_str.compare("SHOTGUN") == 0) { id.sub_type.weapon_t = IT_WT_SHOTGUN; }
					else if (t_str.compare("GRENADE") == 0) { id.sub_type.weapon_t = IT_WT_GRENADE; }
					else if (t_str.compare("HUUMA") == 0) { id.sub_type.weapon_t = IT_WT_HUUMA; }
					else if (t_str.compare("2HSTAFF") == 0) { id.sub_type.weapon_t = IT_WT_2HSTAFF; }
					else {
						ZoneLog->error("Invalid value for field 'Subtype' in entry '{}' file '{}', defaulting to 'FIST'.", id.item_id, file_path);
						id.sub_type.weapon_t = IT_WT_FIST;
					}
					break;
				case IT_TYPE_AMMO:
					if (t_str.compare("ARROW") == 0) { id.sub_type.ammo_t = IT_AT_ARROW; }
					else if (t_str.compare("DAGGER") == 0) { id.sub_type.ammo_t = IT_AT_DAGGER; }
					else if (t_str.compare("BULLET") == 0) { id.sub_type.ammo_t = IT_AT_BULLET; }
					else if (t_str.compare("SHELL") == 0) { id.sub_type.ammo_t = IT_AT_SHELL; }
					else if (t_str.compare("GRENADE") == 0) { id.sub_type.ammo_t = IT_AT_GRENADE; }
					else if (t_str.compare("SHURIKEN") == 0) { id.sub_type.ammo_t = IT_AT_SHURIKEN; }
					else if (t_str.compare("KUNAI") == 0) { id.sub_type.ammo_t = IT_AT_KUNAI; }
					else if (t_str.compare("CANNONBALL") == 0) { id.sub_type.ammo_t = IT_AT_CANNONBALL; }
					else if (t_str.compare("THROWABLE_WEAPON") == 0) { id.sub_type.ammo_t = IT_AT_THROWABLE_WEAPON; }
					else if (t_str.compare("NONE") == 0) { id.sub_type.ammo_t = IT_AT_NONE; }
					else {
						ZoneLog->error("Invalid value for field 'Subtype' in entry '{}' file '{}', defaulting to 'IT_AT_NONE'.", id.item_id, file_path);
						id.sub_type.ammo_t = IT_AT_NONE;
					}
					break;
				default:
					ZoneLog->error("Field 'Subtype' is only allowed for IT_TYPE_WEAPON and IT_TYPE_AMMO in entry '{}' file '{}', ignoring...", id.item_id, file_path);
					break;
			}
		}

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
			ZoneLog->warn("Buying/Selling [{}/{}] price of item {} ({}) "
						"allows Zeny making exploit through buying/selling at discounted/overcharged prices! File '{}'.\n",
						id.value_buy, id.value_sell, id.item_id, id.name, file_path);
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

		sol::optional<sol::object> maybe_job_tbl = tbl["Job"];
		if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::table) {
			sol::table job_tbl = maybe_job_tbl.value().as<sol::table>();
			job_tbl.for_each([&id, &file_path](sol::object const &key, sol::object const &value) {
				std::string job_name = key.as<std::string>();
				bool enable = value.as<bool>();

				if (job_name.compare("All") == 0) {
					return;
				} else if (job_name.compare("NormalJobs") == 0) {
					for (int i = JOB_BASE_START; i < JOB_BASE_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_2_1_START; i < JOB_2_1_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_2_2_START; i < JOB_2_2_END; i++)
						id.requirements.job_ids.push_back(i);
					return;
				} else if (job_name.compare("NormalBabyJobs") == 0) {
					for (int i = JOB_BABY_BASE_START; i < JOB_BABY_BASE_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_BABY_2_1_START; i < JOB_BABY_2_1_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_BABY_2_2_START; i < JOB_BABY_2_2_END; i++)
						id.requirements.job_ids.push_back(i);
					return;
				} else if (job_name.compare("TransJobs") == 0) {
					for (int i = JOB_TRANS_BASE_START; i < JOB_TRANS_BASE_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_TRANS_2_1_START; i < JOB_TRANS_2_1_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_TRANS_2_2_START; i < JOB_TRANS_2_2_END; i++)
						id.requirements.job_ids.push_back(i);
					return;
				} else if (job_name.compare("ThirdJobs") == 0) {
					for (int i = JOB_3_1_START; i < JOB_3_1_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_3_2_START; i < JOB_3_2_END; i++)
						id.requirements.job_ids.push_back(i);
					return;
				} else if (job_name.compare("ThirdTransJobs") == 0) {
					for (int i = JOB_TRANS_3_1_START; i < JOB_TRANS_3_1_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_TRANS_3_2_START; i < JOB_TRANS_3_2_END; i++)
						id.requirements.job_ids.push_back(i);
					return;
				} else if (job_name.compare("ThirdBabyJobs") == 0) {
					for (int i = JOB_BABY_3_1_START; i < JOB_BABY_3_1_END; i++)
						id.requirements.job_ids.push_back(i);
					for (int i = JOB_BABY_3_2_START; i < JOB_BABY_3_2_END; i++)
						id.requirements.job_ids.push_back(i);
					return;
				}

				job_class_type job_id = JobDB->get_job_class_by_name(job_name);

				if (job_id == JOB_INVALID) {
					ZoneLog->error("Invalid Job '{}' specified for entry in file '{}', skipping...", job_name, file_path);
					return;
				}

				if (enable) {
					id.requirements.job_ids.push_back(job_id);
				} else {
					std::remove_if(id.requirements.job_ids.begin(), id.requirements.job_ids.end(), [job_id](uint32_t id) {
						return job_id == id;
					});
				}
			});
		} else if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::string) {
			std::string job_name = maybe_job_tbl.value().as<std::string>();
			job_class_type job_id = JobDB->get_job_class_by_name(job_name);
			if (job_id == JOB_INVALID) {
				ZoneLog->error("Invalid Job '{}' specified for entry in file '{}', skipping...", job_name, file_path);
			} else {
				id.requirements.job_ids.push_back(job_id);
			}
		} else if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::number) {
			id.requirements.job_ids.push_back(maybe_job_tbl.value().as<uint32_t>());
		}

		t_str = tbl.get_or("Gender", std::string(""));
		if (!t_str.empty()) {
			if (t_str.compare("IT_GENDER_FEMALE") == 0) { id.requirements.gender = IT_GENDER_FEMALE; }
			else if (t_str.compare("IT_GENDER_MALE") == 0) { id.requirements.gender = IT_GENDER_MALE; }
			else if (t_str.compare("IT_GENDER_ANY") == 0) { id.requirements.gender = IT_GENDER_ANY; }
			else {
				ZoneLog->error("Invalid Gender '{}' for item '{}' ID {} in file '{}', skipping...", t_str, id.aegis_name, id.item_id, file_path);
				id.requirements.gender = IT_GENDER_ANY;
			}
		} else {
			id.requirements.gender = IT_GENDER_ANY;
		}

		t_str = tbl.get_or("Loc", std::string(""));
		if (!t_str.empty()) {
			if (t_str.compare("NONE") == 0) { id.equip_location_mask = IT_EQPM_NONE; }
			else if (t_str.compare("HEAD_LOW") == 0) { id.equip_location_mask = IT_EQPM_HEAD_LOW; }
			else if (t_str.compare("HEAD_MID") == 0) { id.equip_location_mask = IT_EQPM_HEAD_MID; }
			else if (t_str.compare("HEAD_TOP") == 0) { id.equip_location_mask = IT_EQPM_HEAD_TOP; }
			else if (t_str.compare("HAND_R") == 0) { id.equip_location_mask = IT_EQPM_HAND_R; }
			else if (t_str.compare("HAND_L") == 0) { id.equip_location_mask = IT_EQPM_HAND_L; }
			else if (t_str.compare("ARMOR") == 0) { id.equip_location_mask = IT_EQPM_ARMOR; }
			else if (t_str.compare("SHOES") == 0) { id.equip_location_mask = IT_EQPM_SHOES; }
			else if (t_str.compare("GARMENT") == 0) { id.equip_location_mask = IT_EQPM_GARMENT; }
			else if (t_str.compare("ACC_L") == 0) { id.equip_location_mask = IT_EQPM_ACC_L; }
			else if (t_str.compare("ACC_R") == 0) { id.equip_location_mask = IT_EQPM_ACC_R; }
			else if (t_str.compare("COSTUME_HEAD_TOP") == 0) { id.equip_location_mask = IT_EQPM_COSTUME_HEAD_TOP; }
			else if (t_str.compare("COSTUME_HEAD_MID") == 0) { id.equip_location_mask = IT_EQPM_COSTUME_HEAD_MID; }
			else if (t_str.compare("COSTUME_HEAD_LOW") == 0) { id.equip_location_mask = IT_EQPM_COSTUME_HEAD_LOW; }
			else if (t_str.compare("COSTUME_GARMENT") == 0) { id.equip_location_mask = IT_EQPM_COSTUME_GARMENT; }
			else if (t_str.compare("AMMO") == 0) { id.equip_location_mask = IT_EQPM_AMMO; }
			else if (t_str.compare("SHADOW_ARMOR") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_ARMOR; }
			else if (t_str.compare("SHADOW_WEAPON") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_WEAPON; }
			else if (t_str.compare("SHADOW_SHIELD") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_SHIELD; }
			else if (t_str.compare("SHADOW_SHOES") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_SHOES; }
			else if (t_str.compare("SHADOW_ACC_R") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_ACC_R; }
			else if (t_str.compare("SHADOW_ACC_L") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_ACC_L; }
			else if (t_str.compare("WEAPON") == 0) { id.equip_location_mask = IT_EQPM_WEAPON; }
			else if (t_str.compare("SHIELD") == 0) { id.equip_location_mask = IT_EQPM_SHIELD; }
			else if (t_str.compare("ARMS") == 0) { id.equip_location_mask = IT_EQPM_ARMS; }
			else if (t_str.compare("HELM") == 0) { id.equip_location_mask = IT_EQPM_HELM; }
			else if (t_str.compare("ACC") == 0) { id.equip_location_mask = IT_EQPM_ACC; }
			else if (t_str.compare("COSTUME") == 0) { id.equip_location_mask = IT_EQPM_COSTUME; }
			else if (t_str.compare("SHADOW_ACC") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_ACC; }
			else if (t_str.compare("SHADOW_ARMS") == 0) { id.equip_location_mask = IT_EQPM_SHADOW_ARMS; }
			else {
				ZoneLog->error("Invalid Loc '{}' for item '{}' ID {} in file '{}', skipping...", t_str, id.aegis_name, id.item_id, file_path);
				id.equip_location_mask = IT_EQPM_NONE;
			}
		} else {
			id.equip_location_mask = IT_EQPM_NONE;
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

	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "refine_db.lua";

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
		ZoneLog->info("Loaded {} entries from '{}' ({}µs).", total_entries, file_path, std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
	} catch(const std::exception &e) {
		ZoneLog->error("{} in file '{}'", e.what(), file_path);
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
			ZoneLog->error("Invalid type for entry 'Rates' table '{}' in file '{}'. Skipping...", table_name, file_path);
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
		ZoneLog->error("Non-existent configuration for entry 'Rates' table '{}' in file '{}'. Skipping...", table_name, file_path);
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

	int total_entries = 0;

	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "weapon_target_size_modifiers.lua";

	try {
		lua.script_file(file_path);

		sol::table size_mod_tbl = lua["weapon_target_size_modifiers"];

		for (int i = IT_WT_FIST; i < IT_WT_MAX; i++) {
			std::shared_ptr<std::array<uint8_t, ESZ_MAX>> arr = std::make_shared<std::array<uint8_t, ESZ_MAX>>();
			for (int j = ESZ_SMALL; j < ESZ_MAX; j++) {
				std::string size = j == ESZ_SMALL ? "Small" : j == ESZ_MEDIUM ? "Medium" : "Large";
				try {
					(*arr)[j] = size_mod_tbl[get_weapon_type_name((item_weapon_type) i)][size];
				} catch (std::exception &err) {
					ZoneLog->error("Weapon target size modifier was not found for weapon type {} size {}, defaulting to 100%...", get_weapon_type_name((item_weapon_type) i), size);
					(*arr)[j] = 100;
				}
			}
			_weapon_target_size_modifiers_db.insert((item_weapon_type) i, arr);
			total_entries++;
		}
		auto stop = std::chrono::high_resolution_clock::now();
		ZoneLog->info("Loaded {} entries from '{}' ({}µs).", total_entries, file_path, std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
	} catch(const std::exception &e) {
		ZoneLog->error("{} in file '{}'", e.what(), file_path);
		return false;
	}

	return true;
}

bool ItemDatabase::load_weapon_attribute_modifiers_db()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);

	int total_entries = 0;

	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "weapon_attribute_modifiers.lua";

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

		for (int i = IT_LVL_WEP_1; i < IT_LVL_MAX; i++) {
			std::shared_ptr<std::array<std::array<uint8_t, IT_ELE_MAX>, IT_ELE_MAX>> arr = std::make_shared<std::array<std::array<uint8_t, IT_ELE_MAX>, IT_ELE_MAX>>();
			for (int j = IT_ELE_NEUTRAL; j < IT_ELE_MAX; j++) {
				for (int k = IT_ELE_NEUTRAL; k < IT_ELE_MAX; k++) {
					try {
						(*arr)[j][k] = attr_mod_tbl[i][attr_s[j].ele_name][k + 1];
					} catch (std::exception &err) {
						ZoneLog->error("Weapon target attribute modifier was not found for weapon type {} attribute [{}][{}], defaulting to 100%...", get_weapon_type_name((item_weapon_type) i), attr_s[j].ele_name, attr_s[k].ele_name);
						(*arr)[j][k] = 100;
					}
					total_entries++;
				}
			}
			_weapon_attribute_modifiers_db.insert((item_level_type) i, arr);
		}
		auto stop = std::chrono::high_resolution_clock::now();
		ZoneLog->info("Loaded {} entries from '{}' ({}µs).", total_entries, file_path, std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
	} catch(const std::exception &e) {
		ZoneLog->error("{} in file '{}'", e.what(), file_path);
		return false;
	}

	return true;
}
