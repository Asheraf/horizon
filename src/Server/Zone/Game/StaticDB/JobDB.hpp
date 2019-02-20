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

#ifndef HORIZON_ZONE_GAME_JOBDB
#define HORIZON_ZONE_GAME_JOBDB

#include "Server/Zone/Game/Definitions/ItemDefinitions.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

#include <unordered_map>
#include <map>
#include <vector>
#include <array>
#include <string>
#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
struct job_db_data
{
	int _id{0};
	int _max_weight{20000};
	std::string _base_exp_group{""}, _job_exp_group{""};
	std::array<int, WT_MAX> _weapon_base_aspd{0};
	std::vector<int> _hp_table, _sp_table;
};
class JobDB
{
public:
	JobDB();
	~JobDB() { }

	job_classes get_job_class_by_name(std::string name) const;
	job_class_mask job_id_to_mask(job_classes job_id) const;
	bool load();
	int load_job(sol::table &job_tbl, std::string name = "");
	bool load_job_internal(sol::table &job_tbl, job_db_data &data, std::string job_name = "");
	bool load_hp_sp_table(sol::table &job_tbl, job_db_data &data, std::string &job_name, std::string table_name);

private:
	std::unordered_map<job_classes, job_db_data> _job_db;
	std::map<std::string, int> _name2id_list;
};
}
}
}
#endif /* HORIZON_ZONE_GAME_JOBDB */
