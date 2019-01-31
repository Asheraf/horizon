
#include "JobDB.hpp"
#include "Server/Zone/Zone.hpp"
#include <libconfig.h++>

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
			load_job_internal(*job_c, data, name);
			_job_db.emplace(name, data);
			count++;
		}
	} else {
		if (cfg.exists(name)) {
			job_db_data data;
			load_job_internal(cfg, data, name);
			_job_db.emplace(name, data);
		} else {
			ZoneLog->warn("JobDB::load_job: Job named '{}' was not found.", name);
		}
	}

	return count;
}

void Horizon::Zone::Game::JobDB::load_job_internal(libconfig::Setting &job_c, job_db_data &data, std::string job_name)
{
	std::string inherit;

	if (job_c.getType() != libconfig::Setting::TypeGroup) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid type for setting named '{}', skipping.", job_name);
	}

	if (!job_c.lookupValue("BaseExpGroup", data._base_exp_group)) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existant BaseExpGroup for job '{}'.", job_name);
	}

	if (!job_c.lookupValue("JobExpGroup", data._job_exp_group)) {
		ZoneLog->warn("JobDB::load_job_internal: Invalid or non-existant JobExpGroup for job '{}'.", job_name);
	}

	// Inherit if specified.
	if (job_c.lookupValue("Inherit", inherit)) {
		job_db_data inherited_data = _job_db.find(inherit)->second;
		data._weapon_base_aspd = inherited_data._weapon_base_aspd;
		data._max_weight = inherited_data._max_weight;
	} else {
		// Max Weight
		job_c.lookupValue("MaxWeight", data._max_weight);

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
	}

	load_hp_sp_table(job_c, data, job_name, "HPTable");
	load_hp_sp_table(job_c, data, job_name, "SPTable");
}

void Horizon::Zone::Game::JobDB::load_hp_sp_table(libconfig::Setting &cfg, job_db_data &data, std::string &job_name, std::string table_name)
{
	if (!cfg.exists(table_name)) {
		std::string inherit;
		job_db_data inherited_data;
		if (cfg.lookupValue("Inherit", inherit)) {
			inherited_data = _job_db.find(inherit)->second;
		} else if (cfg.lookupValue("InheritHP", inherit)) {
			inherited_data = _job_db.find(inherit)->second;
		} else if (cfg.lookupValue("InheritSP", inherit)) {
			inherited_data = _job_db.find(inherit)->second;
		}
		data._hp_table = inherited_data._hp_table;
		data._sp_table = inherited_data._sp_table;
		return;
	}

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
}
