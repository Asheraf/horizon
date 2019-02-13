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

#include "PacketHandlerRagexe20170906.hpp"

#include "Server/Char/Database/Query.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"

using namespace Horizon::Char;
PacketHandlerRagexe20170906::PacketHandlerRagexe20170906(std::shared_ptr<CharSocket> socket)
: PacketHandlerRagexe20170228(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20170906::~PacketHandlerRagexe20170906()
{
	//
}

void PacketHandlerRagexe20170906::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20170906::packets::packet, boost::bind(&PacketHandlerRagexe20170906::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}

/**
 * @brief Send to the client with the HC_ACCEPT_ENTER packet on client connection.
 * @see packets
 * @overload PacketHandler::Send_HC_ACCEPT_ENTER()
 */
void PacketHandlerRagexe20170906::Send_HC_ACCEPT_ENTER()
{
	std::shared_ptr<CharSession> session = get_socket()->get_session();
	std::shared_ptr<GameAccount> game_account = session->get_game_account();

	Ragexe20170906::PACKET_HC_ACCEPT_ENTER pkt;

	CharQuery->load_all_characters_for_account(session->get_game_account());

	auto char_list = game_account->get_characters();

	pkt.packet_length = pkt.get_length(char_list.size());

	PacketBuffer buf = pkt.serialize();

	for (auto &c : char_list) {
		Ragexe20170906::PACKET_HC_ACCEPT_ENTER::character_list_data character;
		character.create_from_model(c.second);
		character.serialize(buf);
	}

	send_packet(buf);

	CharLog->info("Sent character-list information to AID {}", game_account->get_id());
}
