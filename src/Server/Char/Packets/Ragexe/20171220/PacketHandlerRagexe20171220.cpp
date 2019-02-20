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

#include "PacketHandlerRagexe20171220.hpp"

#include "Server/Char/Database/Query.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Common/Models/GameAccount.hpp"

using namespace Horizon::Char;
using namespace Horizon::Models::Character;

PacketHandlerRagexe20171220::PacketHandlerRagexe20171220(std::shared_ptr<CharSocket> socket)
: PacketHandler(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20171220::~PacketHandlerRagexe20171220()
{
	//
}

void PacketHandlerRagexe20171220::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20171220::packets::packet, boost::bind(&PacketHandlerRagexe20171220::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}

/**
 * @brief Send to the client with the HC_ACCEPT_ENTER packet on client connection.
 * @see packets
 * @overload PacketHandler::Send_HC_ACCEPT_ENTER()
 */
void PacketHandlerRagexe20171220::Send_HC_ACCEPT_ENTER()
{
	std::shared_ptr<CharSession> session = get_socket()->get_session();
	std::shared_ptr<GameAccount> game_account = session->get_game_account();

	Ragexe20171220::PACKET_HC_ACCEPT_ENTER pkt;

	CharQuery->load_all_characters_for_account(session->get_game_account());

	auto char_list = game_account->get_characters();

	pkt.packet_length = pkt.get_length(char_list.size());

	PacketBuffer buf = pkt.serialize();

	for (auto &c : char_list) {
		Ragexe20171220::PACKET_HC_ACCEPT_ENTER::character_list_data character;
		character.create_from_model(c.second);
		character.serialize(buf);
	}

	send_packet(buf);

	CharLog->info("Sent character-list information to AID {}", game_account->get_id());
}

void PacketHandlerRagexe20171220::Send_HC_ACCEPT_MAKECHAR(std::shared_ptr<Character> character)
{
	Ragexe20171220::PACKET_HC_ACCEPT_MAKECHAR pkt;

	pkt.character.create_from_model(character);
	PacketBuffer buf = pkt.serialize();
	send_packet(buf);
}
