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

#include "InterSession.hpp"

#include "Server/Auth/SocketMgr/InterSocketMgr.hpp"
#include "Server/Auth/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Auth/PacketHandler/InterPacketHandler.hpp"
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"

#include <random>

Horizon::Auth::InterSession::InterSession(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void Horizon::Auth::InterSession::start()
{
	PacketBuffer buf;
	AuthLog->info("Established connection from {}.", getRemoteIPAddress());
	setPacketHandler(PacketHandlerFactory::CreateInterPacketHandler(shared_from_this()));
	getPacketHandler()->ReceiveAndHandle(buf);
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Auth::InterSession::onClose()
{
	AuthLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	InterSocktMgr->ClearSession(INTER_SESSION_NAME, shared_from_this());
}

void Horizon::Auth::InterSession::readHandler()
{
	// Not required for Inter Sessions.
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Auth::InterSession::update()
{
	return AuthSocket::update();
}

std::shared_ptr<Horizon::Auth::InterPacketHandler> Horizon::Auth::InterSession::getPacketHandler()
{
	return std::atomic_load(&_packet_handler);
}

void Horizon::Auth::InterSession::setPacketHandler(std::shared_ptr<InterPacketHandler> handler)
{
	std::atomic_store(&_packet_handler, handler);
}
