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

#ifndef HORIZON_ZONE_PACKETHANDLER_HPP
#define HORIZON_ZONE_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"

#include <memory>

class PacketBuffer;
class SessionData;

namespace Horizon
{
namespace Zone
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
	/**
	 * Responders
	 */
};
}
}

#endif //HORIZON_PACKETHANDLER_HPP

