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
#include "ZoneSession.hpp"

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Zone/Packets/PacketHandlerFactory.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Models;
using namespace Horizon::Zone;
using namespace Horizon::Zone::Game::Entities;
using namespace Horizon::Models::Character;

ZoneSession::ZoneSession(std::shared_ptr<ZoneSocket> socket)
: Session(socket)
{
	_client_type = ZoneServer->general_conf().get_client_type();
	_packet_version = ZoneServer->general_conf().get_packet_version();
}

ZoneSession::~ZoneSession()
{
	//
}

/* Packet Handler */
std::shared_ptr<PacketHandler> ZoneSession::get_packet_handler() { return _packet_handler; }
void ZoneSession::set_packet_handler(std::shared_ptr<PacketHandler> handler) { _packet_handler.swap(handler); }
/* Character */
std::shared_ptr<Horizon::Models::Character::Character> ZoneSession::get_char_model() { return _character; }
void ZoneSession::set_char_model(std::shared_ptr<Horizon::Models::Character::Character> character) { _character.swap(character); }
/* Game Account */
std::shared_ptr<GameAccount> ZoneSession::get_game_account() { return _game_account; }
void ZoneSession::set_game_account(std::shared_ptr<GameAccount> game_acc) { _game_account.swap(game_acc); }
/* Session Data */
std::shared_ptr<SessionData> ZoneSession::get_session_data() { return _session_data; }
void ZoneSession::set_session_data(std::shared_ptr<SessionData> session_data) { _session_data.swap(session_data); }
/* Player */
std::shared_ptr<Player> ZoneSession::get_player() { return _player.lock(); }
void ZoneSession::set_player(std::weak_ptr<Player> p) { _player = p; }

/**
 * @brief Initializes the zone session's members.
 */
void ZoneSession::initialize()
{
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), _client_type, _packet_version));
}

/**
 * @brief Update loop for each Zone Session.
 * @thread called from MapThreadContainer.
 */
void ZoneSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	if (get_socket() != nullptr) {
		while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
			_packet_handler->handle_received_packet(*buf);
		}
	}
}

/**
 * @brief Performs generic logout of player in cases where the
 * connection was closed abruptly or by instruction.
 * Also marks the player for removal from the MapThreadContainer.
 * @thread Called from the NetworkThread.
 */
void ZoneSession::perform_cleanup()
{
	if (get_player() != nullptr) {
		std::shared_ptr<Player> player = get_player();
		player->notify_nearby_players_of_self(EVP_NOTIFY_LOGGED_OUT);
		player->set_logged_in(false);
		player->sync_with_models();
		player->get_map_container()->remove_player(get_player());
	}
}
