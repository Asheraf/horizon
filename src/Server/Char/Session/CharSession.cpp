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

#include "CharSession.hpp"

#include "Server/Char/Packets/PacketHandler.hpp"
#include "Server/Char/Packets/PacketHandlerFactory.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Char.hpp"

using namespace Horizon::Char;
using namespace Horizon::Models::Character;
CharSession::CharSession(std::shared_ptr<CharSocket> socket)
: Horizon::Networking::Session<CharSocket>(socket)
{
	_client_type = CharServer->general_conf().get_client_type();
	_packet_version = CharServer->general_conf().get_packet_version();
}

CharSession::~CharSession()
{
	//
}

/* Packet Handler */
std::shared_ptr<PacketHandler> CharSession::get_packet_handler() { return _packet_handler; }
void CharSession::set_packet_handler(std::shared_ptr<PacketHandler> handler) { _packet_handler.swap(handler); }
/* Character */
std::shared_ptr<Character> CharSession::get_character() { return _character; }
void CharSession::set_character(std::shared_ptr<Character> character) { _character.swap(character); }
/* Game Account */
std::shared_ptr<GameAccount> CharSession::get_game_account() { return _game_account; }
void CharSession::set_game_account(std::shared_ptr<GameAccount> account) { _game_account.swap(account); }
/* Session Data */
std::shared_ptr<SessionData> CharSession::get_session_data() { return _session_data; }
void CharSession::set_session_data(std::shared_ptr<SessionData> session_data) { _session_data.swap(session_data); }

void CharSession::initialize()
{
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), _client_type, _packet_version));
}

void CharSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	if (_packet_handler != nullptr && _packet_handler->session_has_expired()) {
		get_socket()->close_socket();
		return;
	}

	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
		_packet_handler->handle_received_packet(*buf);
	}
}

