/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_GAME_MAP_MAPMGR_HPP
#define HORIZON_GAME_MAP_MAPMGR_HPP

namespace Horizon
{
namespace Game
{
namespace Map
{
class MapMgr
{
public:
	MapMgr() { };
	~MapMgr() { };

	static MapMgr *getInstance()
	{
		static MapMgr map_mgr;
		return &map_mgr;
	}

private:
	std::map<uint32_t, std::shared_ptr<Map>> _maps;
}
}
}
}

#define ZoneMapMgr Horizon::Game::Map::MapMgr::getInstance()

#endif /* HORIZON_GAME_MAP_MAPMGR_HPP */
