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

#include "AuthSocket.hpp"

#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Auth/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Auth/PacketHandler/PacketHandler.hpp"
#include "Server/Auth/Session/AuthSession.hpp"

#include <random>

using namespace Horizon::Auth;

AuthSocket::AuthSocket(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

AuthSocket::~AuthSocket()
{

}

/**
 * @thread created by network thread and called from main thread / client-sockt-mgr for update().
 */
std::shared_ptr<AuthSession> AuthSocket::get_session() { return std::atomic_load(&_session); }
void AuthSocket::set_session(std::shared_ptr<AuthSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the AuthSocket.
 */
void AuthSocket::start()
{
	AuthLog->info("Established connection from {}.", remote_ip_address());
	set_session(std::make_shared<AuthSession>(shared_from_this()));
	async_read();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void AuthSocket::on_close()
{
	AuthLog->info("Closed connection from {}.", remote_ip_address());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	ClientSocktMgr->clear_socket(shared_from_this());
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool AuthSocket::update()
{
	return BaseSocket::update();
}

void AuthSocket::read_handler()
{
	while (get_read_buffer().get_active_size()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, get_read_buffer().get_read_pointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, get_read_buffer().get_read_pointer(), get_read_buffer().get_active_size());
		get_read_buffer().read_completed(get_read_buffer().get_active_size());
		_packet_recv_queue.push(std::move(pkt));
	}
}
