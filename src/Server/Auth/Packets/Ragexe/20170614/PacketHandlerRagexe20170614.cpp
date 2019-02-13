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

#include "PacketHandlerRagexe20170614.hpp"

using namespace Horizon::Auth;
PacketHandlerRagexe20170614::PacketHandlerRagexe20170614(std::shared_ptr<AuthSocket> socket)
: PacketHandlerRagexe20170228(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20170614::~PacketHandlerRagexe20170614()
{
	//
}

void PacketHandlerRagexe20170614::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20170614::packets::packet, boost::bind(&PacketHandlerRagexe20170614::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
