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

#include "InterSocket.hpp"

#include "Server/Common/Base/PacketHandler/InterPackets.hpp"
#include "Server/Auth/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Auth/PacketHandler/InterPacketHandler.hpp"
#include "Server/Auth/Session/InterSession.hpp"
#include "Server/Auth/SocketMgr/InterSocketMgr.hpp"

#include <random>

using namespace Horizon::Auth;

InterSocket::InterSocket(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * @thread created by network thread and called from main thread for pings and re-connection.
 */
std::shared_ptr<InterSession> InterSocket::get_session() { return std::atomic_load(&_session); }
void InterSocket::set_session(std::shared_ptr<InterSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void InterSocket::start()
{
	AuthLog->info("Established connection from {}.", remote_ip_address());
	set_session(std::make_shared<InterSession>(shared_from_this()));
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void InterSocket::on_close()
{
	AuthLog->info("Closed connection from {}.", remote_ip_address());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	InterSocktMgr->finalize_connector_socket(INTER_SESSION_NAME, shared_from_this());
}

void InterSocket::read_handler()
{
	// Not required for Inter Sessions.
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool InterSocket::update()
{
	return BaseSocket::update();
}
