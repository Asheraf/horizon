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

#include "Server/Inter/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Inter/PacketHandler/PacketHandlerFactory.hpp"

#include "Core/Logging/Logger.hpp"
#include "Packets.hpp"

Horizon::Inter::Session::Session(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
	//
}

/**
 * @brief Start method invoked once from the network thread that the socket is in,
 *        on start of the socket connection.
 */
void Horizon::Inter::Session::start()
{
	std::string ip_address = getRemoteIPAddress();

	InterLog->info("Established connection from {}.", ip_address);

	if (getPacketHandler() == nullptr) {
		setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this()));
		getPacketHandler()->Send_INTER_CONNECT_INIT();
	}
	asyncRead();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Inter::Session::onClose()
{
	InterLog->info("Closed connection from {}.", getRemoteIPAddress());

	/* Perform socket manager cleanup. */
	ClientSocktMgr->ClearSession(shared_from_this());
}

/**
 * @brief Asynchronous update() method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Inter::Session::update()
{
	return InterSocket::update();
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Inter::Session::readHandler()
{
	while (getReadBuffer().GetActiveSize()) {
		uint16_t op_code;
		memcpy(&op_code, getReadBuffer().getReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, getReadBuffer().getReadPointer(), getReadBuffer().GetActiveSize());
		getReadBuffer().readCompleted(getReadBuffer().GetActiveSize());

		if (getPacketHandler() == nullptr) {
			setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this()));
			getPacketHandler()->Send_INTER_CONNECT_INIT();
		}

		if (!getPacketHandler()->HandleReceivedPacket(pkt))
			getReadBuffer().Reset();
	}
}
