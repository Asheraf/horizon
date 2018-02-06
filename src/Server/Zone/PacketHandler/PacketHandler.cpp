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

#include "PacketHandler.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/Session/Session.hpp"
#include "Server/Common/Models/SessionData.hpp"

#include <boost/bind.hpp>

/**
 * @brief Packet Handler Constructor.
 */
Horizon::Zone::PacketHandler::PacketHandler(std::shared_ptr<Session> session)
: Horizon::Base::PacketHandler<Session>(session)
{
	InitializeHandlers();
}

/**
 * @brief Packet Handler destructor.
 */
Horizon::Zone::PacketHandler::~PacketHandler()
{
}

/**
 * @brief Initialize packet handlers.
 */
void Horizon::Zone::PacketHandler::InitializeHandlers()
{
#define HANDLER_FUNC(packet) addPacketHandler(packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}

/*==============*
 * Handler Methods
 *==============*/


/*==============*
 * Responder Methods
 *==============*/

