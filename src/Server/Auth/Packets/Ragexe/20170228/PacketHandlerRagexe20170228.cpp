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

#include "PacketHandlerRagexe20170228.hpp"
#include "Server/Auth/Packets/Ragexe/PacketStructs.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;
PacketHandlerRagexe20170228::PacketHandlerRagexe20170228(std::shared_ptr<AuthSocket> socket)
: PacketHandler(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20170228::~PacketHandlerRagexe20170228()
{
	//
}

void PacketHandlerRagexe20170228::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20170228::packets::packet, boost::bind(&PacketHandlerRagexe20170228::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}

void PacketHandlerRagexe20170228::Send_AC_ACCEPT_LOGIN()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<SessionData> session_data = get_socket()->get_session()->get_session_data();
	const CharacterServerMapType char_servers = AuthServer->get_character_servers();
	Ragexe20170228::PACKET_AC_ACCEPT_LOGIN pkt;
	Ragexe20170228::PACKET_AC_ACCEPT_LOGIN::character_server_list *server_list = nullptr;

	/**
	 * Reject if no character servers.
	 */
	if (char_servers.empty()) {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_REJECTED_FROM_SERVER);
		return;
	}

	server_list = new Ragexe20170228::PACKET_AC_ACCEPT_LOGIN::character_server_list[char_servers.size()];

	pkt.packet_len = pkt.get_length(char_servers.size());
	pkt.auth_code = session_data->get_auth_code();
	pkt.aid = game_account->get_id();
	pkt.user_level = 1;
	pkt.last_login_ip = 0; // not used anymore.
	memset(pkt.last_login_time, '\0', sizeof(pkt.last_login_time)); // Not used anymore
	pkt.sex = (uint8_t) game_account->get_gender();

	PacketBuffer buf = pkt.serialize();

	int i = 0;
	for (auto &chr : char_servers) {
		server_list[i].ip = inet_addr(chr.second->ip_address.c_str());
		server_list[i].port = chr.second->port;
		strncpy(server_list[i].name, chr.second->name.c_str(), sizeof(server_list[i].name));
		server_list[i].type = (uint16_t) chr.second->server_type;
		server_list[i].is_new = chr.second->is_new;
		server_list[i].usercount = 88;
		server_list[i].serialize(buf);
		++i;
	}

	delete[] server_list;

	send_packet(buf);
}
