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

#include "PacketHandlerRE20130612.hpp"

using namespace Horizon::Common;
using namespace Horizon::Common::RE20130612;

PacketHandlerRE20130612::PacketHandlerRE20130612(std::shared_ptr<CommonSocket> socket)
: PacketHandlerRE20130605(socket)
{
	initialize_handlers();
}

PacketHandlerRE20130612::~PacketHandlerRE20130612()
{
	//
}

void PacketHandlerRE20130612::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(RE20130612::packets::packet, boost::bind(&PacketHandlerRE20130612::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
