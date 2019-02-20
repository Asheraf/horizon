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

#ifndef HORIZON_ZONE_GAME_STATICDB
#define HORIZON_ZONE_GAME_STATICDB

#include "ExpDB.hpp"
#include "JobDB.hpp"
#include "ItemDB.hpp"

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

	ExpDB const &get_exp_db() const { return _exp_db; }
	JobDB const &get_job_db() const { return _job_db; }
	ItemDB const &get_item_db() const { return _item_db; }
	
	void load_all();

private:
	ExpDB _exp_db;
	JobDB _job_db;
	ItemDB _item_db;
};
}
}
}

#define StaticDB Horizon::Zone::Game::StaticDBStore::get_instance()

#endif /* HORIZON_ZONE_GAME_STATICDB */
