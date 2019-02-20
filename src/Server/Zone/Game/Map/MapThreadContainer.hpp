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

#ifndef HORIZON_ZONE_GAME_MAPTHREADCONTAINER_HPP
#define HORIZON_ZONE_GAME_MAPTHREADCONTAINER_HPP

#include "Core/Multithreading/ThreadSafeQueue.hpp"
#include "Server/Zone/Game/Map/Script/ScriptMgr.hpp"

#include <stdio.h>
#include <thread>
#include <unordered_map>
#include <atomic>
#include <sol.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Map;
namespace Entities
{
	class Player;
}
class MapThreadContainer : public std::enable_shared_from_this<MapThreadContainer>
{
public:
	MapThreadContainer();
	~MapThreadContainer();

	std::shared_ptr<Map> get_map(std::string name) const;

	void add_map(std::shared_ptr<Map> &&map);
	void remove_map(std::shared_ptr<Map> &&map);

	void add_player(std::string map_name, std::shared_ptr<Entities::Player> p);
	void remove_player(std::shared_ptr<Entities::Player> p);

	void initialize();
	void start();

	std::shared_ptr<ScriptManager> get_script_manager() { return _script_mgr; }

private:
	void start_internal();
	void update(uint32_t tick);
	
	std::thread _thread;
	std::unordered_map<std::string, std::shared_ptr<Map>> _managed_maps;
	std::unordered_map<uint32_t, std::shared_ptr<Entities::Player>> _managed_players;
	ThreadSafeQueue<std::pair<bool, std::shared_ptr<Entities::Player>>> _player_buffer;
	std::shared_ptr<ScriptManager> _script_mgr;
};
}
}
}
#endif /* HORIZON_ZONE_GAME_MAPTHREADCONTAINER_HPP */
