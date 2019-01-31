//
//  MapThreadContainer.cpp
//  zone
//
//  Created by SagunKho on 24/01/2019.
//

#include "MapThreadContainer.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Core/Logging/Logger.hpp"

void Horizon::Zone::Game::MapThreadContainer::add_map(std::shared_ptr<Map> &&m)
{
	_managed_maps.emplace(m->get_name(), m);
}

void Horizon::Zone::Game::MapThreadContainer::remove_map(std::shared_ptr<Map> &&m)
{
	_managed_maps.erase(m->get_name());
}

void Horizon::Zone::Game::MapThreadContainer::add_player(std::string /*map_name*/, std::shared_ptr<Entities::Player> p)
{
	_player_buffer.push(std::make_pair(true, p));
}

void Horizon::Zone::Game::MapThreadContainer::remove_player(std::shared_ptr<Entities::Player> p)
{
	_player_buffer.push(std::make_pair(false, p));
}

void Horizon::Zone::Game::MapThreadContainer::start()
{
	int core_update_interval = ZoneServer->general_conf().get_core_update_interval();
	_thread = std::thread(&MapThreadContainer::start_internal, this, core_update_interval);

	ZoneLog->info("A map container thread with {} maps has begun working.", _managed_maps.size());
}

void Horizon::Zone::Game::MapThreadContainer::start_internal(uint32_t core_update_interval)
{
	do {
		update(core_update_interval);
		std::this_thread::sleep_for(std::chrono::microseconds(core_update_interval));
	} while (!ZoneServer->general_conf().is_test_run() && !ZoneServer->is_shutting_down());
}

void Horizon::Zone::Game::MapThreadContainer::initialize_maps()
{
	for (auto mi = _managed_maps.begin(); mi != _managed_maps.end(); mi++) {
		mi->second->ensureAllGrids();
	}
}

void Horizon::Zone::Game::MapThreadContainer::update(uint32_t diff)
{
	std::shared_ptr<std::pair<bool, std::shared_ptr<Entities::Player>>> pbuf = nullptr;

	// Add any new players / remove anyone else.
	while ((pbuf = _player_buffer.try_pop())) {
		std::shared_ptr<ZoneSession> session = pbuf->second->get_session();

		if (session == nullptr)
			continue;

		int account_id = pbuf->second->get_session()->get_game_account()->get_id();

		if (pbuf->first)
			_managed_players.emplace(account_id, pbuf->second);
		else
			_managed_players.erase(account_id);
	}

	// Update sessions
	for (auto pi = _managed_players.begin(); pi != _managed_players.end(); pi++) {
		std::shared_ptr<ZoneSession> session = pi->second->get_session();

		if (session == nullptr) {
			_managed_players.erase(pi);
			continue;
		}

		// process packets
		pi->second->get_session()->update(diff);
		// update entity.
		pi->second->update(diff);
	}
}
