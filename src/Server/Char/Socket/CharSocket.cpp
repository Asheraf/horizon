/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "CharSocket.hpp"

#include "Server/Char/Packets/PacketHandlerFactory.hpp"
#include "Server/Char/Packets/PacketHandler.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"

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
 * Session dependency.
 * @thread created by network thread and called from another thread for pings and re-connection.
 * @note requires atomic loading and storing of the reference count and pointer.
 */
std::shared_ptr<CharSession> CharSocket::get_session() { return std::atomic_load(&_session); }
void CharSocket::set_session(std::shared_ptr<CharSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the CharSocket.
 */
void CharSocket::start()
{
	CharLog->info("Established connection from {}.", remote_ip_address());
	set_session(std::make_shared<CharSession>(shared_from_this()));
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void CharSocket::on_close()
{
	CharLog->info("Closed connection from {}.", remote_ip_address());

	/* Perform socket manager cleanup. */
	ClientSocktMgr->remove_socket(get_socket_id());
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
	return BaseSocket::update();
}

/**
 * Incoming buffer read handler.
 */
void CharSocket::read_handler()
{
	while (get_read_buffer().get_active_size()) {
		uint16_t packet_id = 0x0;
		memcpy(&packet_id, get_read_buffer().get_read_pointer(), sizeof(uint16_t));

		int16_t packet_length = GET_CHAR_PACKETLEN(packet_id);

		if (packet_length == -1) {
			memcpy(&packet_length, get_read_buffer().get_read_pointer() + 2, sizeof(int16_t));
		} else if (packet_length == 0) {
			CharLog->warn("Received non-existent packet id {0:x}, disconnecting session...", packet_id);
			close_socket();
			break;
		}

		PacketBuffer buf(get_read_buffer().get_read_pointer(), packet_length);
		get_read_buffer().read_completed(packet_length);

		_packet_recv_queue.push(std::move(buf));
	}
}

void CharSocket::update_session(uint32_t diff)
{
	get_session()->update(diff);
}
