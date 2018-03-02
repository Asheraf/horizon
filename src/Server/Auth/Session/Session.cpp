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

#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Auth/PacketHandler/PacketHandlerFactory.hpp"
#include "Server/Auth/PacketHandler/PacketHandler.hpp"

#include <random>

Horizon::Auth::Session::Session(std::shared_ptr<tcp::socket> socket)
: Socket(socket)
{
}

/**
 * @brief Initial method invoked once from the network thread that handles the session.
 */
void Horizon::Auth::Session::start()
{
	std::string ip_address = getRemoteIPAddress();

	AuthLog->info("Established connection from {}.", ip_address);

	asyncRead();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Auth::Session::onClose()
{

	AuthLog->info("Closed connection from {}.", getRemoteIPAddress());

	/**
	 * @brief Perform socket manager cleanup.
	 */
	ClientSocktMgr->ClearSession(shared_from_this());
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @return true on successful update, false on failure.
 */
bool Horizon::Auth::Session::update()
{
	std::shared_ptr<PacketBuffer> buf;
	while ((buf = _packet_queue.try_pop()))
		if (!getPacketHandler()->HandleReceivedPacket(*buf))
			getReadBuffer().Reset();

	return AuthSocket::update();
}

int Horizon::Auth::Session::GetPacketVersion(uint16_t op_code, PacketBuffer buf)
{
	int packet_ver = 0;

	switch (op_code)
	{
	case CA_LOGIN:
	{
		PACKET_CA_LOGIN pkt;
		buf >> pkt;
		packet_ver = pkt.version;
	}
		break;
	default:
		return 0;
	}

	return packet_ver;
}

void Horizon::Auth::Session::readHandler()
{
	while (getReadBuffer().GetActiveSize()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, getReadBuffer().getReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, getReadBuffer().getReadPointer(), getReadBuffer().GetActiveSize());
		getReadBuffer().readCompleted(getReadBuffer().GetActiveSize());

		/**
		 * Devise the a suitable packet handler
		 * based on the client's packet version.
		 */
		if (op_code == CA_LOGIN) {
			int packet_ver = GetPacketVersion(op_code, pkt);
			setPacketHandler(PacketHandlerFactory::CreateAuthPacketHandler(shared_from_this(), packet_ver));
		}

		if (getPacketHandler() == nullptr) {
			AuthLog->error("Packet handler was null!");
			return;
		}

		_packet_queue.push(std::move(pkt));
	}
}

std::shared_ptr<Horizon::Auth::PacketHandler> Horizon::Auth::Session::getPacketHandler()
{
	return _packet_handler;
}

void Horizon::Auth::Session::setPacketHandler(std::shared_ptr<PacketHandler> handler)
{
	_packet_handler = handler;
}
