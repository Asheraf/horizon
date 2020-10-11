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

#include "MapThreadContainer.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Core/Logging/Logger.hpp"

using namespace Horizon::Zone::Game;

MapThreadContainer::MapThreadContainer()
{

}

MapThreadContainer::~MapThreadContainer()
{
}

//! @brief Retrieves a shared pointer to a map managed by the container.
//! Managed maps are saved in thread-safe tables.
//! @param[in] name const reference to the name of the map to lookup.
//! @return Managed map if found, else a null shared_ptr instance.
std::shared_ptr<Map> MapThreadContainer::get_map(std::string const &name) const
{
	return _managed_maps.at(name);
}

//! @brief Adds a map to the container in real time. Managed maps are
//! saved in thread-safe tables.
//! @param[in] m r-value reference to a shared_ptr of a map object.
void MapThreadContainer::add_map(std::shared_ptr<Map> &&m)
{
	_managed_maps.insert(m->get_name(), m);
}

//! @brief Removes a map from the container in real time. Managed maps are
//! saved in thread-safe tables.
//! @param[in] m r-value reference to a shared_ptr of a map object.
void MapThreadContainer::remove_map(std::string const &name)
{
	_managed_maps.erase(name);
}

//! @brief Adds a player to the player buffer, marking him for addition to the
//! list of managed players by this container on the next update.
//! @param[in] p shared_ptr to a player object which should be managed by this map.
//! @note A player added for management by this container must be the only owner of the player object.
void MapThreadContainer::add_player(std::shared_ptr<Entities::Player> p)
{
	_player_buffer.push(std::make_pair(true, p));
}

//! @brief Adds a player to the player buffer, marking him for removal from the
//! list of managed players by this container on the next update.
void MapThreadContainer::remove_player(std::shared_ptr<Entities::Player> p)
{
	_player_buffer.push(std::make_pair(false, p));
}

//! @brief Responsible for initialization of the container and is called externally.
//! This is mainly for members that can't be initialized from the constructor method.
void MapThreadContainer::initialize()
{
	_script_mgr = std::make_shared<ScriptManager>(shared_from_this());
}

//! @brief Process container finalization by cleanly disconnecting players after saving their data.
//! Clears all managed map instances from itself.
//! This method must not be called from within the thread itself! @see MapManager::finalize()
void MapThreadContainer::finalize()
{
	for (auto pi = _managed_players.begin(); pi != _managed_players.end();) {
		std::shared_ptr<Entities::Player> player = pi->second;
		pi = _managed_players.erase(pi);

		if (!player || !player->get_socket() || !player->get_socket()->is_open())
			continue;

		// Sync with models / Save to DB
		player->sync_with_models();
		// Disconnect player.
		player->get_packet_handler()->Send_ZC_ACK_REQ_DISCONNECT(true);
		pi = _managed_players.erase(pi);
	}

	// Clear anyone in the player buffer (You never know...)
	std::shared_ptr<std::pair<bool, std::shared_ptr<Entities::Player>>> pbuf = nullptr;

	while ((pbuf = _player_buffer.try_pop())) {
		std::shared_ptr<Entities::Player> player = pbuf->second;

		if (!player || !player->get_socket() || !player->get_socket()->is_open())
			continue;

		player->sync_with_models();
		player->get_packet_handler()->Send_ZC_ACK_REQ_DISCONNECT(true);
	}

	if (_thread.joinable())
		_thread.join();

	_managed_maps.clear();

	CoreLog(info) <<"Map container {:p} has shut down.", (void *) this);
}

//! @brief Begins running the container's thread and notifies of doing so.
//! This function is a wrapper for the internal start function which the internal thread instance is
//! responsible for calling. The internal start function deals with actual data loading/initializing,
//! world update loop and finalization of the same on shutdown.
void MapThreadContainer::start()
{
	_thread = std::thread(&MapThreadContainer::start_internal, this);

	CoreLog(info) <<"Map container {:p} with {} maps has begun working.", (void *) this, _managed_maps.size());
}

//! @brief Called by the internal thread of MapThreadContainer and deals with initialization of thread-accessible data.
//! Is also responsible emulating the world update loop and performing everything in maps it manages.
//! @thread MapThreadContainer
void MapThreadContainer::start_internal()
{
	int core_update_interval = ZoneServer->general_conf().get_core_update_interval();

	get_script_manager()->initialize();

	while (!ZoneServer->general_conf().is_test_run() && ZoneServer->get_shutdown_stage() == SHUTDOWN_NOT_STARTED) {
		update(get_sys_time());
		std::this_thread::sleep_for(std::chrono::microseconds(core_update_interval));
	};

	get_script_manager()->finalize();
}

//! @brief World update loop for a MapThreadContainer.
//! Performs world updates for maps managed in the specific thread container.
//! @param[in] diff current system time.
void MapThreadContainer::update(uint64_t diff)
{
	std::shared_ptr<std::pair<bool, std::shared_ptr<Entities::Player>>> pbuf = nullptr;

	// Add any new players / remove anyone else.
	while ((pbuf = _player_buffer.try_pop())) {
		std::shared_ptr<Entities::Player> player = pbuf->second;

		if (player->get_session() == nullptr)
			continue;

		if (pbuf->first) {
			if (!player->is_initialized())
				player->initialize();
			_managed_players.emplace(player->get_guid(), player);
		} else {
			_managed_players.erase(player->get_guid());
		}
	}

	// Update sessions
	for (auto pi = _managed_players.begin(); pi != _managed_players.end();) {
		std::shared_ptr<Entities::Player> player = pi->second;

		if (!player || !player->get_socket() || !player->get_socket()->is_open()) {
			pi = _managed_players.erase(pi);
			continue;
		}
		// process packets
		player->get_session()->update(diff);
		// update entity.
		player->update(diff);
		pi++;
	}

	// Update NPCs
	for (auto npci : _script_mgr->_npc_db) {
		std::shared_ptr<Entities::NPC> npc = npci.second._npc;
		npc->update(diff);
	}
}
