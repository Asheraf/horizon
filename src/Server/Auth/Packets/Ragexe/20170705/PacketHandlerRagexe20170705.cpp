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

#include "PacketHandlerRagexe20170705.hpp"

using namespace Horizon::Auth;
PacketHandlerRagexe20170705::PacketHandlerRagexe20170705(std::shared_ptr<AuthSocket> socket)
: PacketHandlerRagexe20170621(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20170705::~PacketHandlerRagexe20170705()
{
	//
}

void PacketHandlerRagexe20170705::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20170705::packets::packet, boost::bind(&PacketHandlerRagexe20170705::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
