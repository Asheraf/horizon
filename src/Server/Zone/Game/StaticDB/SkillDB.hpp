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
#ifndef HORIZON_ZONE_GAME_SKILLDB_HPP
#define HORIZON_ZONE_GAME_SKILLDB_HPP

#include "Core/Multithreading/LockedLookupTable.hpp"

#include <cstdlib>


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
struct skill_config_data
{

};
class SkillDatabase
{
public:
	SkillDatabase();
	~SkillDatabase();
	
	bool load();

protected:
	bool load_internal(sol::object const &key, sol::object const &value);

private:
	LockedLookupTable<uint32_t, std::shared_ptr<skill_config_data>> _skill_db;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_SKILLDB_HPP */
