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

#include "Server/Char/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/GameAccount.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Char.hpp"

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
 * @brief Validate and handle the initial char-server connection (Packet CH_CONNECT)
 * @param[in] buf Copied instance of the PacketBuffer.
 */
void CharSession::handle_new_connection(PacketBuffer &buf)
{
	PACKET_CH_CONNECT pkt;

	buf >> pkt;

	// Set a default packet handler through the scope of this request.
	// We reset it towards the end of this request, once we have the packet version.
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), 0));

	std::shared_ptr<SessionData> session_data = std::make_shared<SessionData>();
	if (!session_data->load(CharServer, pkt.account_id)) {
		get_packet_handler()->Send_HC_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		get_socket()->delayed_close_socket();
		return;
	}

	std::shared_ptr<GameAccount> game_account = std::make_shared<GameAccount>();
	if (!game_account->load(CharServer, pkt.account_id)) {
		get_packet_handler()->Send_HC_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		get_socket()->delayed_close_socket();
		return;
	}

	set_session_data(session_data);
	set_game_account(game_account);

	// Create a packet handler for this session.
	set_packet_handler(PacketHandlerFactory::create_packet_handler(get_socket(), _session_data->get_client_version()));
	get_packet_handler()->Handle_CH_CONNECT(pkt);
}

void CharSession::update(uint32_t /*diff*/)
{
	std::shared_ptr<PacketBuffer> buf;

	if (_packet_handler != nullptr && _packet_handler->session_has_expired()) {
		get_socket()->close_socket();
		return;
	}

	while ((buf = get_socket()->get_packet_recv_queue().try_pop())) {
		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (buf->getOpCode() == CH_CONNECT) {
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

