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
#ifndef HORIZON_ZONE_GAME_JOBDB
#define HORIZON_ZONE_GAME_JOBDB

#include "Common/Definitions/ItemDefinitions.hpp"
#include "Common/Definitions/EntityDefinitions.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include <memory>
#include <map>
#include <vector>
#include <array>
#include <string>

#if (((defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))) || defined(_MSC_VER)) \
	&& !defined(SOL_EXCEPTIONS_SAFE_PROPAGATION))
#define SOL_EXCEPTIONS_SAFE_PROPAGATION
#endif

#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
struct job_db_data
{
	int id{0};
	int max_weight{20000};
	std::string base_exp_group{""}, job_exp_group{""};
	std::array<int, IT_WT_MAX> weapon_base_aspd;
	std::vector<int> hp_table, sp_table;
};
class JobDatabase
{
public:
	JobDatabase();
	~JobDatabase() { }

	static JobDatabase *get_instance()
	{
		static JobDatabase instance;
		return &instance;
	}

	job_class_type get_job_class_by_name(std::string name) const;
	job_class_mask job_id_to_mask(job_class_type job_id) const;

	bool load();
	int load_job(sol::table &job_tbl, std::string name = "");
	bool load_job_internal(sol::table &job_tbl, job_db_data &data, std::string job_name = "");
	bool load_hp_sp_table(sol::table &job_tbl, job_db_data &data, std::string &job_name, std::string table_name);

	std::shared_ptr<const job_db_data> get(uint16_t job_id) { return _job_db.at((job_class_type) job_id); }
private:
	LockedLookupTable<uint32_t, std::shared_ptr<const job_db_data>> _job_db;
	std::map<std::string, int> _name2id_list;
};
}
}
}

#define JobDB Horizon::Zone::Game::JobDatabase::get_instance()

#endif /* HORIZON_ZONE_GAME_JOBDB */
