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

#include "Server/Common/Base/PacketHandler/InterPackets.hpp"
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
#include "Server/Zone/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Zone/PacketHandler/InterPacketHandler.hpp"

#include <random>

Horizon::Zone::InterSession::InterSession(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void Horizon::Zone::InterSession::Start()
{
	PacketBuffer buf;
	ZoneLog->info("Established connection from {}.", getRemoteIPAddress());
	setPacketHandler(PacketHandlerFactory::CreateInterPacketHandler(shared_from_this()));
	getPacketHandler()->setClientType(INTER_CONNECT_CLIENT_ZONE);
	getPacketHandler()->ReceiveAndHandle(buf);
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Zone::InterSession::OnClose()
{
	ZoneLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	InterSocktMgr->ClearSession(INTER_SESSION_NAME, shared_from_this());
}

void Horizon::Zone::InterSession::ReadHandler()
{
	//
}

bool Horizon::Zone::InterSession::Update()
{
	return CharSocket::Update();
}

const std::shared_ptr<Horizon::Zone::InterPacketHandler> &Horizon::Zone::InterSession::getPacketHandler() const
{
	return _packet_handler;
}

void Horizon::Zone::InterSession::setPacketHandler(std::shared_ptr<InterPacketHandler> handler)
{
	_packet_handler = handler;
}


