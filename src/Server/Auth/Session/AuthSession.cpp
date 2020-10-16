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

#include "Server/Auth/Interface/AuthClientInterface.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Common/SQL/GameAccount.hpp"
#include "Server/Common/SQL/SessionData.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

AuthSession::AuthSession(std::shared_ptr<AuthSocket> socket)
: Networking::Session<AuthSocket, AuthSession>(socket)
{
}

AuthSession::~AuthSession()
{
	//
}

void AuthSession::initialize()
{
	_pkt_tbl = std::make_unique<ClientPacketLengthTable>(shared_from_this());
	_clif = std::make_unique<AuthClientInterface>(shared_from_this());
}

void AuthSession::transmit_buffer(ByteBuffer _buffer, std::size_t size)
{
	if (get_socket() == nullptr || !get_socket()->is_open())
		return;
	
	if (!_buffer.is_empty()) {
		get_socket()->queue_buffer(std::move(_buffer));
	}
}

void AuthSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	std::shared_ptr<ByteBuffer> read_buf;
	while ((read_buf = get_socket()->_buffer_recv_queue.try_pop())) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, read_buf->get_read_pointer(), sizeof(uint16_t));
		PacketTablePairType p = _pkt_tbl->get_packet_info(packet_id);
		
		HLog(debug) << "Handling packet 0x" << std::hex << packet_id << " - 0x" << p.first << std::endl;
		
		p.second->handle(std::move(*read_buf));
	}
}
