//
//  MapThreadContainer.hpp
//  zone
//
//  Created by SagunKho on 24/01/2019.
//

#ifndef MapThreadContainer_hpp
#define MapThreadContainer_hpp

#include "Core/Multithreading/ThreadSafeQueue.hpp"

#include <stdio.h>
#include <thread>
#include <unordered_map>
#include <atomic>

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
class MapThreadContainer
{
public:
	MapThreadContainer() { }
	~MapThreadContainer()
	{
		if (_thread.joinable()) _thread.join();
	}

	bool find_map(std::string name) const { return _managed_maps.find(name) != _managed_maps.end() ? true : false; }
	std::shared_ptr<Map> get_map(std::string name) const
	{
		if (!find_map(name)) return nullptr;
		return _managed_maps.find(name)->second;
	}

	void add_map(std::shared_ptr<Map> &&map);
	void remove_map(std::shared_ptr<Map> &&map);

	void add_player(std::string map_name, std::shared_ptr<Entities::Player> p);
	void remove_player(std::shared_ptr<Entities::Player> p);

	void initialize_maps();

	void start();

private:
	void start_internal(uint32_t core_update_interval);
	void update(uint32_t tick);
	
	std::thread _thread;
	std::unordered_map<std::string, std::shared_ptr<Map>> _managed_maps;
	std::unordered_map<int, std::shared_ptr<Entities::Player>> _managed_players;
	ThreadSafeQueue<std::pair<bool, std::shared_ptr<Entities::Player>>> _player_buffer;
};
}
}
}
#endif /* MapThreadContainer_hpp */
