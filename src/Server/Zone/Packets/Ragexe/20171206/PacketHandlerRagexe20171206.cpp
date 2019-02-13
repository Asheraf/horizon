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

#include "PacketHandlerRagexe20171206.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20171206::PacketHandlerRagexe20171206(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRagexe20171129(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20171206::~PacketHandlerRagexe20171206()
{
	//
}

void PacketHandlerRagexe20171206::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20171206::packets::packet, boost::bind(&PacketHandlerRagexe20171206::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_ENTER)
#undef HANDLER_FUNC
#define SHUFFLE_HANDLER_FUNC(packet) add_packet_handler(Ragexe20171206::packets::packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	SHUFFLE_HANDLER_FUNC(CZ_CHANGE_DIRECTION)
	SHUFFLE_HANDLER_FUNC(CZ_REQNAME)
	SHUFFLE_HANDLER_FUNC(CZ_REQUEST_MOVE)
	SHUFFLE_HANDLER_FUNC(CZ_REQUEST_TIME)
	SHUFFLE_HANDLER_FUNC(CZ_REQUEST_ACT)
#undef SHUFFLE_HANDLER_FUNC
}

bool PacketHandlerRagexe20171206::Handle_CZ_ENTER(PacketBuffer &buf)
{
	Ragexe20171206::PACKET_CZ_ENTER pkt;

	pkt << buf;

	if (!verify_new_connection(pkt.auth_code, pkt.account_id, pkt.char_id))
		return false;

	// Send initial packets.
	Send_ZC_AID();
	Send_ZC_ACCEPT_ENTER3();

	process_player_entry();

	return true;
}
