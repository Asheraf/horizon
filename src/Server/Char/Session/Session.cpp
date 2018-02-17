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

#include "Session.hpp"

#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Char/SocketMgr/InterSocketMgr.hpp"
#include "Server/Char/Interface/InterAPI.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"
#include "Server/Char/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Char/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/InterPacketHandler.hpp"
#include "Server/Common/PacketBuffer.hpp"

Horizon::Char::Session::Session(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
}

Horizon::Char::Session::~Session()
{
}

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void Horizon::Char::Session::start()
{
	CharLog->info("Established connection from {}.", getRemoteIPAddress());

	asyncRead();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Char::Session::onClose()
{
	CharLog->info("Closed connection from {}.", getRemoteIPAddress());

	/* Perform socket manager cleanup. */
	ClientSocktMgr->ClearSession(shared_from_this());
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Char::Session::update()
{
	return CharSocket::update();
}

/**
 * @brief Validate and handle the initial char-server connection (Packet CHAR_CONNECT)
 * @param[in] buf   Copied instance of the PacketBuffer.
 */
void Horizon::Char::Session::validateAndHandleConnection(PacketBuffer &buf)
{
	PACKET_CHAR_CONNECT pkt;

	buf >> pkt;

	// Set a default packet handler through the scope of this request.
	// We reset it towards the end of this request, once we have the packet version.
	setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this(), 0));

	// Refuse if inter-server is not connected.
	if (!InterSocktMgr->getConnectionPoolSize(INTER_SESSION_NAME)) {
		CharLog->info("Rejected connection for account {}, inter-server unavailable.", pkt.account_id);
		getPacketHandler()->Send_CHAR_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		delayedCloseSocket();
		return;
	}

	// Attempt retrieval of session_data from the inter server.
	setSessionData(CharInterAPI->GetSessionFromInter(pkt.auth_code));

	// Game Account
	setGameAccount(CharInterAPI->GetGameAccountFromInter(pkt.account_id));

	// No session was found, reject!
	if (getSessionData() == nullptr || getGameAccount() == nullptr) {
		getPacketHandler()->Send_CHAR_CONNECT_ERROR(character_connect_errors::CHAR_ERR_REJECTED_FROM_SERVER);
		delayedCloseSocket();
		return;
	}

	// Create a packet handler for this session.
	setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this(), getSessionData()->getClientVersion()));
	getPacketHandler()->Handle_CHAR_CONNECT(pkt);
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Char::Session::readHandler()
{
	while (getReadBuffer().GetActiveSize()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, getReadBuffer().getReadPointer(), sizeof(uint16_t));

		PacketBuffer buf(op_code, getReadBuffer().getReadPointer(), getReadBuffer().GetActiveSize());
		getReadBuffer().readCompleted(getReadBuffer().GetActiveSize());

		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (op_code == CHAR_CONNECT) {
			validateAndHandleConnection(buf);
			return;
		}

		if (getPacketHandler() == nullptr) {
			CharLog->error("Packet handler was null!");
			return;
		}

		if (!getPacketHandler()->HandleReceivedPacket(buf))
			getReadBuffer().Reset();
	}
}


std::shared_ptr<Horizon::Char::PacketHandler> Horizon::Char::Session::getPacketHandler()
{
	return _packet_handler;
}

void Horizon::Char::Session::setPacketHandler(std::shared_ptr<PacketHandler> handler)
{
	_packet_handler = handler;
}
