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

#include "PacketHandlerRagexe20181024.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20181024::PacketHandlerRagexe20181024(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRagexe20181017(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20181024::~PacketHandlerRagexe20181024()
{
	//
}

void PacketHandlerRagexe20181024::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20181024::packets::packet, boost::bind(&PacketHandlerRagexe20181024::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
