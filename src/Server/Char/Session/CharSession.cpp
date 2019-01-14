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

#include "CharSession.hpp"

#include "Server/Char/Interface/InterAPI.hpp"
#include "Server/Char/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/SocketMgr/InterSocketMgr.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"

using namespace Horizon::Char;

CharSession::CharSession(std::shared_ptr<CharSocket> socket)
: Horizon::Networking::Session<CharSocket>(socket)
{
	//
}

CharSession::~CharSession()
{
	//
}

/* Packet Handler */
std::shared_ptr<PacketHandler> CharSession::get_packet_handler() { return _packet_handler; }
void CharSession::set_packet_handler(std::shared_ptr<PacketHandler> handler) { _packet_handler.swap(handler); }
/* Character */
std::shared_ptr<Character> CharSession::get_character() { return _character; }
void CharSession::set_character(std::shared_ptr<Character> character) { _character.swap(character); }
/* Game Account */
std::shared_ptr<GameAccount> CharSession::get_game_account() { return _game_account; }
void CharSession::set_game_account(std::shared_ptr<GameAccount> account) { _game_account.swap(account); }
/* Session Data */
std::shared_ptr<SessionData> CharSession::get_session_data() { return _session_data; }
void CharSession::set_session_data(std::shared_ptr<SessionData> session_data) { _session_data.swap(session_data); }

/**
 * @brief Validate and handle the initial char-server connection (Packet CHAR_CONNECT)
 * @param[in] buf Copied instance of the PacketBuffer.
 */
void CharSession::handle_new_connection(PacketBuffer &buf)
{
	PACKET_CHAR_CONNECT pkt;

	buf >> pkt;

	// Set a default packet handler through the scope of this request.
	// We reset it towards the end of this request, once we have the packet version.
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), 0));

	// Refuse if inter-server is not connected.
	if (!InterSocktMgr->connector_pool_size(INTER_SESSION_NAME)) {
		CharLog->info("Rejected connection for account {}, inter-server unavailable.", pkt.account_id);
		get_packet_handler()->Send_CHAR_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		get_socket()->delayed_close_socket();
		return;
	}

	// Attempt retrieval of session_data from the inter server.
	set_session_data(CharInterAPI->get_session_data(pkt.auth_code));

	// Game Account
	set_game_account(CharInterAPI->get_game_account(pkt.account_id));

	// No session was found, reject!
	if (_session_data == nullptr || _game_account == nullptr) {
		get_packet_handler()->Send_CHAR_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		get_socket()->delayed_close_socket();
		return;
	}

	// Create a packet handler for this session.
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), _session_data->get_client_version()));
	get_packet_handler()->Handle_CHAR_CONNECT(pkt);
}

void CharSession::update(uint32_t diff)
{
	std::shared_ptr<PacketBuffer> buf;

	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (buf->getOpCode() == CHAR_CONNECT) {
			handle_new_connection(*buf);
			return;
		}

		if (_packet_handler == nullptr) {
			CharLog->error("Packet handler was null!");
			return;
		}

		_packet_handler->handle_received_packet(*buf);
	}
}

