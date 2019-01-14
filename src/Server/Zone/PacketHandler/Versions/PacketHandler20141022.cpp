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

#include "PacketHandler20141022.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

Horizon::Zone::PacketHandler20141022::PacketHandler20141022(std::shared_ptr<ZoneSocket> socket)
: Horizon::Zone::PacketHandler(socket)
{
	initialize_handlers();
}

Horizon::Zone::PacketHandler20141022::~PacketHandler20141022()
{
	//
}

void Horizon::Zone::PacketHandler20141022::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(PacketVer20141022::packets::packet, boost::bind(&PacketHandler20141022::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_ENTER);
	HANDLER_FUNC(CZ_REQUEST_TIME);
	HANDLER_FUNC(CZ_REQNAME);
	HANDLER_FUNC(CZ_REQUEST_ACT);
	HANDLER_FUNC(CZ_REQUEST_MOVE);
#undef HANDLER_FUNC
}


