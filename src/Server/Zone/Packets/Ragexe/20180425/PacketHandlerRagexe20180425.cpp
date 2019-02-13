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

#include "PacketHandlerRagexe20180425.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20180425::PacketHandlerRagexe20180425(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRagexe20180418(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20180425::~PacketHandlerRagexe20180425()
{
	//
}

void PacketHandlerRagexe20180425::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20180425::packets::packet, boost::bind(&PacketHandlerRagexe20180425::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
