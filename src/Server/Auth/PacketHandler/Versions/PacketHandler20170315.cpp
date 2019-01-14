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

#include "PacketHandler20170315.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"

#include <boost/bind.hpp>

Horizon::Auth::PacketHandler20170315::PacketHandler20170315(std::shared_ptr<AuthSocket> socket)
: Horizon::Auth::PacketHandler(socket)
{
	initialize_handlers();
}

Horizon::Auth::PacketHandler20170315::~PacketHandler20170315()
{
}

void Horizon::Auth::PacketHandler20170315::Send_AC_ACCEPT_LOGIN()
{
	// Override common handler.
	AuthLog->info("Overloaded!");
	Send_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
}

void Horizon::Auth::PacketHandler20170315::Handle_TEST_POLY(PacketBuffer &buf)
{
	PACKET_CA_LOGIN pkt;
	buf >> pkt;

	AuthLog->info("poly working {}", pkt.version);
	Send_AC_ACCEPT_LOGIN();
}

void Horizon::Auth::PacketHandler20170315::initialize_handlers()
{
	Horizon::Auth::PacketHandler::initialize_handlers();
	add_packet_handler(CA_LOGIN, boost::bind(&PacketHandler20170315::Handle_TEST_POLY, this, boost::placeholders::_1));
}
