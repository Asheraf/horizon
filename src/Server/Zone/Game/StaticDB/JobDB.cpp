
#include "JobDB.hpp"
#include "Server/Zone/Zone.hpp"

#include <libconfig.h++>

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

job_classes Horizon::Zone::Game::JobDB::get_job_class_by_name(std::string name)
{
	auto id = _name2id_list.find(name);

	if (id == _name2id_list.end())
		return JOB_INVALID;

	return job_classes(id->second);
}

bool Horizon::Zone::Game::JobDB::load()
{
	libconfig::Config cfg;
	int total_entries = 0;
	std::string tmp_string;
	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "job_db.conf";

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(file_path.c_str());
	} catch(const libconfig::FileIOException &fioex) {
		ZoneLog->error("I/O error while reading file '{}'.", file_path);
		return false;
	} catch(const libconfig::ParseException &pex) {
		ZoneLog->error("Parse error at {}:{} - {}", pex.getFile(), pex.getLine(), pex.getError());
		return false;
	}

	total_entries = load_job(cfg.getRoot());

	ZoneLog->info("Loaded {} entries from '{}'", total_entries, file_path);

	return true;
}

int Horizon::Zone::Game::JobDB::load_job(libconfig::Setting &cfg, std::string name)
{
	int count = 0;


	if (name.empty()) {
		for (auto job_c = cfg.begin(); job_c != cfg.end(); job_c++) {
			job_db_data data;
			std::string name = job_c->getName();
			job_classes jc = get_job_class_by_name(name);
			if (load_job_internal(*job_c, data, name) == true) {
				_job_db.emplace(jc, data);
				count++;
			}
		}
	} else {
		if (cfg.exists(name)) {
			job_db_data data;
			job_classes jc = get_job_class_by_name(name);
			if (load_job_internal(cfg, data, name) == true)
				_job_db.emplace(jc, data);
		} else {
			ZoneLog->warn("JobDB::load_job: Job named '{}' was not found.", name);
		}
	}

	return count;
}

bool Horizon::Zone::Game::JobDB::load_job_internal(libconfig::Setting &job_c, job_db_data &data, std::string job_name)
{
	std::string inherit;

	if (job_c.getType() != libconfig::Setting::TypeGroup) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid type for setting named '{}', skipping...", job_name);
		return false;
	}

	if (!job_c.lookupValue("BaseExpGroup", data._base_exp_group)) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existant BaseExpGroup for job '{}', skipping...", job_name);
		return false;
	}

	if (!job_c.lookupValue("JobExpGroup", data._job_exp_group)) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existant JobExpGroup for job '{}', skipping...", job_name);
		return false;
	}

	// Inherit if specified.
	if (job_c.exists("Inherit") == false) {
		// Max Weight
		if (job_c.lookupValue("Weight", data._max_weight) ==  false)
			data._max_weight = 20000;

		try {
			libconfig::Setting &aspd_c = job_c.lookup("BaseASPD");

			if (aspd_c.getType() != libconfig::Setting::TypeGroup) {
				ZoneLog->warn("JobDB::load_job_internal: Invalid type BaseASPD setting for job '{}'.", job_name);
			} else {
				for (auto aspd_it = aspd_c.begin(); aspd_it != aspd_c.end(); aspd_it++) {
					std::string w_name = aspd_it->getName();
					if (!aspd_it->isNumber()) {
						ZoneLog->warn("JobDB::load_job_internal: Invalid entry in BaseASPD setting weapon {} for job '{}'.", w_name, job_name);
						continue;
					}

					int val = *aspd_it;
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
				}
			}
		} catch (libconfig::SettingNotFoundException &err) {
			ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existent 'BaseASPD' setting for job '{}', skipping...", job_name);
			return false;
		}
	} else {
		if (job_c.lookupValue("Inherit", inherit) == false) {
			ZoneLog->warn("JobDB::load_job_internal: Invalid 'Inherit' value provided for entry '{}', Skipping...", job_name);
			return false;
		}

		job_classes jc = get_job_class_by_name(inherit);
		if (jc == JOB_INVALID) {
			ZoneLog->warn("JobDB::load_job_internal: Unable to inherit from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", inherit, job_name);
			return false;
		}

		auto jobi = _job_db.find(jc);

		if (jc == JOB_INVALID) {
			ZoneLog->warn("JobDB::load_job_internal: Unable to inherit from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", inherit, job_name);
			return false;
		}

		job_db_data inherited_data = jobi->second;
		data._weapon_base_aspd = inherited_data._weapon_base_aspd;
		data._max_weight = inherited_data._max_weight;
	}

	if (load_hp_sp_table(job_c, data, job_name, "HPTable") == false)
		return false;
	if (load_hp_sp_table(job_c, data, job_name, "SPTable") == false)
		return false;

	return true;
}

bool Horizon::Zone::Game::JobDB::load_hp_sp_table(libconfig::Setting &cfg, job_db_data &data, std::string &job_name, std::string table_name)
{
	std::string inherit;

	if (cfg.lookupValue("Inherit", inherit) == true
		|| cfg.lookupValue("InheritHP", inherit) == true
		|| cfg.lookupValue("InheritSP", inherit) == true) {
		job_classes jc = get_job_class_by_name(inherit);
		if (jc == JOB_INVALID) {
			ZoneLog->warn("JobDB::load_job_internal: Unable to inherit from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", inherit, job_name);
			return false;
		}
		auto jobi = _job_db.find(jc);
		if (jobi == _job_db.end()) {
			ZoneLog->warn("JobDB::load_hp_sp_table: Unable to inherit {} from non-existent job '{}' for '{}', make sure the job is read before being inherited. Skipping...", table_name, inherit, job_name);
			return false;
		}
		job_db_data inherited_data = jobi->second;

		data._hp_table = inherited_data._hp_table;
		data._sp_table = inherited_data._sp_table;
		return true;
	}

	try {
		libconfig::Setting &table_c = cfg.lookup(table_name);

		if (!cfg.exists(table_name) || !table_c.isArray()) {
			ZoneLog->warn("JobDB::load_hp_sp_table: Invalid type or non-existant {} setting for job '{}'.", table_name, job_name);
		} else {
			for (int i = 0; i < table_c.getLength(); i++) {
				if (!table_c[i].isNumber()) {
					ZoneLog->warn("JobDB::load_hp_sp_table: Invalid index {} for entry {} in job '{}', skipping...", i + 1, job_name, job_name);
					continue;
				}

				if (!table_name.compare("HPTable"))
					data._hp_table.push_back(table_c[i]);
				else if (!table_name.compare("SPTable"))
					data._sp_table.push_back(table_c[i]);
			}
		}
	} catch (libconfig::SettingNotFoundException &err) {
		ZoneLog->warn("JobDB::load_hp_sp_table: {} for job '{}' does not exist, skipping...", table_name, job_name);
		return false;
	}

	return true;
}
