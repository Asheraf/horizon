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

#include "PacketHandlerZero20180808.hpp"

using namespace Horizon::Zone;
PacketHandlerZero20180808::PacketHandlerZero20180808(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerZero20180801(socket)
{
	initialize_handlers();
}

PacketHandlerZero20180808::~PacketHandlerZero20180808()
{
	//
}

void PacketHandlerZero20180808::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Zero20180808::packets::packet, boost::bind(&PacketHandlerZero20180808::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
