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

#ifndef HORIZON_ZONE_GAME_CONFIGURATION_EXPDB
#define HORIZON_ZONE_GAME_CONFIGURATION_EXPDB

#include "Server/Common/Definitions/Horizon.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"

#include <string>
#include <vector>
#include <sol.hpp>
#include <cassert>

namespace Horizon
{
namespace Zone
{
namespace Game
{

struct exp_group_data
{
	uint32_t max_level;
	std::vector<uint64_t> exp;
};

enum exp_group_type
{
	EXP_GROUP_TYPE_BASE,
	EXP_GROUP_TYPE_JOB
};

class ExpDatabase
{
public:
	ExpDatabase() { }
	~ExpDatabase() { }

	static ExpDatabase *get_instance()
	{
		static ExpDatabase instance;
		return &instance;
	}

	bool load();

	std::shared_ptr<const exp_group_data> get_exp_group(std::string const &name, exp_group_type type)
	{
		return type == EXP_GROUP_TYPE_BASE ? _base_exp_group_db.at(name) : _job_exp_group_db.at(name);
	}

	uint32_t get_status_point(uint32_t level)
	{
		if (level <= 0 || level > _stat_point_db.size() || level > MAX_LEVEL)
			return 0;
		return _stat_point_db.at(level);
	}

	bool load_status_point_table();

protected:
	int load_group(sol::table &tbl, exp_group_type type);
	LockedLookupTable<std::string, std::shared_ptr<const exp_group_data>> _base_exp_group_db;
	LockedLookupTable<std::string, std::shared_ptr<const exp_group_data>> _job_exp_group_db;
	LockedLookupTable<uint32_t, uint32_t> _stat_point_db;
};

}
}
}

#define ExpDB Horizon::Zone::Game::ExpDatabase::get_instance()

#endif /* HORIZON_ZONE_GAME_CONFIGURATION_EXPDB */
