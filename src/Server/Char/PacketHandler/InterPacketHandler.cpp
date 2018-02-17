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

#include "InterPacketHandler.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Char/Char.hpp"
#include "Server/Char/Session/InterSession.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"

#include <boost/bind.hpp>

Horizon::Char::InterPacketHandler::InterPacketHandler(std::shared_ptr<InterSession> session)
: Horizon::Base::InterPacketHandler<InterSession>(session, CharServer->getNetworkConf().getInterServerPassword(), INTER_CONNECT_CLIENT_CHAR)
{
	// Construct
	InitializeHandlers();
}

Horizon::Char::InterPacketHandler::~InterPacketHandler()
{
	// Destruct
}

void Horizon::Char::InterPacketHandler::InitializeHandlers()
{
	Base::InterPacketHandler<InterSession>::InitializeHandlers();

#define HANDLER_FUNC(packet, handler) addPacketHandler(packet, boost::bind(handler, this, boost::placeholders::_1))
	///
#undef HANDLER_FUNC
}
