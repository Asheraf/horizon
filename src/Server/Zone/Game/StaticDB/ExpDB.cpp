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

#include "ExpDB.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Zone.hpp"


bool Horizon::Zone::Game::ExpDB::load()
{
	sol::state lua;
	int total_entries[2] = { 0, 0 };
	std::string tmp_string;
	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "exp_group_db.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table base_exp_tbl = lua["base_exp_group_db"];
		sol::table job_exp_tbl = lua["job_exp_group_db"];
		total_entries[0] = load_group(base_exp_tbl, EXP_GROUP_TYPE_BASE);
		total_entries[1] = load_group(job_exp_tbl, EXP_GROUP_TYPE_JOB);
	} catch(const std::exception &e) {
		ZoneLog->error("ExpDB::error: {}.", e.what());
		return false;
	}

	ZoneLog->info("Read {} Base and {} Job EXP groups from '{}'", total_entries[0], total_entries[1], file_path);

	return true;
}

int Horizon::Zone::Game::ExpDB::load_group(sol::table &group_tbl, exp_group_type type)
{
	int total_entries = 0;
	std::unordered_map<std::string, exp_group_data> *group_db = type == EXP_GROUP_TYPE_BASE ? &_base_exp_group_db : &_job_exp_group_db;

	group_tbl.for_each([group_db, &total_entries, type](sol::object const &key, sol::object const &value) {
		std::string group_name = key.as<std::string>();
		sol::table tbl = value.as<sol::table>();
		exp_group_data expd;

		std::unordered_map<std::string, exp_group_data>::iterator dup_it;
		if ((dup_it = group_db->find(group_name)) != group_db->end()) {
			ZoneLog->warn("ExpDB::load: Found duplicate {} Exp group for '{}', overwriting...", type == EXP_GROUP_TYPE_BASE ? "base" : "job", group_name);
			group_db->erase(dup_it);
		}

		expd.max_level = tbl.get_or("MaxLevel", 0);
		if (expd.max_level == 0) {
			ZoneLog->error("ExpDB::load: Max Level not given for group '{}', skipping...", group_name);
			return;
		}

		sol::optional<sol::table> maybe_exp_tbl = tbl.get<sol::optional<sol::table>>("Exp");
		if (!maybe_exp_tbl) {
			ZoneLog->error("ExpDB::load: Missing Exp data for group '()', skipping...", group_name);
			return;
		}

		sol::table &exp_tbl = maybe_exp_tbl.value();
		exp_tbl.for_each([&expd, &group_name](sol::object const &key, sol::object const &value) {
			if (key.get_type() != sol::type::number) {
				ZoneLog->error("ExpDB::load: Invalid Exp data found in array of group '{}', aborting with '{}' entries...", group_name, key.as<int>());
				return;
			}
			expd.exp.push_back(value.as<int>());
		});

		group_db->emplace(group_name, expd);
		total_entries++;
	});

	return total_entries;
}
