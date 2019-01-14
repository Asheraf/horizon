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

#ifndef HORIZON_INTER_PACKETHANDLER_HPP
#define HORIZON_INTER_PACKETHANDLER_HPP

#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"

#include <cstdint>
#include <memory>

class PacketBuffer;

namespace Horizon
{
namespace Inter
{
class InterSocket;
class PacketHandler : public Horizon::Base::PacketHandler<InterSocket>
{
public:
	PacketHandler(std::shared_ptr<InterSocket> socket);
	~PacketHandler();

	virtual void initialize_handlers() override;
	
	/**
	 * Handlers
	 */
	void Handle_INTER_CONNECT_AUTH(PacketBuffer &buf);
	// Session
	void Handle_INTER_SESSION_SET(PacketBuffer &buf);
	void Handle_INTER_SESSION_DEL(PacketBuffer &buf);
	void Handle_INTER_SESSION_REQ(PacketBuffer &buf);
	// Game Account
	void Handle_INTER_GAME_ACCOUNT_SET(PacketBuffer &buf);
	void Handle_INTER_GAME_ACCOUNT_DEL(PacketBuffer &buf);
	void Handle_INTER_GAME_ACCOUNT_REQ(PacketBuffer &buf);
	void Handle_INTER_PING(PacketBuffer &buf);
	/**
	 * Response
	 */
	void Send_INTER_ACK_RECEIVED(uint16_t packet_id, uint8_t response);
	void Send_INTER_CONNECT_INIT();
	void Send_INTER_PONG();
};
}
}

#endif //HORIZON_INTER_PACKETHANDLER_HPP
