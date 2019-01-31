//
//  ExpDB.hpp
//  zone
//
//  Created by SagunKho on 22/01/2019.
//

#ifndef HORIZON_ZONE_GAME_CONFIGURATION_EXPDB
#define HORIZON_ZONE_GAME_CONFIGURATION_EXPDB

#include <string>
#include <vector>
#include <unordered_map>

namespace libconfig
{
	class Config;
}

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
	
class ExpDB
{
public:
	ExpDB() { }
	~ExpDB() { }

	bool load();

	int load_group(libconfig::Config &cfg, exp_group_type type);

protected:
	std::unordered_map<std::string, exp_group_data> _base_exp_group_db;
	std::unordered_map<std::string, exp_group_data> _job_exp_group_db;
};

}
}
}
#endif /* HORIZON_ZONE_GAME_CONFIGURATION_EXPDB */
