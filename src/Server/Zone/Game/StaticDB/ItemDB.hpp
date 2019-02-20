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
