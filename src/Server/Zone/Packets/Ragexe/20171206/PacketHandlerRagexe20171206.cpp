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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#include "PacketHandlerRagexe20171206.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NOTIFY_STANDENTRY11.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NOTIFY_MOVEENTRY11.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20171206::PacketHandlerRagexe20171206(std::shared_ptr<ZoneSocket> socket)
: PacketHandler(socket)
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
	Send_ZC_ACCEPT_ENTER2();

	process_player_entry();

	return true;
}

void PacketHandlerRagexe20171206::Send_ZC_NOTIFY_STANDENTRY(entity_viewport_entry const &entry)
{
	Ragexe::PACKET_ZC_NOTIFY_STANDENTRY11 pkt;

	pkt.entry = entry;

	// set here params.
	send_packet(pkt.serialize());
}

void PacketHandlerRagexe20171206::Send_ZC_NOTIFY_MOVEENTRY(entity_viewport_entry const &entry)
{
	Ragexe::PACKET_ZC_NOTIFY_MOVEENTRY11 pkt;
	pkt.entry = entry;
	send_packet(pkt.serialize());
}

