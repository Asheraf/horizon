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
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include "Server/Zone/Zone.hpp"
#include "Server/Zone/Socket/InterSocket.hpp"

#include <boost/bind.hpp>

Horizon::Zone::InterPacketHandler::InterPacketHandler(std::shared_ptr<InterSocket> socket)
: Horizon::Base::InterPacketHandler<InterSocket>(socket, ZoneServer->network_conf().get_inter_server_password(), INTER_CONNECT_CLIENT_ZONE)
{
	// Construct
	initialize_handlers();
}

Horizon::Zone::InterPacketHandler::~InterPacketHandler()
{
	// Destruct
}

void Horizon::Zone::InterPacketHandler::initialize_handlers()
{
	Base::InterPacketHandler<InterSocket>::initialize_handlers();

#define HANDLER_FUNC(packet, handler) add_packet_handler(packet, boost::bind(handler, this, boost::placeholders::_1))
	///
#undef HANDLER_FUNC
}

