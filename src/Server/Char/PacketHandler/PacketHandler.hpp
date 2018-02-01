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

#ifndef HORIZON_PACKETHANDLER_HPP
#define HORIZON_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"

#include <memory>

class PacketBuffer;
class SessionData;

namespace Horizon
{
namespace Char
{
class Session;
class PacketHandler : public Horizon::Base::PacketHandler<Session>
{
public:
	explicit PacketHandler(std::shared_ptr<Session> session);
	virtual ~PacketHandler();

	virtual void InitializeHandlers();
	/**
	 * Handlers
	 */
	virtual void Handle_CHAR_CONNECT(PACKET_CHAR_CONNECT &pkt);
	virtual void Handle_CHAR_KEEP_ALIVE(PacketBuffer &buf);
	/**
	 * Responders
	 */
	virtual void Respond_CHAR_CONNECT_ERROR(character_connect_errors error);
	virtual void Respond_CHAR_ACCOUNT_ID();
	virtual void Respond_CHAR_SLOT_INFO_ACK();
	virtual void Respond_CHAR_LIST_ACK();
	virtual void Respond_CHAR_BAN_LIST_ACK();
	virtual void Respond_CHAR_PINCODE_STATE_ACK();
};
}
}

#endif //HORIZON_PACKETHANDLER_HPP
