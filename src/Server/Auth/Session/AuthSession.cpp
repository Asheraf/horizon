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

#include "AuthSession.hpp"

#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Common/SQL/GameAccount.hpp"
#include "Server/Common/SQL/SessionData.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

AuthSession::AuthSession(std::shared_ptr<AuthSocket> socket)
: Networking::Session<AuthSocket>(socket), _clif(socket)
{
}

AuthSession::~AuthSession()
{
	//
}

void AuthSession::initialize()
{
}

void AuthSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

//	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
//		if (_packet_handler == nullptr) {
//			HLog(error) <<"Packet handler was null!");
//			return;
//		}

//		_packet_handler->handle_received_packet(*buf);
//	}
}
