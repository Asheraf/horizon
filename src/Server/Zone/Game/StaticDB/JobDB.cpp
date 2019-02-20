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

#include "JobDB.hpp"
#include "Server/Zone/Zone.hpp"

Horizon::Zone::Game::JobDB::JobDB()
{
	_name2id_list.emplace("Novice", JOB_NOVICE);
	_name2id_list.emplace("Swordsman", JOB_SWORDMAN);
	_name2id_list.emplace("Magician", JOB_MAGE);
	_name2id_list.emplace("Archer", JOB_ARCHER);
	_name2id_list.emplace("Acolyte", JOB_ACOLYTE);
	_name2id_list.emplace("Merchant", JOB_MERCHANT);
	_name2id_list.emplace("Thief", JOB_THIEF);
	_name2id_list.emplace("Knight", JOB_KNIGHT);
	_name2id_list.emplace("Priest", JOB_PRIEST);
	_name2id_list.emplace("Wizard", JOB_WIZARD);
	_name2id_list.emplace("Blacksmith", JOB_BLACKSMITH);
	_name2id_list.emplace("Hunter", JOB_HUNTER);
	_name2id_list.emplace("Assassin", JOB_ASSASSIN);
	_name2id_list.emplace("Crusader", JOB_CRUSADER);
	_name2id_list.emplace("Monk", JOB_MONK);
	_name2id_list.emplace("Sage", JOB_SAGE);
	_name2id_list.emplace("Rogue", JOB_ROGUE);
	_name2id_list.emplace("Alchemist", JOB_ALCHEMIST);
	_name2id_list.emplace("Bard", JOB_BARD);
	_name2id_list.emplace("Dancer", JOB_DANCER);
	_name2id_list.emplace("Super_Novice", JOB_SUPER_NOVICE);
	_name2id_list.emplace("Gunslinger", JOB_GUNSLINGER);
	_name2id_list.emplace("Ninja", JOB_NINJA);
	_name2id_list.emplace("Novice_High", JOB_NOVICE_HIGH);
	_name2id_list.emplace("Swordsman_High", JOB_SWORDMAN_HIGH);
	_name2id_list.emplace("Magician_High", JOB_MAGE_HIGH);
	_name2id_list.emplace("Archer_High", JOB_ARCHER_HIGH);
	_name2id_list.emplace("Acolyte_High", JOB_ACOLYTE_HIGH);
	_name2id_list.emplace("Merchant_High", JOB_MERCHANT_HIGH);
	_name2id_list.emplace("Thief_High", JOB_THIEF_HIGH);
	_name2id_list.emplace("Lord_Knight", JOB_LORD_KNIGHT);
	_name2id_list.emplace("High_Priest", JOB_HIGH_PRIEST);
	_name2id_list.emplace("High_Wizard", JOB_HIGH_WIZARD);
	_name2id_list.emplace("Whitesmith", JOB_WHITESMITH);
	_name2id_list.emplace("Sniper", JOB_SNIPER);
	_name2id_list.emplace("Assassin_Cross", JOB_ASSASSIN_CROSS);
	_name2id_list.emplace("Paladin", JOB_PALADIN);
	_name2id_list.emplace("Champion", JOB_CHAMPION);
	_name2id_list.emplace("Professor", JOB_PROFESSOR);
	_name2id_list.emplace("Stalker", JOB_STALKER);
	_name2id_list.emplace("Creator", JOB_CREATOR);
	_name2id_list.emplace("Clown", JOB_CLOWN);
	_name2id_list.emplace("Gypsy", JOB_GYPSY);
	_name2id_list.emplace("Baby_Novice", JOB_BABY);
	_name2id_list.emplace("Baby_Swordsman", JOB_BABY_SWORDMAN);
	_name2id_list.emplace("Baby_Magician", JOB_BABY_MAGE);
	_name2id_list.emplace("Baby_Archer", JOB_BABY_ARCHER);
	_name2id_list.emplace("Baby_Acolyte", JOB_BABY_ACOLYTE);
	_name2id_list.emplace("Baby_Merchant", JOB_BABY_MERCHANT);
	_name2id_list.emplace("Baby_Thief", JOB_BABY_THIEF);
	_name2id_list.emplace("Baby_Knight", JOB_BABY_KNIGHT);
	_name2id_list.emplace("Baby_Priest", JOB_BABY_PRIEST);
	_name2id_list.emplace("Baby_Wizard", JOB_BABY_WIZARD);
	_name2id_list.emplace("Baby_Blacksmith", JOB_BABY_BLACKSMITH);
	_name2id_list.emplace("Baby_Hunter", JOB_BABY_HUNTER);
	_name2id_list.emplace("Baby_Assassin", JOB_BABY_ASSASSIN);
	_name2id_list.emplace("Baby_Crusader", JOB_BABY_CRUSADER);
	_name2id_list.emplace("Baby_Monk", JOB_BABY_MONK);
	_name2id_list.emplace("Baby_Sage", JOB_BABY_SAGE);
	_name2id_list.emplace("Baby_Rogue", JOB_BABY_ROGUE);
	_name2id_list.emplace("Baby_Alchemist", JOB_BABY_ALCHEMIST);
	_name2id_list.emplace("Baby_Bard", JOB_BABY_BARD);
	_name2id_list.emplace("Baby_Dancer", JOB_BABY_DANCER);
	_name2id_list.emplace("Super_Baby", JOB_SUPER_BABY);
	_name2id_list.emplace("Taekwon", JOB_TAEKWON);
	_name2id_list.emplace("Star_Gladiator", JOB_STAR_GLADIATOR);
	_name2id_list.emplace("Soul_Linker", JOB_SOUL_LINKER);
	_name2id_list.emplace("Gangsi", JOB_GANGSI);
	_name2id_list.emplace("Death_Knight", JOB_DEATH_KNIGHT);
	_name2id_list.emplace("Dark_Collector", JOB_DARK_COLLECTOR);
	_name2id_list.emplace("Rune_Knight", JOB_RUNE_KNIGHT);
	_name2id_list.emplace("Warlock", JOB_WARLOCK);
	_name2id_list.emplace("Ranger", JOB_RANGER);
	_name2id_list.emplace("Arch_Bishop", JOB_ARCH_BISHOP);
	_name2id_list.emplace("Mechanic", JOB_MECHANIC);
	_name2id_list.emplace("Guillotine_Cross", JOB_GUILLOTINE_CROSS);
	_name2id_list.emplace("Rune_Knight_Trans", JOB_RUNE_KNIGHT_T);
	_name2id_list.emplace("Warlock_Trans", JOB_WARLOCK_T);
	_name2id_list.emplace("Ranger_Trans", JOB_RANGER_T);
	_name2id_list.emplace("Arch_Bishop_Trans", JOB_ARCH_BISHOP_T);
	_name2id_list.emplace("Mechanic_Trans", JOB_MECHANIC_T);
	_name2id_list.emplace("Guillotine_Cross_Trans", JOB_GUILLOTINE_CROSS_T);
	_name2id_list.emplace("Royal_Guard", JOB_ROYAL_GUARD);
	_name2id_list.emplace("Sorcerer", JOB_SORCERER);
	_name2id_list.emplace("Minstrel", JOB_MINSTREL);
	_name2id_list.emplace("Wanderer", JOB_WANDERER);
	_name2id_list.emplace("Sura", JOB_SURA);
	_name2id_list.emplace("Genetic", JOB_GENETIC);
	_name2id_list.emplace("Shadow_Chaser", JOB_SHADOW_CHASER);
	_name2id_list.emplace("Royal_Guard_Trans", JOB_ROYAL_GUARD_T);
	_name2id_list.emplace("Sorcerer_Trans", JOB_SORCERER_T);
	_name2id_list.emplace("Minstrel_Trans", JOB_MINSTREL_T);
	_name2id_list.emplace("Wanderer_Trans", JOB_WANDERER_T);
	_name2id_list.emplace("Sura_Trans", JOB_SURA_T);
	_name2id_list.emplace("Genetic_Trans", JOB_GENETIC_T);
	_name2id_list.emplace("Shadow_Chaser_Trans", JOB_SHADOW_CHASER_T);
	_name2id_list.emplace("Baby_Rune_Knight", JOB_BABY_RUNE);
	_name2id_list.emplace("Baby_Warlock", JOB_BABY_WARLOCK);
	_name2id_list.emplace("Baby_Ranger", JOB_BABY_RANGER);
	_name2id_list.emplace("Baby_Arch_Bishop", JOB_BABY_BISHOP);
	_name2id_list.emplace("Baby_Mechanic", JOB_BABY_MECHANIC);
	_name2id_list.emplace("Baby_Guillotine_Cross", JOB_BABY_CROSS);
	_name2id_list.emplace("Baby_Royal_Guard", JOB_BABY_GUARD);
	_name2id_list.emplace("Baby_Sorcerer", JOB_BABY_SORCERER);
	_name2id_list.emplace("Baby_Minstrel", JOB_BABY_MINSTREL);
	_name2id_list.emplace("Baby_Wanderer", JOB_BABY_WANDERER);
	_name2id_list.emplace("Baby_Sura", JOB_BABY_SURA);
	_name2id_list.emplace("Baby_Genetic", JOB_BABY_GENETIC);
	_name2id_list.emplace("Baby_Shadow_Chaser", JOB_BABY_CHASER);
	_name2id_list.emplace("Expanded_Super_Novice", JOB_SUPER_NOVICE_E);
	_name2id_list.emplace("Expanded_Super_Baby", JOB_SUPER_BABY_E);
	_name2id_list.emplace("Kagerou", JOB_KAGEROU);
	_name2id_list.emplace("Oboro", JOB_OBORO);
	_name2id_list.emplace("Rebellion", JOB_REBELLION);
	_name2id_list.emplace("Summoner", JOB_SUMMONER);
}

job_classes Horizon::Zone::Game::JobDB::get_job_class_by_name(std::string name) const
{
	auto id = _name2id_list.find(name);

	if (id == _name2id_list.end())
		return JOB_INVALID;

	return job_classes(id->second);
}

bool Horizon::Zone::Game::JobDB::load()
{
	sol::state lua;

	int total_entries = 0;
	std::string tmp_string;
	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "job_db.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table job_tbl = lua.get<sol::table>("job_db");
		total_entries = load_job(job_tbl);
		ZoneLog->info("Loaded {} entries from '{}'", total_entries, file_path);
	} catch(const std::exception &e) {
		ZoneLog->error("JobDB::load: {}.", e.what());
		return false;
	}

	return true;
}

int Horizon::Zone::Game::JobDB::load_job(sol::table &job_tbls, std::string name)
{
	int count = 0;

	if (name.empty()) {
		job_tbls.for_each([this, &count](sol::object const &/*key*/, sol::object const &value) {
			job_db_data data;
			sol::table job_tbl = value.as<sol::table>();
			std::string name = job_tbl.get_or("Name", std::string(""));
			job_classes jc = get_job_class_by_name(name);
			if (load_job_internal(job_tbl, data, name) == true) {
				_job_db.emplace(jc, data);
				count++;
			}
		});
	} else {
		sol::optional<sol::table> maybe_job = job_tbls.get<sol::optional<sol::table>>(name);
		if (maybe_job) {
			job_db_data data;
			job_classes jc = get_job_class_by_name(name);
			if (load_job_internal(maybe_job.value(), data, name) == true)
				_job_db.emplace(jc, data);
		} else {
			ZoneLog->warn("JobDB::load_job: Job named '{}' was not found.", name);
		}
	}

	return count;
}

bool Horizon::Zone::Game::JobDB::load_job_internal(sol::table &job_tbl, job_db_data &data, std::string job_name)
{
	std::string t_str;

	t_str = job_tbl.get_or("BaseExpGroup", std::string(""));
	if (t_str.empty()) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existant BaseExpGroup for job '{}', skipping...", job_name);
		return false;
	}
	data._base_exp_group = t_str;

	t_str = job_tbl.get_or("JobExpGroup", std::string(""));
	if (t_str.empty()) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existant JobExpGroup for job '{}', skipping...", job_name);
		return false;
	}
	data._job_exp_group = t_str;

	t_str = job_tbl.get_or("Inherit", std::string(""));
	if (t_str.empty()) {
		// Max Weight
		data._max_weight = job_tbl.get_or("Weight", 20000);

		sol::optional<sol::table> aspd_tbl = job_tbl.get<sol::optional<sol::table>>("BaseASPD");
		if (aspd_tbl) {
			aspd_tbl.value().for_each([&data, &job_name] (sol::object const &key, sol::object const &value) {
				std::string w_name = key.as<std::string>();

				if (value.get_type() != sol::type::number) {
					ZoneLog->warn("JobDB::load_job_internal: Invalid entry in BaseASPD setting weapon {} for job '{}'.", w_name, job_name);
					return;
				}

				int val = value.as<int>();
				if (!w_name.compare("Fist")) {
					data._weapon_base_aspd[WT_FIST] = val;
				} else if (!w_name.compare("Dagger")) {
					data._weapon_base_aspd[WT_DAGGER] = val;
				} else if (!w_name.compare("Sword")) {
					data._weapon_base_aspd[WT_1HSWORD] = val;
				} else if (!w_name.compare("TwoHandSword")) {
					data._weapon_base_aspd[WT_2HSWORD] = val;
				} else if (!w_name.compare("Spear")) {
					data._weapon_base_aspd[WT_1HSPEAR] = val;
				} else if (!w_name.compare("TwoHandSpear")) {
					data._weapon_base_aspd[WT_2HSPEAR] = val;
				} else if (!w_name.compare("Axe")) {
					data._weapon_base_aspd[WT_1HAXE] = val;
				} else if (!w_name.compare("TwoHandAxe")) {
					data._weapon_base_aspd[WT_2HAXE] = val;
				} else if (!w_name.compare("Mace")) {
					data._weapon_base_aspd[WT_1HMACE] = val;
				} else if (!w_name.compare("TwoHandMace")) {
					data._weapon_base_aspd[WT_2HMACE] = val;
				} else if (!w_name.compare("Rod")) {
					data._weapon_base_aspd[WT_STAFF] = val;
				} else if (!w_name.compare("Bow")) {
					data._weapon_base_aspd[WT_BOW] = val;
				} else if (!w_name.compare("Knuckle")) {
					data._weapon_base_aspd[WT_KNUCKLE] = val;
				} else if (!w_name.compare("Instrument")) {
					data._weapon_base_aspd[WT_MUSICAL] = val;
				} else if (!w_name.compare("Whip")) {
					data._weapon_base_aspd[WT_WHIP] = val;
				} else if (!w_name.compare("Book")) {
					data._weapon_base_aspd[WT_BOOK] = val;
				} else if (!w_name.compare("Katar")) {
					data._weapon_base_aspd[WT_KATAR] = val;
				} else if (!w_name.compare("Revolver")) {
					data._weapon_base_aspd[WT_REVOLVER] = val;
				} else if (!w_name.compare("Rifle")) {
					data._weapon_base_aspd[WT_RIFLE] = val;
				} else if (!w_name.compare("GatlingGun")) {
					data._weapon_base_aspd[WT_GATLING] = val;
				} else if (!w_name.compare("Shotgun")) {
					data._weapon_base_aspd[WT_SHOTGUN] = val;
				} else if (!w_name.compare("GrenadeLauncher")) {
					data._weapon_base_aspd[WT_GRENADE] = val;
				} else if (!w_name.compare("FuumaShuriken")) {
					data._weapon_base_aspd[WT_HUUMA] = val;
				} else if (!w_name.compare("TwoHandRod")) {
					data._weapon_base_aspd[WT_2HSTAFF] = val;
				} else if (!w_name.compare("Shield")) {
					data._weapon_base_aspd[WT_SHIELD] = val;
				}
			});

		}
	} else {
		job_classes jc = get_job_class_by_name(t_str);

		if (jc == JOB_INVALID) {
			ZoneLog->warn("JobDB::load_job_internal: Unable to inherit from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", t_str, job_name);
			return false;
		}

		auto jobi = _job_db.find(jc);
		if (jobi == _job_db.end()) {
			ZoneLog->warn("JobDB::load_job_internal: Unable to inherit from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", t_str, job_name);
			return false;
		}

		data._weapon_base_aspd = jobi->second._weapon_base_aspd;
		data._max_weight = jobi->second._max_weight;
	}

	if (load_hp_sp_table(job_tbl, data, job_name, "HPTable") == false)
		return false;

	if (load_hp_sp_table(job_tbl, data, job_name, "SPTable") == false)
		return false;

	return true;
}

bool Horizon::Zone::Game::JobDB::load_hp_sp_table(sol::table &job_tbl, job_db_data &data, std::string &job_name, std::string table_name)
{
	std::string t_str;

	t_str = job_tbl.get_or("Inherit", t_str);
	t_str = job_tbl.get_or("InheritHP", t_str);
	t_str = job_tbl.get_or("InheritSP", t_str);

	if (!t_str.empty()) {
		job_classes jc = get_job_class_by_name(t_str);
		if (jc == JOB_INVALID) {
			ZoneLog->warn("JobDB::load_job_internal: Unable to inherit from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", t_str, job_name);
			return false;
		}
		auto jobi = _job_db.find(jc);
		if (jobi == _job_db.end()) {
			ZoneLog->warn("JobDB::load_hp_sp_table: Unable to inherit {} from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", table_name, t_str, job_name);
			return false;
		}
		job_db_data inherited_data = jobi->second;

		data._hp_table = inherited_data._hp_table;
		data._sp_table = inherited_data._sp_table;
		return true;
	}

	sol::optional<sol::table> tbl = job_tbl.get<sol::optional<sol::table>>(table_name);

	if (!tbl) {
		ZoneLog->warn("JobDB::load_hp_sp_table: Job '{}' does not have a {}, skipping...", job_name, table_name);
		return false;
	}

	tbl.value().for_each([&data, &job_name, &table_name](sol::object const &key, sol::object const &val) {
		if (key.get_type() != sol::type::number) {
			ZoneLog->warn("JobDB::load_hp_sp_table: Invalid index {} for entry {} in job '{}', skipping...", key.as<int>(), job_name, table_name);
			return;
		}

		if (!table_name.compare("HPTable"))
			data._hp_table.push_back(val.as<int>());
		else if (!table_name.compare("SPTable"))
			data._sp_table.push_back(val.as<int>());
	});

	return true;
}

job_class_mask Horizon::Zone::Game::JobDB::job_id_to_mask(job_classes job_id) const
{
	switch (job_id)
	{
	//Novice And 1-1 Jobs
	case JOB_NOVICE:                return JMASK_NOVICE;
	case JOB_SWORDMAN:              return JMASK_SWORDMAN;
	case JOB_MAGE:                  return JMASK_MAGE;
	case JOB_ARCHER:                return JMASK_ARCHER;
	case JOB_ACOLYTE:               return JMASK_ACOLYTE;
	case JOB_MERCHANT:              return JMASK_MERCHANT;
	case JOB_THIEF:                 return JMASK_THIEF;
	case JOB_TAEKWON:               return JMASK_TAEKWON;
	case JOB_WEDDING:               return JMASK_WEDDING;
	case JOB_GUNSLINGER:            return JMASK_GUNSLINGER;
	case JOB_NINJA:                 return JMASK_NINJA;
	case JOB_XMAS:                  return JMASK_XMAS;
	case JOB_SUMMER:                return JMASK_SUMMER;
	case JOB_GANGSI:                return JMASK_GANGSI;
	case JOB_SUMMONER:              return JMASK_SUMMONER;
	//2-1 Jobs
	case JOB_SUPER_NOVICE:          return JMASK_SUPER_NOVICE;
	case JOB_KNIGHT:                return JMASK_KNIGHT;
	case JOB_WIZARD:                return JMASK_WIZARD;
	case JOB_HUNTER:                return JMASK_HUNTER;
	case JOB_PRIEST:                return JMASK_PRIEST;
	case JOB_BLACKSMITH:            return JMASK_BLACKSMITH;
	case JOB_ASSASSIN:              return JMASK_ASSASSIN;
	case JOB_STAR_GLADIATOR:        return JMASK_STAR_GLADIATOR;
	case JOB_KAGEROU:
	case JOB_OBORO:                 return JMASK_KAGEROUOBORO;
	case JOB_REBELLION:             return JMASK_REBELLION;
	case JOB_DEATH_KNIGHT:          return JMASK_DEATH_KNIGHT;
	//2-2 Jobs
	case JOB_CRUSADER:              return JMASK_CRUSADER;
	case JOB_SAGE:                  return JMASK_SAGE;
	case JOB_BARD:
	case JOB_DANCER:                return JMASK_BARDDANCER;
	case JOB_MONK:                  return JMASK_MONK;
	case JOB_ALCHEMIST:             return JMASK_ALCHEMIST;
	case JOB_ROGUE:                 return JMASK_ROGUE;
	case JOB_SOUL_LINKER:           return JMASK_SOUL_LINKER;
	case JOB_DARK_COLLECTOR:        return JMASK_DARK_COLLECTOR;
	//Trans Novice And Trans 1-1 Jobs
	case JOB_NOVICE_HIGH:           return JMASK_NOVICE_HIGH;
	case JOB_SWORDMAN_HIGH:         return JMASK_SWORDMAN_HIGH;
	case JOB_MAGE_HIGH:             return JMASK_MAGE_HIGH;
	case JOB_ARCHER_HIGH:           return JMASK_ARCHER_HIGH;
	case JOB_ACOLYTE_HIGH:          return JMASK_ACOLYTE_HIGH;
	case JOB_MERCHANT_HIGH:         return JMASK_MERCHANT_HIGH;
	case JOB_THIEF_HIGH:            return JMASK_THIEF_HIGH;
	//Trans 2-1 Jobs
	case JOB_LORD_KNIGHT:           return JMASK_LORD_KNIGHT;
	case JOB_HIGH_WIZARD:           return JMASK_HIGH_WIZARD;
	case JOB_SNIPER:                return JMASK_SNIPER;
	case JOB_HIGH_PRIEST:           return JMASK_HIGH_PRIEST;
	case JOB_WHITESMITH:            return JMASK_WHITESMITH;
	case JOB_ASSASSIN_CROSS:        return JMASK_ASSASSIN_CROSS;
	//Trans 2-2 Jobs
	case JOB_PALADIN:               return JMASK_PALADIN;
	case JOB_PROFESSOR:             return JMASK_PROFESSOR;
	case JOB_CLOWN:
	case JOB_GYPSY:                 return JMASK_CLOWNGYPSY;
	case JOB_CHAMPION:              return JMASK_CHAMPION;
	case JOB_CREATOR:               return JMASK_CREATOR;
	case JOB_STALKER:               return JMASK_STALKER;
	//Baby Novice And Baby 1-1 Jobs
	case JOB_BABY:                  return JMASK_BABY;
	case JOB_BABY_SWORDMAN:         return JMASK_BABY_SWORDMAN;
	case JOB_BABY_MAGE:             return JMASK_BABY_MAGE;
	case JOB_BABY_ARCHER:           return JMASK_BABY_ARCHER;
	case JOB_BABY_ACOLYTE:          return JMASK_BABY_ACOLYTE;
	case JOB_BABY_MERCHANT:         return JMASK_BABY_MERCHANT;
	case JOB_BABY_THIEF:            return JMASK_BABY_THIEF;
	//Baby 2-1 Jobs
	case JOB_SUPER_BABY:            return JMASK_SUPER_BABY;
	case JOB_BABY_KNIGHT:           return JMASK_BABY_KNIGHT;
	case JOB_BABY_WIZARD:           return JMASK_BABY_WIZARD;
	case JOB_BABY_HUNTER:           return JMASK_BABY_HUNTER;
	case JOB_BABY_PRIEST:           return JMASK_BABY_PRIEST;
	case JOB_BABY_BLACKSMITH:       return JMASK_BABY_BLACKSMITH;
	case JOB_BABY_ASSASSIN:         return JMASK_BABY_ASSASSIN;
	//Baby 2-2 Jobs
	case JOB_BABY_CRUSADER:         return JMASK_BABY_CRUSADER;
	case JOB_BABY_SAGE:             return JMASK_BABY_SAGE;
	case JOB_BABY_BARD:
	case JOB_BABY_DANCER:           return JMASK_BABY_BARDDANCER;
	case JOB_BABY_MONK:             return JMASK_BABY_MONK;
	case JOB_BABY_ALCHEMIST:        return JMASK_BABY_ALCHEMIST;
	case JOB_BABY_ROGUE:            return JMASK_BABY_ROGUE;
	//3-1 Jobs
	case JOB_SUPER_NOVICE_E:        return JMASK_SUPER_NOVICE_E;
	case JOB_RUNE_KNIGHT:           return JMASK_RUNE_KNIGHT;
	case JOB_WARLOCK:               return JMASK_WARLOCK;
	case JOB_RANGER:                return JMASK_RANGER;
	case JOB_ARCH_BISHOP:           return JMASK_ARCH_BISHOP;
	case JOB_MECHANIC:              return JMASK_MECHANIC;
	case JOB_GUILLOTINE_CROSS:      return JMASK_GUILLOTINE_CROSS;
	//3-2 Jobs
	case JOB_ROYAL_GUARD:           return JMASK_ROYAL_GUARD;
	case JOB_SORCERER:              return JMASK_SORCERER;
	case JOB_MINSTREL:
	case JOB_WANDERER:              return JMASK_MINSTRELWANDERER;
	case JOB_SURA:                  return JMASK_SURA;
	case JOB_GENETIC:               return JMASK_GENETIC;
	case JOB_SHADOW_CHASER:         return JMASK_SHADOW_CHASER;
	//Trans 3-1 Jobs
	case JOB_RUNE_KNIGHT_T:         return JMASK_RUNE_KNIGHT_T;
	case JOB_WARLOCK_T:             return JMASK_WARLOCK_T;
	case JOB_RANGER_T:              return JMASK_RANGER_T;
	case JOB_ARCH_BISHOP_T:         return JMASK_ARCH_BISHOP_T;
	case JOB_MECHANIC_T:            return JMASK_MECHANIC_T;
	case JOB_GUILLOTINE_CROSS_T:    return JMASK_GUILLOTINE_CROSS_T;
	//Trans 3-2 Jobs
	case JOB_ROYAL_GUARD_T:         return JMASK_ROYAL_GUARD_T;
	case JOB_SORCERER_T:            return JMASK_SORCERER_T;
	case JOB_MINSTREL_T:
	case JOB_WANDERER_T:            return JMASK_MINSTRELWANDERER_T;
	case JOB_SURA_T:                return JMASK_SURA_T;
	case JOB_GENETIC_T:             return JMASK_GENETIC_T;
	case JOB_SHADOW_CHASER_T:       return JMASK_SHADOW_CHASER_T;
	//Baby 3-1 Jobs
	case JOB_SUPER_BABY_E:          return JMASK_SUPER_BABY_E;
	case JOB_BABY_RUNE:             return JMASK_BABY_RUNE;
	case JOB_BABY_WARLOCK:          return JMASK_BABY_WARLOCK;
	case JOB_BABY_RANGER:           return JMASK_BABY_RANGER;
	case JOB_BABY_BISHOP:           return JMASK_BABY_BISHOP;
	case JOB_BABY_MECHANIC:         return JMASK_BABY_MECHANIC;
	case JOB_BABY_CROSS:            return JMASK_BABY_CROSS;
	//Baby 3-2 Jobs
	case JOB_BABY_GUARD:            return JMASK_BABY_GUARD;
	case JOB_BABY_SORCERER:         return JMASK_BABY_SORCERER;
	case JOB_BABY_MINSTREL:
	case JOB_BABY_WANDERER:         return JMASK_BABY_MINSTRELWANDERER;
	case JOB_BABY_SURA:             return JMASK_BABY_SURA;
	case JOB_BABY_GENETIC:          return JMASK_BABY_GENETIC;
	case JOB_BABY_CHASER:           return JMASK_BABY_CHASER;
	default:                        return JMASK_INVALID;
	}
}
