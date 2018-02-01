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

#include "PacketHandler20171113.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Auth/Session/Session.hpp"

#include <boost/bind.hpp>

Horizon::Auth::PacketHandler20171113::PacketHandler20171113(std::shared_ptr<Session> session)
: PacketHandler20170315(session)
{
	InitializeHandlers();
}

Horizon::Auth::PacketHandler20171113::~PacketHandler20171113()
{
}

void Horizon::Auth::PacketHandler20171113::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{

}

void Horizon::Auth::PacketHandler20171113::Handle_Poly(PacketBuffer &/*buf*/)
{
	AuthLog->info("20171113 Poly Overloaded!");
}

void Horizon::Auth::PacketHandler20171113::InitializeHandlers()
{
	PacketHandler20170315::InitializeHandlers();
	addPacketHandler(CA_LOGIN, boost::bind(&PacketHandler::Handle_CA_LOGIN, this, boost::placeholders::_1));
}
