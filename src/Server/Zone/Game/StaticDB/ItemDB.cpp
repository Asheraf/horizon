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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "ItemDB.hpp"
#include "Server/Zone/Game/StaticDB/StaticDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Zone.hpp"
#include <chrono>

bool Horizon::Zone::Game::ItemDB::load()
{
	sol::state lua;
	auto start = std::chrono::high_resolution_clock::now();

	lua.open_libraries(sol::lib::base);

	int total_entries = 0;

	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "item_db.lua";

	try {
		lua.script_file(file_path);
		sol::table item_tbl = lua.get<sol::table>("item_db");
		total_entries = load_items(item_tbl);
		auto stop = std::chrono::high_resolution_clock::now();
		ZoneLog->info("Loaded {} entries from '{}' ({}µs).", total_entries, file_path, std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count());
	} catch(const std::exception &e) {
		ZoneLog->error("ItemDB::load: {}", e.what());
		return false;
	}

	return true;
}

int Horizon::Zone::Game::ItemDB::load_items(sol::table &item_tbl)
{
	item_tbl.for_each([this](sol::object const &key, sol::object const &value) {
		uint32_t item_id = key.as<uint32_t>(), t_int = 0;
		sol::table tbl = value.as<sol::table>();
		std::string t_str;
		item_data id;

		id.aegis_name = tbl.get_or("AegisName", std::string(""));
		if (id.aegis_name.empty()) {
			ZoneLog->error("ItemDB::load_items: Invalid or non-existent mandatory field 'AegisName' for entry {}. Skipping...", item_id);
			return;
		}

		id.name = tbl.get_or("Name", std::string(""));
		if (id.name.empty()) {
			ZoneLog->error("ItemDB::load_items: Invalid or non-existent mandatory field 'Name' for entry {}. Skipping...", item_id);
			return;
		}

		t_str = tbl.get_or("Type", std::string(""));
		if (!t_str.empty()) {
			if (t_str.compare("IT_TYPE_HEALING") == 0) {
				id.type = IT_TYPE_HEALING;
			} else if (t_str.compare("IT_TYPE_UNKNOWN") == 0) {
				id.type = IT_TYPE_UNKNOWN;
			} else if (t_str.compare("IT_TYPE_USABLE") == 0) {
				id.type = IT_TYPE_USABLE;
			} else if (t_str.compare("IT_TYPE_ETC") == 0) {
				id.type = IT_TYPE_ETC;
			} else if (t_str.compare("IT_TYPE_WEAPON") == 0) {
				id.type = IT_TYPE_WEAPON;
			} else if (t_str.compare("IT_TYPE_ARMOR") == 0) {
				id.type = IT_TYPE_ARMOR;
			} else if (t_str.compare("IT_TYPE_CARD") == 0) {
				id.type = IT_TYPE_CARD;
			} else if (t_str.compare("IT_TYPE_PET_EGG") == 0) {
				id.type = IT_TYPE_PET_EGG;
			} else if (t_str.compare("IT_TYPE_PET_ARMOR") == 0) {
				id.type = IT_TYPE_PET_ARMOR;
			} else if (t_str.compare("IT_TYPE_UNKNOWN2") == 0) {
				id.type = IT_TYPE_UNKNOWN2;
			} else if (t_str.compare("IT_TYPE_AMMO") == 0) {
				id.type = IT_TYPE_AMMO;
			} else if (t_str.compare("IT_TYPE_CONSUMPTION_DELAY") == 0) {
				id.type = IT_TYPE_CONSUMPTION_DELAY;
			} else if (t_str.compare("IT_TYPE_CASH") == 0) {
				id.type = IT_TYPE_CASH;
			} else {
				ZoneLog->error("Invalid value for field 'Type' in item '{}', defaulting to 'IT_TYPE_ETC'.", item_id);
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
					if (t_str.compare("WT_DAGGER") == 0) { id.sub_type.weapon_t = WT_DAGGER; }
					else if (t_str.compare("WT_1HSWORD") == 0) { id.sub_type.weapon_t = WT_1HSWORD; }
					else if (t_str.compare("WT_2HSWORD") == 0) { id.sub_type.weapon_t = WT_2HSWORD; }
					else if (t_str.compare("WT_1HSPEAR") == 0) { id.sub_type.weapon_t = WT_1HSPEAR; }
					else if (t_str.compare("WT_2HSPEAR") == 0) { id.sub_type.weapon_t = WT_2HSPEAR; }
					else if (t_str.compare("WT_1HAXE") == 0) { id.sub_type.weapon_t = WT_1HAXE; }
					else if (t_str.compare("WT_2HAXE") == 0) { id.sub_type.weapon_t = WT_2HAXE; }
					else if (t_str.compare("WT_1HMACE") == 0) { id.sub_type.weapon_t = WT_1HMACE; }
					else if (t_str.compare("WT_2HMACE") == 0) { id.sub_type.weapon_t = WT_2HMACE; }
					else if (t_str.compare("WT_STAFF") == 0) { id.sub_type.weapon_t = WT_STAFF; }
					else if (t_str.compare("WT_BOW") == 0) { id.sub_type.weapon_t = WT_BOW; }
					else if (t_str.compare("WT_KNUCKLE") == 0) { id.sub_type.weapon_t = WT_KNUCKLE; }
					else if (t_str.compare("WT_MUSICAL") == 0) { id.sub_type.weapon_t = WT_MUSICAL; }
					else if (t_str.compare("WT_WHIP") == 0) { id.sub_type.weapon_t = WT_WHIP; }
					else if (t_str.compare("WT_BOOK") == 0) { id.sub_type.weapon_t = WT_BOOK; }
					else if (t_str.compare("WT_KATAR") == 0) { id.sub_type.weapon_t = WT_KATAR; }
					else if (t_str.compare("WT_REVOLVER") == 0) { id.sub_type.weapon_t = WT_REVOLVER; }
					else if (t_str.compare("WT_RIFLE") == 0) { id.sub_type.weapon_t = WT_RIFLE; }
					else if (t_str.compare("WT_GATLING") == 0) { id.sub_type.weapon_t = WT_GATLING; }
					else if (t_str.compare("WT_SHOTGUN") == 0) { id.sub_type.weapon_t = WT_SHOTGUN; }
					else if (t_str.compare("WT_GRENADE") == 0) { id.sub_type.weapon_t = WT_GRENADE; }
					else if (t_str.compare("WT_HUUMA") == 0) { id.sub_type.weapon_t = WT_HUUMA; }
					else if (t_str.compare("WT_2HSTAFF") == 0) { id.sub_type.weapon_t = WT_2HSTAFF; }
					else if (t_str.compare("WT_SHIELD") == 0) { id.sub_type.weapon_t = WT_SHIELD; }
					else {
						ZoneLog->error("Invalid value for field 'Subtype' in entry '{}', defaulting to 'WT_FIST'.", item_id);
						id.sub_type.weapon_t = WT_FIST;
					}
					break;
				case IT_TYPE_AMMO:
					if (t_str.compare("AMMO_TYPE_ARROW") == 0) { id.sub_type.ammo_t = AMMO_TYPE_ARROW; }
					else if (t_str.compare("AMMO_TYPE_DAGGER") == 0) { id.sub_type.ammo_t = AMMO_TYPE_DAGGER; }
					else if (t_str.compare("AMMO_TYPE_BULLET") == 0) { id.sub_type.ammo_t = AMMO_TYPE_BULLET; }
					else if (t_str.compare("AMMO_TYPE_SHELL") == 0) { id.sub_type.ammo_t = AMMO_TYPE_SHELL; }
					else if (t_str.compare("AMMO_TYPE_GRENADE") == 0) { id.sub_type.ammo_t = AMMO_TYPE_GRENADE; }
					else if (t_str.compare("AMMO_TYPE_SHURIKEN") == 0) { id.sub_type.ammo_t = AMMO_TYPE_SHURIKEN; }
					else if (t_str.compare("AMMO_TYPE_KUNAI") == 0) { id.sub_type.ammo_t = AMMO_TYPE_KUNAI; }
					else if (t_str.compare("AMMO_TYPE_CANNONBALL") == 0) { id.sub_type.ammo_t = AMMO_TYPE_CANNONBALL; }
					else if (t_str.compare("AMMO_TYPE_THROWABLE_WEAPON") == 0) { id.sub_type.ammo_t = AMMO_TYPE_THROWABLE_WEAPON; }
					else if (t_str.compare("AMMO_TYPE_NON") == 0) { id.sub_type.ammo_t = AMMO_TYPE_NONE; }
					else {
						ZoneLog->error("Invalid value for field 'Subtype' in entry '{}', defaulting to 'AMMO_TYPE_NONE'.", item_id);
						id.sub_type.ammo_t = AMMO_TYPE_NONE;
					}
					break;
				default:
					ZoneLog->error("Field 'Subtype' is only allowed for IT_TYPE_WEAPON and IT_TYPE_AMMO in entry '{}', ignoring...", item_id);
					break;
			}
		}

		id.value_buy = tbl.get_or("Buy", 0);
		id.value_sell = tbl.get_or("Sell", 0);
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
			job_tbl.for_each([&id](sol::object const &key, sol::object const &value) {
				std::string job_name = key.as<std::string>();
				bool enable = value.as<bool>();

				if (job_name.compare("All") == 0) {
					if (enable)
						id.requirements.job_mask |= UINT64_MAX;
					else
						id.requirements.job_mask &= ~UINT64_MAX;
					return;
				}

				job_classes job_id = StaticDB->get_job_db().get_job_class_by_name(job_name);

				if (job_id == JOB_INVALID) {
					ZoneLog->error("Invalid Job '{}' specified in entry, skipping...", job_name);
					return;
				}

				job_class_mask mask_id = StaticDB->get_job_db().job_id_to_mask(job_id);

				if (enable)
					id.requirements.job_mask |= mask_id;
				else
					id.requirements.job_mask &= ~mask_id;
			});
		} else if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::string) {
			std::string job_name = maybe_job_tbl.value().as<std::string>();
			job_classes job_id = StaticDB->get_job_db().get_job_class_by_name(job_name);
			job_class_mask mask_id = StaticDB->get_job_db().job_id_to_mask(job_id);
			id.requirements.job_mask |= mask_id;
		} else if (maybe_job_tbl && maybe_job_tbl.value().get_type() == sol::type::number) {

		} else {
			id.requirements.job_mask = 0;
		}

		t_str = tbl.get_or("Gender", std::string(""));
		if (!t_str.empty()) {
			if (t_str.compare("IT_GENDER_FEMALE") == 0) { id.requirements.gender = IT_GENDER_FEMALE; }
			else if (t_str.compare("IT_GENDER_MALE") == 0) { id.requirements.gender = IT_GENDER_MALE; }
			else if (t_str.compare("IT_GENDER_ANY") == 0) { id.requirements.gender = IT_GENDER_ANY; }
			else {
				ZoneLog->error("Invalid Gender '{}' for item '{}' specified in entry {}, skipping...", t_str, id.aegis_name, item_id);
				id.requirements.gender = IT_GENDER_ANY;
			}
		} else {
			id.requirements.gender = IT_GENDER_ANY;
		}

		t_str = tbl.get_or("Loc", std::string(""));
		if (!t_str.empty()) {
			if (t_str.compare("EQP_NONE") == 0) { id.equip_location_mask = EQP_NONE; }
			else if (t_str.compare("EQP_HEAD_LOW") == 0) { id.equip_location_mask = EQP_HEAD_LOW; }
			else if (t_str.compare("EQP_HEAD_MID") == 0) { id.equip_location_mask = EQP_HEAD_MID; }
			else if (t_str.compare("EQP_HEAD_TOP") == 0) { id.equip_location_mask = EQP_HEAD_TOP; }
			else if (t_str.compare("EQP_HAND_R") == 0) { id.equip_location_mask = EQP_HAND_R; }
			else if (t_str.compare("EQP_HAND_L") == 0) { id.equip_location_mask = EQP_HAND_L; }
			else if (t_str.compare("EQP_ARMOR") == 0) { id.equip_location_mask = EQP_ARMOR; }
			else if (t_str.compare("EQP_SHOES") == 0) { id.equip_location_mask = EQP_SHOES; }
			else if (t_str.compare("EQP_GARMENT") == 0) { id.equip_location_mask = EQP_GARMENT; }
			else if (t_str.compare("EQP_ACC_L") == 0) { id.equip_location_mask = EQP_ACC_L; }
			else if (t_str.compare("EQP_ACC_R") == 0) { id.equip_location_mask = EQP_ACC_R; }
			else if (t_str.compare("EQP_COSTUME_HEAD_TOP") == 0) { id.equip_location_mask = EQP_COSTUME_HEAD_TOP; }
			else if (t_str.compare("EQP_COSTUME_HEAD_MID") == 0) { id.equip_location_mask = EQP_COSTUME_HEAD_MID; }
			else if (t_str.compare("EQP_COSTUME_HEAD_LOW") == 0) { id.equip_location_mask = EQP_COSTUME_HEAD_LOW; }
			else if (t_str.compare("EQP_COSTUME_GARMENT") == 0) { id.equip_location_mask = EQP_COSTUME_GARMENT; }
			else if (t_str.compare("EQP_AMMO") == 0) { id.equip_location_mask = EQP_AMMO; }
			else if (t_str.compare("EQP_SHADOW_ARMOR") == 0) { id.equip_location_mask = EQP_SHADOW_ARMOR; }
			else if (t_str.compare("EQP_SHADOW_WEAPON") == 0) { id.equip_location_mask = EQP_SHADOW_WEAPON; }
			else if (t_str.compare("EQP_SHADOW_SHIELD") == 0) { id.equip_location_mask = EQP_SHADOW_SHIELD; }
			else if (t_str.compare("EQP_SHADOW_SHOES") == 0) { id.equip_location_mask = EQP_SHADOW_SHOES; }
			else if (t_str.compare("EQP_SHADOW_ACC_R") == 0) { id.equip_location_mask = EQP_SHADOW_ACC_R; }
			else if (t_str.compare("EQP_SHADOW_ACC_L") == 0) { id.equip_location_mask = EQP_SHADOW_ACC_L; }
			else if (t_str.compare("EQP_WEAPON") == 0) { id.equip_location_mask = EQP_WEAPON; }
			else if (t_str.compare("EQP_SHIELD") == 0) { id.equip_location_mask = EQP_SHIELD; }
			else if (t_str.compare("EQP_ARMS") == 0) { id.equip_location_mask = EQP_ARMS; }
			else if (t_str.compare("EQP_HELM") == 0) { id.equip_location_mask = EQP_HELM; }
			else if (t_str.compare("EQP_ACC") == 0) { id.equip_location_mask = EQP_ACC; }
			else if (t_str.compare("EQP_COSTUME") == 0) { id.equip_location_mask = EQP_COSTUME; }
			else if (t_str.compare("EQP_SHADOW_ACC") == 0) { id.equip_location_mask = EQP_SHADOW_ACC; }
			else if (t_str.compare("EQP_SHADOW_ARMS") == 0) { id.equip_location_mask = EQP_SHADOW_ARMS; }
			else {
				ZoneLog->error("Invalid Loc '{}' for item '{}' specified in entry {}, skipping...", t_str, id.aegis_name, item_id);
				id.equip_location_mask = EQP_NONE;
			}
		} else {
			id.equip_location_mask = EQP_NONE;
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

		_item_db.insert(item_id, id);
	});

	return _item_db.size();
}
