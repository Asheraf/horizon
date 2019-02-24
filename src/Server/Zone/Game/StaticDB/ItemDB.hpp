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

#ifndef HORIZON_ZONE_GAME_ITEMDB
#define HORIZON_ZONE_GAME_ITEMDB

#include "Server/Zone/Game/Definitions/ItemDefinitions.hpp"
#include "Core/Multithreading/LockedLookupTable.hpp"
#include <cstdio>
#include <map>
#include <cstring>
#include <iostream>
#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
class ItemDB
{
public:
	ItemDB() { }
	~ItemDB() { }

	bool load();
	int load_items(sol::table &item_tbl);
	bool load_table_item(sol::object const &key, sol::object const &value);
private:
	LockedLookupTable<uint32_t, item_data> _item_db;
};
}
}
}
#endif /* HORIZON_ZONE_GAME_ITEMDB */
