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

#include "PacketHandler.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Packets/Ragexe/PacketStructs.hpp"
#include "Server/Auth/Packets/Ragexe/Packets.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Common/Models/Character/Group.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"

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
#define HANDLER_FUNC(packet) add_packet_handler(Ragexe::packet, boost::bind(&PacketHandler::Handle_ ## packet, this, boost::placeholders::_1))
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

	// Game Account Data.
	game_account->set_last_ip(get_socket()->remote_ip_address());
	game_account->set_last_login((int) time(nullptr));
	game_account->update(AuthServer);
	
	// Session Data.
	session_data->set_auth_code(game_account->get_id()); // @TODO Change to something unique to prevent session hijaking.
	session_data->set_game_account_id(game_account->get_id());
	session_data->set_client_version(client_version);
	session_data->set_client_type(client_type);
	session_data->set_character_slots(game_account->get_character_slots());
	session_data->set_group_id(game_account->get_group_id());

	session_data->save(AuthServer);

	get_socket()->get_session()->set_session_data(session_data);

	return true;
}

bool Horizon::Auth::PacketHandler::process_login(std::string username, std::string password, uint32_t client_type, uint32_t client_version)
{
	bool authenticated = false;
	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();

	AuthLog->info("Authentication of account '{}' requested. (Client Version: {}, Type: {})", username, client_version, client_type);

	switch (AuthServer->get_auth_config().get_pass_hash_method())
	{
		case PASS_HASH_NONE:
		case PASS_HASH_MD5:
			authenticated = game_account->verify_credentials(AuthServer, username, password);
			break;
		case PASS_HASH_SCRYPT:
			authenticated = game_account->verify_credentials_scrypt(AuthServer, username, password);
			break;
	}

	if (authenticated) {
		get_socket()->get_session()->set_game_account(game_account);

		AuthLog->info("Authentication of account '{}' granted.", username);

		validate_session_data(game_account, client_version, client_type);
		Send_AC_ACCEPT_LOGIN();
	} else {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Rejected unknown account '{}' or incorrect password.", username);
		return false;
	}

	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN pkt;

	pkt << buf;

	return process_login(pkt.username, pkt.password, pkt.client_type, pkt.version);
}

bool Horizon::Auth::PacketHandler::Handle_CA_REQ_HASH(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_REQ_HASH pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN2(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN2 pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN3(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN3 pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_CONNECT_INFO_CHANGED pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_EXE_HASHCHECK(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_EXE_HASHCHECK pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN_PCBANG(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN_PCBANG pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN4(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN4 pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN_HAN(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN_HAN pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_SSO_LOGIN_REQ(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_SSO_LOGIN_REQ pkt;
	pkt << buf;
	return true;
}

bool Horizon::Auth::PacketHandler::Handle_CA_LOGIN_OTP(PacketBuffer &buf)
{
	Ragexe::PACKET_CA_LOGIN_OTP pkt;
	pkt << buf;
	return true;
}

/**
 * Auth To Client
 */
void Horizon::Auth::PacketHandler::Send_AC_ACCEPT_LOGIN()
{
	std::shared_ptr<GameAccount> game_account = get_socket()->get_session()->get_game_account();
	std::shared_ptr<SessionData> session_data = get_socket()->get_session()->get_session_data();
	const CharacterServerMapType char_servers = AuthServer->get_character_servers();
	Ragexe::PACKET_AC_ACCEPT_LOGIN pkt;
	Ragexe::PACKET_AC_ACCEPT_LOGIN::character_server_list *server_list = nullptr;

	/**
	 * Reject if no character servers.
	 */
	if (char_servers.empty()) {
		Send_AC_REFUSE_LOGIN(login_error_codes::ERR_REJECTED_FROM_SERVER);
		return;
	}

	server_list = new Ragexe::PACKET_AC_ACCEPT_LOGIN::character_server_list[char_servers.size()];

	pkt.packet_len = sizeof(pkt) + (sizeof(*server_list));
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

void Horizon::Auth::PacketHandler::Send_AC_REFUSE_LOGIN(login_error_codes error_code)
{
	Ragexe::PACKET_AC_REFUSE_LOGIN pkt;
	pkt.error_code = (uint8_t) error_code;
	send_packet(pkt.serialize());
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
