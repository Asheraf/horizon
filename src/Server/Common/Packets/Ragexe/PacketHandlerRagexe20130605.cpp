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

#include "PacketHandlerRagexe20130605.hpp"

using namespace Horizon::Common;
using namespace Horizon::Common::Ragexe20130605;

PacketHandlerRagexe20130605::PacketHandlerRagexe20130605(std::shared_ptr<CommonSocket> socket)
: PacketHandlerRagexe20080624(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20130605::~PacketHandlerRagexe20130605()
{
	//
}

void PacketHandlerRagexe20130605::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20130605::packets::packet, boost::bind(&PacketHandlerRagexe20130605::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
