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

#include "Server/Char/SocketMgr/InterSocketMgr.hpp"
#include "Server/Char/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Char/PacketHandler/InterPacketHandler.hpp"
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"

#include <random>

Horizon::Char::InterSession::InterSession(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void Horizon::Char::InterSession::Start()
{
	PacketBuffer buf;
	CharLog->info("Established connection from {}.", getRemoteIPAddress());
	setPacketHandler(PacketHandlerFactory::CreateInterPacketHandler(shared_from_this()));
	getPacketHandler()->setClientType(INTER_CONNECT_CLIENT_CHAR);
	getPacketHandler()->ReceiveAndHandle(buf);
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Char::InterSession::OnClose()
{
	CharLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	InterSocktMgr->ClearSession(INTER_SESSION_NAME, shared_from_this());
}

void Horizon::Char::InterSession::ReadHandler()
{
	//
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Char::InterSession::Update()
{
	return CharSocket::Update();
}

const std::shared_ptr<Horizon::Char::InterPacketHandler> &Horizon::Char::InterSession::getPacketHandler() const
{
	return _packet_handler;
}

void Horizon::Char::InterSession::setPacketHandler(std::shared_ptr<InterPacketHandler> handler)
{
	_packet_handler = handler;
}

