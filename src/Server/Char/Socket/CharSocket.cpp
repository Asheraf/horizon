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

#include "CharSocket.hpp"

#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Char/Char.hpp"

#include <memory>

using namespace Horizon::Char;

CharSocket::CharSocket(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
	//
}

CharSocket::~CharSocket()
{
	//
}

/**
 * @thread created by network thread and called from main thread / client-sockt-mgr for update().
 */
std::shared_ptr<CharSession> CharSocket::get_session() { return std::atomic_load(&_session); }
void CharSocket::set_session(std::shared_ptr<CharSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the CharSocket.
 */
void CharSocket::start()
{
	auto session = std::make_shared<CharSession>(shared_from_this());

	set_session(session);

	session->initialize();

	HLog(info) << "Established connection from " << remote_ip_address() << ".";

	// Start async_read loop.
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void CharSocket::on_close()
{
	HLog(info) << "Closed connection from " << remote_ip_address() << ".";

	/* Perform socket manager cleanup. */
	ClientSocktMgr->set_socket_for_removal(shared_from_this());
}

void CharSocket::on_error()
{

}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool CharSocket::update()
{
	if (sChar->get_shutdown_stage() > SHUTDOWN_NOT_STARTED)
		ClientSocktMgr->set_socket_for_removal(shared_from_this());

	return BaseSocket::update();
}

/**
 * Incoming buffer read handler.
 */
void CharSocket::read_handler()
{
	while (get_read_buffer().active_length()) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, get_read_buffer().get_read_pointer(), sizeof(uint16_t));
		
		PacketTablePairType p = get_session()->pkt_tbl()->get_packet_info(packet_id);
		
		int16_t packet_length = p.first;
		
		HLog(debug) << "Received packet 0x" << packet_id << " of length " << packet_length << " from client.";
		HLog(debug) << "Data:" << get_read_buffer().to_string();
		
		if (packet_length == -1) {
			memcpy(&packet_length, get_read_buffer().get_read_pointer() + 2, sizeof(int16_t));
			if (get_read_buffer().active_length() < packet_length) {
				HLog(debug) << "Received packet 0x" << packet_id << " has expected length " << packet_length << " but buffer only supplied " << get_read_buffer().active_length() << " from client.";
				break;
			}
		} else if (packet_length == 0) {
			HLog(warning) << "Received non-existent packet id 0x" << std::hex << packet_id << ", disconnecting session..." << std::endl;
			get_read_buffer().read_completed(get_read_buffer().active_length());
			close_socket();
			break;
		}
		
		ByteBuffer b;
		b.append(get_read_buffer().get_read_pointer(), packet_length);
		get_recv_queue().push(std::move(b));
		get_read_buffer().read_completed(packet_length);
	}
}

void CharSocket::update_session(uint32_t diff)
{
	get_session()->update(diff);
}
