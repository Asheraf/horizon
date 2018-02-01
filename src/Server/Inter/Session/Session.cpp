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

#include "Server/Inter/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Inter/PacketHandler/PacketHandlerFactory.hpp"

#include "Core/Logging/Logger.hpp"
#include "Packets.hpp"

Horizon::Inter::Session::Session(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
	//
}

void Horizon::Inter::Session::Start()
{
	std::string ip_address = getRemoteIPAddress();

	InterLog->info("Established connection from {}.", ip_address);

	if (getPacketHandler() == nullptr) {
		setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this()));
		getPacketHandler()->Respond_INTER_CONNECT_INIT();
	}
	AsyncRead();
}

void Horizon::Inter::Session::OnClose()
{
	try {
		std::string ip_address = getRemoteIPAddress();
		InterLog->info("Closed connection from {}.", ip_address);
	} catch (boost::system::system_error &error) {
		InterLog->info("Closed a connected session abruptly. Error: {}", error.what());
	}

	/**
	 * @brief Perform socket manager cleanup.
	 */
	ClientSocktMgr->ClearSession(shared_from_this());
}

bool Horizon::Inter::Session::Update()
{
	return InterSocket::Update();
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Inter::Session::ReadHandler()
{
	while (GetReadBuffer().GetActiveSize()) {
		uint16_t op_code;
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, GetReadBuffer().GetReadPointer(), GetReadBuffer().GetActiveSize());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());

		if (getPacketHandler() == nullptr) {
			setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this()));
			getPacketHandler()->Respond_INTER_CONNECT_INIT();
		}

		if (!getPacketHandler()->HandleReceivedPacket(pkt))
			GetReadBuffer().Reset();
	}
}
