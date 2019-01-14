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
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
#include "Server/Zone/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Zone/PacketHandler/InterPacketHandler.hpp"
#include "Server/Zone/Session/InterSession.hpp"

#include <random>

using namespace Horizon::Zone;

InterSocket::InterSocket(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * Session dependency.
 * @thread set by network thread and retrieved from another thread for pings and re-connection.
 * @note requires atomic loading and storing of the reference count and pointer.
 */
std::shared_ptr<InterSession> InterSocket::get_session() { return std::atomic_load(&_session); }
void InterSocket::set_session(std::shared_ptr<InterSession> session) { std::atomic_store(&_session, session); }

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void InterSocket::start()
{
	ZoneLog->info("Established connection from {}.", remote_ip_address());
	set_session(std::make_shared<InterSession>(shared_from_this()));
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void InterSocket::on_close()
{
	ZoneLog->info("Closed connection from {}.", remote_ip_address());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	InterSocktMgr->finalize_connector_socket(INTER_SESSION_NAME, shared_from_this());
}

void InterSocket::read_handler()
{
	//
}

bool InterSocket::update()
{
	return BaseSocket::update();
}
