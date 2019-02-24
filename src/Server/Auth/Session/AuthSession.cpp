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

#include "AuthSession.hpp"

#include "Server/Auth/Packets/PacketHandler.hpp"
#include "Server/Auth/Packets/PacketHandlerFactory.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

AuthSession::AuthSession(std::shared_ptr<AuthSocket> socket)
: Horizon::Networking::Session<AuthSocket>(socket)
{
	_client_type = AuthServer->general_conf().get_client_type();
	_packet_version = AuthServer->general_conf().get_packet_version();
}

AuthSession::~AuthSession()
{
	//
}

/* Packet Handler */
std::shared_ptr<PacketHandler> AuthSession::get_packet_handler() { return _packet_handler; }
void AuthSession::set_packet_handler(std::shared_ptr<PacketHandler> handler) { _packet_handler.swap(handler); }
/* Game Account */
std::shared_ptr<GameAccount> AuthSession::get_game_account() { return _game_account; }
void AuthSession::set_game_account(std::shared_ptr<GameAccount> account) { _game_account.swap(account); }
/* Session Data */
std::shared_ptr<SessionData> AuthSession::get_session_data() { return _session_data; }
void AuthSession::set_session_data(std::shared_ptr<SessionData> session_data) { _session_data.swap(session_data); }

void AuthSession::initialize()
{
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), _client_type, _packet_version));
}

void AuthSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
		if (_packet_handler == nullptr) {
			AuthLog->error("Packet handler was null!");
			return;
		}

		_packet_handler->handle_received_packet(*buf);
	}
}
