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

void Horizon::Char::Session::Start()
{
	CharLog->info("Established connection from {}.", getRemoteIPAddress());

	AsyncRead();
}

void Horizon::Char::Session::OnClose()
{
	CharLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	ClientSocktMgr->ClearSession(shared_from_this());
}

bool Horizon::Char::Session::Update()
{
	return CharSocket::Update();
}

/**
 * @brief Validate and handle the initial char-server connection (Packet CHAR_CONNECT)
 * @param[in] buf   Copied instance of the PacketBuffer.
 */
void Horizon::Char::Session::ValidateAndHandleConnection(PacketBuffer &buf)
{
	PACKET_CHAR_CONNECT pkt;

	buf >> pkt;

	// Set a default packet handler through the scope of this request.
	// We reset it towards the end of this request, once we have the packet version.
	setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this(), 0));

	// Refuse if inter-server is not connected.
	if (!InterSocktMgr->getConnectionPoolSize(INTER_SESSION_NAME)) {
		CharLog->info("Rejected connection for account {}, inter-server unavailable.", pkt.account_id);
		getPacketHandler()->Respond_CHAR_CONNECT_ERROR(CHAR_ERR_REJECTED_FROM_SERVER);
		return;
	}

	// Attempt retrieval of session_data from the inter server.
	setSessionData(CharInterAPI->GetSessionFromInter(pkt.auth_code));

	// No session was found, reject!
	if (getSessionData() == nullptr) {
		getPacketHandler()->Respond_CHAR_CONNECT_ERROR(CHAR_ERR_REJECTED_FROM_SERVER);
		return;
	}

	// Create a packet handler for this session.
	setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this(), getSessionData()->getClientVersion()));
	getPacketHandler()->Handle_CHAR_CONNECT(pkt);
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Char::Session::ReadHandler()
{
	while (GetReadBuffer().GetActiveSize()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer buf(op_code, GetReadBuffer().GetReadPointer(), GetReadBuffer().GetActiveSize());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());

		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (op_code == CHAR_CONNECT) {
			ValidateAndHandleConnection(buf);
			return;
		}

		if (getPacketHandler() == nullptr) {
			CharLog->error("Packet handler was null!");
			return;
		}

		if (!getPacketHandler()->HandleReceivedPacket(buf))
			GetReadBuffer().Reset();
	}
}


const std::shared_ptr<Horizon::Char::PacketHandler> &Horizon::Char::Session::getPacketHandler() const
{
	return _packet_handler;
}

void Horizon::Char::Session::setPacketHandler(std::shared_ptr<PacketHandler> handler)
{
	_packet_handler = handler;
}
