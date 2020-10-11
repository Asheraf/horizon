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

#include "SkillDB.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone::Game;

SkillDatabase::SkillDatabase()
{
	//
}

SkillDatabase::~SkillDatabase()
{
	//
}

bool SkillDatabase::load()
{
	sol::state lua;

	int total_entries = 0;
	std::string tmp_string;
	std::string file_path = ZoneServer->get_zone_config().get_database_path() + "skill_db.lua";

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		sol::table skill_tbl = lua.get<sol::table>("skill_db");
		skill_tbl.for_each([this, &total_entries] (sol::object const &key, sol::object const &value) {
			total_entries = load_internal(key, value);
		});
		CoreLog(info) <<"Loaded {} entries from '{}'", total_entries, file_path);
	} catch(const std::exception &e) {
		CoreLog(error) <<"JobDB::load: {}.", e.what());
		return false;
	}

	return true;
}

bool SkillDatabase::load_internal(const sol::object &key, const sol::object &value)
{
	
	return true;
}
