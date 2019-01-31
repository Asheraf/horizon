//
//  ExpDB.cpp
//  zone
//
//  Created by SagunKho on 22/01/2019.
//

#include "ExpDB.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Zone.hpp"

#include <libconfig.h++>

bool Horizon::Zone::Game::ExpDB::load()
{
	libconfig::Config cfg;
	int total_entries[2] = { 0, 0 };
	std::string tmp_string;
	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "exp_group_db.conf";

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

	total_entries[0] = load_group(cfg, EXP_GROUP_TYPE_BASE);
	total_entries[1] = load_group(cfg, EXP_GROUP_TYPE_JOB);

	ZoneLog->info("Read {} Base and {} Job EXP groups from '{}'", total_entries[0], total_entries[1], file_path);

	return true;
}

int Horizon::Zone::Game::ExpDB::load_group(libconfig::Config &cfg, exp_group_type type)
{
	int total_entries = 0;
	const libconfig::Setting &group_db_c = type == EXP_GROUP_TYPE_BASE ? cfg.getRoot()["base_exp_group_db"] : cfg.getRoot()["job_exp_group_db"];
	std::unordered_map<std::string, exp_group_data> *group_db = type == EXP_GROUP_TYPE_BASE ? &_base_exp_group_db : &_job_exp_group_db;

	for (auto it = group_db_c.begin(); it != group_db_c.end(); it++) {
		std::string class_name = it->getName();
		exp_group_data expd;

		std::unordered_map<std::string, exp_group_data>::iterator dup_it;
		if ((dup_it = group_db->find(class_name)) != group_db->end()) {
			ZoneLog->warn("ExpDB::load: Found duplicate {} Exp group for '{}', overwriting...", type == EXP_GROUP_TYPE_BASE ? "base" : "job", class_name);
			group_db->erase(dup_it);
		}

		if (!it->lookupValue("MaxLevel", expd.max_level)) {
			ZoneLog->error("ExpDB::load: Max Level not given for group '{}', skipping...", class_name);
			continue;
		}

		if (!it->exists("Exp")) {
			ZoneLog->error("ExpDB::load: Missing Exp data for group '()', skipping...", class_name);
			continue;
		}

		libconfig::Setting &exp_c = it->lookup("Exp");

		if (exp_c.getType() != libconfig::Setting::TypeArray) {
			ZoneLog->error("ExpDB::load: Exp data has invalid data type in group '{}', skipping...", class_name);
			continue;
		}

		int exp_entry_count = 0;
		for (int i = 0; i < exp_c.getLength(); i++) {
			if (!exp_c[i].isNumber()) {
				ZoneLog->error("ExpDB::load: Invalid Exp data found in array of group '{}', aborting with '{}' entries...", class_name, exp_entry_count);
				break;
			}

			expd.exp.push_back((int) exp_c[i]);

			exp_entry_count++;
		}

		group_db->emplace(class_name, expd);
		total_entries++;
	}

	return total_entries;
}
