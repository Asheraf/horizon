/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#include "Session.hpp"

#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
#include "Server/Zone/Interface/InterAPI.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Zone/PacketHandler/PacketHandler.hpp"
#include "Server/Zone/PacketHandler/InterPacketHandler.hpp"
#include "Server/Common/PacketBuffer.hpp"

Horizon::Zone::Session::Session(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

void Horizon::Zone::Session::Start()
{
	ZoneLog->info("Established connection from {}.", getRemoteIPAddress());

	AsyncRead();
}

void Horizon::Zone::Session::OnClose()
{
	ZoneLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	ClientSocktMgr->ClearSession(shared_from_this());
}

bool Horizon::Zone::Session::Update()
{
	return ZoneSocket::Update();
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
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		// @TODO

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
