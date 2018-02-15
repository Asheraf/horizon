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

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
#include "Server/Zone/Interface/InterAPI.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Zone/PacketHandler/PacketHandler.hpp"
#include "Server/Zone/PacketHandler/InterPacketHandler.hpp"
#include "Server/Zone/PacketHandler/Versions/PacketHandler20141022.hpp"

Horizon::Zone::Session::Session(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void Horizon::Zone::Session::Start()
{
	ZoneLog->info("Established connection from {}.", getRemoteIPAddress());

	AsyncRead();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Zone::Session::OnClose()
{
	ZoneLog->info("Closed connection from {}.", getRemoteIPAddress());

	/* Perform socket manager cleanup. */
	ClientSocktMgr->ClearSession(shared_from_this());
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Zone::Session::Update()
{
	return ZoneSocket::Update();
}

/**
 * @brief Validate and handle the initial char-server connection (Packet CZ_ENTER)
 * @param[in] buf   Copied instance of the PacketBuffer.
 */
void Horizon::Zone::Session::ValidateAndHandleConnection(PacketBuffer &buf)
{
	uint32_t account_id, char_id, auth_code;

	switch (buf.getOpCode())
	{
	case PacketVer20141022::CZ_ENTER:
	{
		PacketVer20141022::PACKET_CZ_ENTER pkt;
		buf >> pkt;
		account_id = pkt.account_id;
		char_id = pkt.char_id;
		auth_code = pkt.auth_code;
		setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this(), 20141022));
		break;
	}
	default:
		ZoneLog->info("New connection attempt from unknown client version. Packet Id: '{0:x}'.", buf.getOpCode());
		return;
	}

	setSessionData(ZoneInterAPI->GetSessionFromInter(auth_code));
	if (getSessionData() == nullptr) {
		ZoneLog->info("New connection attempt from unauthorized session '{}'.", auth_code);
		getPacketHandler()->Respond_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	setGameAccount(ZoneInterAPI->GetGameAccountFromInter(account_id));
	if (getGameAccount() == nullptr) {
		ZoneLog->info("New connection attempt from unknown account '{}'.", account_id);
		getPacketHandler()->Respond_ZC_ERROR(ZONE_SERV_ERROR_REJECT);
		return;
	}

	getPacketHandler()->Respond_ZC_ACCOUNT_ID();
	getPacketHandler()->Respond_ZC_ACCEPT_CONNECTION();
	//getPacketHandler()->Respond_ZC_NPCACK_MAPMOVE("prontera", 101, 120);
	ZoneLog->info("New connection established for account '{}' using version '{}' from '{}'.",
				  account_id, getSessionData()->getClientVersion(), getRemoteIPAddress());
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Zone::Session::ReadHandler()
{
	while (GetReadBuffer().GetActiveSize()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer buf(op_code, GetReadBuffer().GetReadPointer(), GetReadBuffer().GetActiveSize());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());

		/**
		 * Devise a suitable packet handler
		 * based on the client's packet version.
		 * (CZ_ENTER) is handled separately.
		 */
		if (getPacketHandler() == nullptr) {
			ValidateAndHandleConnection(buf);
			return;
		}

		if (getPacketHandler() == nullptr) {
			ZoneLog->error("Packet handler was null!");
			return;
		}

		if (!getPacketHandler()->HandleReceivedPacket(buf))
			GetReadBuffer().Reset();
	}
}


const std::shared_ptr<Horizon::Zone::PacketHandler> &Horizon::Zone::Session::getPacketHandler() const
{
	return _packet_handler;
}

void Horizon::Zone::Session::setPacketHandler(std::shared_ptr<PacketHandler> handler)
{
	_packet_handler = handler;
}
