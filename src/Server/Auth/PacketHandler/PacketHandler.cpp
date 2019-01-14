/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "PacketHandler.hpp"

#include "Core/Database/MySqlConnection.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/SocketMgr/InterSocketMgr.hpp"
#include "Server/Auth/Interface/InterAPI.hpp"
#include "Server/Auth/PacketHandler/InterPacketHandler.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include "Server/Common/Models/Character/Group.hpp"
#include "Server/Auth/Auth.hpp"

#include <string>

Horizon::Auth::PacketHandler::PacketHandler(std::shared_ptr<AuthSocket> socket)
	: Horizon::Base::PacketHandler<AuthSocket>(socket)
{
	// Construct
	initialize_handlers();
}

Horizon::Auth::PacketHandler::~PacketHandler()
{
	// Destruct
}

void Horizon::Auth::PacketHandler::initialize_handlers()
{
#define HANDLER_FUNC(packet) add_packet_handler(packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1))
	HANDLER_FUNC(CA_LOGIN);
	HANDLER_FUNC(CA_REQ_HASH);
	HANDLER_FUNC(CA_LOGIN2);
	HANDLER_FUNC(CA_LOGIN3);
	HANDLER_FUNC(CA_CONNECT_INFO_CHANGED);
	HANDLER_FUNC(CA_EXE_HASHCHECK);
	HANDLER_FUNC(CA_LOGIN_PCBANG);
	HANDLER_FUNC(CA_LOGIN4);
	HANDLER_FUNC(CA_LOGIN_HAN);
	HANDLER_FUNC(CA_SSO_LOGIN_REQ);
	HANDLER_FUNC(CA_LOGIN_OTP);
#undef HANDLER_FUNC
}

bool Horizon::Auth::PacketHandler::validate_session_data(std::shared_ptr<GameAccount> game_account, uint32_t client_version, uint8_t client_type)
{
	std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();

	if (AuthInterAPI->get_session_data(game_account->get_id()) != nullptr) {
		// @TODO Check if online in char-server & map-server.
		AuthInterAPI->delete_game_account(game_account->get_id());
		AuthInterAPI->delete_session(game_account->get_id());
		return false;
	}
	
	// Game Account Data.
	game_account->set_last_ip(get_socket()->remote_ip_address());
	game_account->set_last_login((int) time(nullptr));
	
	// Session Data.
	session_data->set_auth_code(game_account->get_id()); // @TODO Change to something unique to prevent session hijaking.
	session_data->set_game_account_id(game_account->get_id());
	session_data->set_client_version(client_version);
	session_data->set_client_type(client_type);
	session_data->set_character_slots(game_account->get_character_slots());
	session_data->set_group_id(game_account->get_group_id());

	get_socket()->get_session()->set_session_data(session_data);

	// Send session data to inter.
	AuthInterAPI->store_session_data(session_data);
	AuthInterAPI->store_game_account(game_account);
	return true;
}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN(PacketBuffer &packet)
{
	PACKET_CA_LOGIN pkt;
	bool authenticated = false;
	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();

	packet >> pkt;

	if (pkt.version < MINIMUM_PACKETVER || pkt.version > MAXIMUM_PACKETVER) {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Authentication of account '{}' rejected. Unsupported Version.", pkt.username, pkt.version);
		return;
	}

	if (!InterSocktMgr->connector_pool_size(INTER_SESSION_NAME)) {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_NONE);
		AuthLog->info("Authentication of account '{}' rejected. Inter server not available.", pkt.username);
		return;
	}

	AuthLog->info("Authentication of account '{}' requested. (Client Version: {}, Type: {})", pkt.username, pkt.version, pkt.client_type);

	switch (AuthServer->get_auth_config().getPassHashMethod())
	{
	case PASS_HASH_NONE:
	case PASS_HASH_MD5:
		authenticated = game_account->verify_credentials(AuthServer, pkt.username, pkt.password);
		break;
	case PASS_HASH_BCRYPT:
		authenticated = game_account->verify_credentials_bcrypt(AuthServer, pkt.username, pkt.password);
		break;
	}

	if (authenticated) {
		if (game_account == nullptr) {
			AuthLog->error("nullptr gameaccount!?!?!");
			return;
		}

		get_socket()->get_session()->set_game_account(game_account);

		AuthLog->info("Authentication of account '{}' granted.", pkt.username);

		if (validate_session_data(game_account, pkt.version, pkt.client_type) == false) {
			Send_AC_REFUSE_LOGIN(login_error_codes::ERR_SESSION_CONNECTED);
			AuthLog->info("Refused connection for account '{}', already online.", pkt.username);
			get_socket()->delayed_close_socket();
			if (AuthInterAPI->get_session_data(game_account->get_id()) != nullptr) {
				// @TODO Check if online in char-server & map-server.
				AuthInterAPI->delete_game_account(game_account->get_id());
				AuthInterAPI->delete_session(game_account->get_id());
			}
		} else {
			Send_AC_ACCEPT_LOGIN();
		}
	} else {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Rejected unknown account '{}' or incorrect password.", pkt.username);
	}
}

void Horizon::Auth::PacketHandler::Handle_CA_REQ_HASH(PacketBuffer &/*packet*/)
{
	PACKET_CA_REQ_HASH pkt;
}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN2(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN2 pkt;
}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN3(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN3 pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &/*packet*/)
{
	PACKET_CA_CONNECT_INFO_CHANGED pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_EXE_HASHCHECK(PacketBuffer &/*packet*/)
{
	PACKET_CA_EXE_HASHCHECK pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN_PCBANG(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_PCBANG pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN4(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN4 pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN_HAN(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_HAN pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_SSO_LOGIN_REQ(PacketBuffer &/*packet*/)
{
	PACKET_CA_SSO_LOGIN_REQ pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_OTP pkt;

}

/**
 * Auth To Client
 */
void Horizon::Auth::PacketHandler::Send_AC_ACCEPT_LOGIN()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<SessionData> session_data = get_socket()->get_session()->get_session_data();
	const CharacterServerMapType char_servers = AuthServer->get_character_servers();
	auto *pkt = new PACKET_AC_ACCEPT_LOGIN();
	PACKET_AC_ACCEPT_LOGIN::character_server_list *server_list;
	PacketBuffer buf;

	/**
	 * Reject if no character servers.
	 */
	if (char_servers.empty()) {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_REJECTED_FROM_SERVER);
		delete pkt;
		return;
	}

	server_list = new PACKET_AC_ACCEPT_LOGIN::character_server_list[char_servers.size()];

	pkt->packet_len = sizeof(*pkt) + (sizeof(struct PACKET_AC_ACCEPT_LOGIN::character_server_list) * char_servers.size());
	pkt->auth_code = session_data->get_auth_code();
	pkt->aid = game_account->get_id();
	pkt->user_level = 1;
	pkt->last_login_ip = 0; // not used anymore.
	memset(pkt->last_login_time, '\0', sizeof(pkt->last_login_time)); // Not used anymore

	pkt->sex = (uint8_t) game_account->get_gender();

	int i = 0;
	for (auto &chr : char_servers) {
		server_list[i].ip = inet_addr(chr.second->ip_address.c_str());
		server_list[i].port = chr.second->port;
		strncpy(server_list[i].name, chr.second->name.c_str(), sizeof(server_list[i].name));
		server_list[i].type = (uint16_t) chr.second->server_type;
		server_list[i].is_new = chr.second->is_new;
		server_list[i].usercount = 88;
		++i;
	}

	buf.append<PACKET_AC_ACCEPT_LOGIN, PACKET_AC_ACCEPT_LOGIN::character_server_list>
		(pkt, sizeof(*pkt), server_list, char_servers.size());

	send_packet(buf, (std::size_t) pkt->packet_len);

	delete[] server_list;
	delete pkt;
}

void Horizon::Auth::PacketHandler::Send_AC_REFUSE_LOGIN(login_error_codes error_code)
{
	PACKET_AC_REFUSE_LOGIN pkt;
	pkt.error_code = (uint8_t) error_code;
	send_packet(pkt);
}

void Horizon::Auth::PacketHandler::Send_SC_NOTIFY_BAN()
{

}

void Horizon::Auth::PacketHandler::Send_AC_ACK_HASH()
{

}

void Horizon::Auth::PacketHandler::Send_AC_REFUSE_LOGIN_R2()
{

}

void Horizon::Auth::PacketHandler::Send_CA_CHARSERVERCONNECT()
{

}
