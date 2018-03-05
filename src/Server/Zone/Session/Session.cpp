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

#include "Server/Common/Models/Character/Character.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Player/Player.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
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
void Horizon::Zone::Session::start()
{
	ZoneLog->info("Established connection from {}.", getRemoteIPAddress());

	asyncRead();
}

/**
 * @brief Socket cleanup method on connection closure.
 */
void Horizon::Zone::Session::onClose()
{
	ZoneLog->info("Closed connection from {}.", getRemoteIPAddress());

	/* Perform socket manager cleanup. */
	ClientSocktMgr->ClearSession(shared_from_this());
}

/**
 * @brief Asynchronous update method periodically called from network threads.
 * @thread NetworkThread
 * @return true on successful update, false on failure.
 */
bool Horizon::Zone::Session::update()
{
	std::shared_ptr<PacketBuffer> buf;

	while ((buf = _packet_queue.try_pop()))
		if (!getPacketHandler()->HandleReceivedPacket(*buf))
			getReadBuffer().Reset();

	return ZoneSocket::update();
}

/**
 * @brief Validate and handle the initial char-server connection (Packet CZ_ENTER)
 * @param[in] buf   Copied instance of the PacketBuffer.
 */
void Horizon::Zone::Session::handleNewConnection(PacketBuffer &buf)
{
	switch (buf.getOpCode())
	{
	case PacketVer20141022::CZ_ENTER:
	{
		setPacketHandler(PacketHandlerFactory::CreatePacketHandler(shared_from_this(), 20141022));
		break;
	}
	default:
		ZoneLog->info("New connection attempt from unknown client version. Packet Id: '{0:x}'.", buf.getOpCode());
	}
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Zone::Session::readHandler()
{
	while (getReadBuffer().GetActiveSize()) {
		uint16_t op_code = 0x0;
		memcpy(&op_code, getReadBuffer().getReadPointer(), sizeof(uint16_t));

		PacketBuffer buf(op_code, getReadBuffer().getReadPointer(), getReadBuffer().GetActiveSize());
		getReadBuffer().readCompleted(getReadBuffer().GetActiveSize());

		/**
		 * Devise a suitable packet handler
		 * based on the client's packet version.
		 */
		if (getPacketHandler() == nullptr)
			handleNewConnection(buf);

		if (getPacketHandler() == nullptr) {
			ZoneLog->error("Packet handler was null!");
			return;
		}

		_packet_queue.push(std::move(buf));
	}
}

/**
 * Packet Handler
 */
std::shared_ptr<Horizon::Zone::PacketHandler> Horizon::Zone::Session::getPacketHandler()
{
	return _packet_handler;
}

void Horizon::Zone::Session::setPacketHandler(std::shared_ptr<PacketHandler> handler)
{
	_packet_handler = handler;
}

/**
 * Character
 */
std::shared_ptr<Character> Horizon::Zone::Session::getCharacter()
{
	return _character;
}

void Horizon::Zone::Session::setCharacter(std::shared_ptr<Character> const &c)
{
	_character = c;
}

/**
 * Player
 */
std::shared_ptr<Player> Horizon::Zone::Session::getPlayer()
{
	return _player;
}

void Horizon::Zone::Session::setPlayer(std::shared_ptr<Player> const &p)
{
	_player = p;
}
