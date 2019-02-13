/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "PacketHandlerZero20180711.hpp"

using namespace Horizon::Zone;
PacketHandlerZero20180711::PacketHandlerZero20180711(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerZero20180703(socket)
{
	initialize_handlers();
}

PacketHandlerZero20180711::~PacketHandlerZero20180711()
{
	//
}

void PacketHandlerZero20180711::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Zero20180711::packets::packet, boost::bind(&PacketHandlerZero20180711::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
