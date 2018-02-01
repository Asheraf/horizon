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

#include "Libraries/BCrypt/BCrypt.hpp"
#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Session/InterSession.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"

#include <boost/bind.hpp>

Horizon::Auth::InterPacketHandler::InterPacketHandler(std::shared_ptr<InterSession> session)
: Horizon::Base::InterPacketHandler<InterSession>(session, AuthServer->getNetworkConf().getInterServerPassword())
{
	// Construct
	InitializeHandlers();
}

Horizon::Auth::InterPacketHandler::~InterPacketHandler()
{
	// Destruct
}

void Horizon::Auth::InterPacketHandler::InitializeHandlers()
{
	Base::InterPacketHandler<InterSession>::InitializeHandlers();

#define HANDLER_FUNC(packet, handler) addPacketHandler(packet, boost::bind(handler, this, boost::placeholders::_1))
	//
#undef HANDLER_FUNC
}

