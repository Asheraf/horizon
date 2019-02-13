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

#include "PacketHandlerRagexe20170104.hpp"

#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/Character/Position.hpp"
#include "Server/Common/Models/Character/UISettings.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NOTIFY_STANDENTRY11.hpp"
#include "Server/Zone/Packets/Ragexe/Structs/PACKET_ZC_NOTIFY_MOVEENTRY11.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20170104::PacketHandlerRagexe20170104(std::shared_ptr<ZoneSocket> socket)
: PacketHandler(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20170104::~PacketHandlerRagexe20170104()
{
	//
}

void PacketHandlerRagexe20170104::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20170104::packets::packet, boost::bind(&PacketHandlerRagexe20170104::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}

void PacketHandlerRagexe20170104::Send_ZC_ACCEPT_ENTER3()
{
	std::shared_ptr<Models::Character::Character> character = get_socket()->get_session()->get_character();
	std::shared_ptr<Models::Character::Position> position = character->get_position_data();
	std::shared_ptr<Models::Character::UISettings> ui_settings = character->get_ui_settings();

	Ragexe20170104::PACKET_ZC_ACCEPT_ENTER3 pkt;
	int x = position->get_current_x();
	int y = position->get_current_y();

	if (x == 0 && y == 0) {
		if ((x = position->get_saved_x()) == 0)
			x = 0;
		if ((y = position->get_saved_y()) == 0)
			y = 0;
	}

	pkt.start_time = time(nullptr);
	pkt.x_size = pkt.y_size = 5;
	pkt.font = ui_settings->get_font();
	send_packet(pkt.serialize(x, y, DIR_NORTH));
}

void PacketHandlerRagexe20170104::Send_ZC_NOTIFY_STANDENTRY(entity_viewport_entry const &entry)
{
	Ragexe::PACKET_ZC_NOTIFY_STANDENTRY11 pkt;

	pkt.entry = entry;

	// set here params.
	send_packet(pkt.serialize());
}

void PacketHandlerRagexe20170104::Send_ZC_NOTIFY_MOVEENTRY(entity_viewport_entry const &entry)
{
	Ragexe::PACKET_ZC_NOTIFY_MOVEENTRY11 pkt;
	pkt.entry = entry;
	send_packet(pkt.serialize());
}
