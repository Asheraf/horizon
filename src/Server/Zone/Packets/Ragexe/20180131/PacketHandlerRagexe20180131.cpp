/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#include "PacketHandlerRagexe20180131.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20180131::PacketHandlerRagexe20180131(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRagexe20180124(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20180131::~PacketHandlerRagexe20180131()
{
	//
}

void PacketHandlerRagexe20180131::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20180131::packets::packet, boost::bind(&PacketHandlerRagexe20180131::Handle_ ## packet, this, boost::placeholders::_1));
	HANDLER_FUNC(CZ_ENTER)
#undef HANDLER_FUNC
#define SHUFFLE_HANDLER_FUNC(packet) add_packet_handler(Ragexe20180131::packets::packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1));
	SHUFFLE_HANDLER_FUNC(CZ_CHANGE_DIRECTION)
	SHUFFLE_HANDLER_FUNC(CZ_REQNAME)
	SHUFFLE_HANDLER_FUNC(CZ_REQUEST_MOVE)
	SHUFFLE_HANDLER_FUNC(CZ_REQUEST_TIME)
	SHUFFLE_HANDLER_FUNC(CZ_REQUEST_ACT)
#undef SHUFFLE_HANDLER_FUNC
}

bool PacketHandlerRagexe20180131::Handle_CZ_ENTER(PacketBuffer &buf)
{
	Ragexe20180131::PACKET_CZ_ENTER pkt;

	pkt << buf;

	if (!verify_new_connection(pkt.auth_code, pkt.account_id, pkt.char_id))
		return false;

	// Send initial packets.
	Send_ZC_AID();
	Send_ZC_ACCEPT_ENTER3();

	process_player_entry();

	return true;
}
