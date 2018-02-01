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

void Horizon::Auth::InterSession::Start()
{
	PacketBuffer buf;
	AuthLog->info("Established connection from {}.", getRemoteIPAddress());
	setPacketHandler(PacketHandlerFactory::CreateInterPacketHandler(shared_from_this()));
	getPacketHandler()->ReceiveAndHandle(buf);
	getPacketHandler()->setClientType(INTER_CONNECT_CLIENT_AUTH);
}

void Horizon::Auth::InterSession::OnClose()
{
	AuthLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	InterSocktMgr->ClearSession(INTER_SESSION_NAME, shared_from_this());
}

void Horizon::Auth::InterSession::ReadHandler()
{
	//
}

bool Horizon::Auth::InterSession::Update()
{
	return AuthSocket::Update();
}

const std::shared_ptr<Horizon::Auth::InterPacketHandler> &Horizon::Auth::InterSession::getPacketHandler() const
{
	return _packet_handler;
}

void Horizon::Auth::InterSession::setPacketHandler(std::shared_ptr<InterPacketHandler> handler)
{
	_packet_handler = handler;
}
