//
//  GameConfig.hpp
//  zone
//
//  Created by SagunKho on 22/01/2019.
//

#ifndef HORIZON_ZONE_GAME_STATICDB
#define HORIZON_ZONE_GAME_STATICDB

#include "ExpDB.hpp"
#include "JobDB.hpp"

#include <stdio.h>

namespace Horizon
{
namespace Zone
{
namespace Game
{
class StaticDBStore
{
public:
	StaticDBStore() { }

	static StaticDBStore *get_instance()
	{
		static StaticDBStore instance;
		return &instance;
	}

	ExpDB get_exp_db() { return _exp_db; }

	void load_all();

private:
	ExpDB _exp_db;
	JobDB _job_db;

};
}
}
}

#define StaticDB Horizon::Zone::Game::StaticDBStore::get_instance()

#endif /* HORIZON_ZONE_GAME_STATICDB */
