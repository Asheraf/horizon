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

#include "PacketHandlerRE20180502.hpp"

using namespace Horizon::Zone;
PacketHandlerRE20180502::PacketHandlerRE20180502(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRE20180425(socket)
{
	initialize_handlers();
}

PacketHandlerRE20180502::~PacketHandlerRE20180502()
{
	//
}

void PacketHandlerRE20180502::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(RE20180502::packets::packet, boost::bind(&PacketHandlerRE20180502::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
