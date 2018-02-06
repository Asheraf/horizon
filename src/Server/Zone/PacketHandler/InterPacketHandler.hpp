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

#ifndef HORIZON_ZONE_INTERPACKETHANDLER_HPP
#define HORIZON_ZONE_INTERPACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/InterPacketHandler.hpp"
#include <memory>

class SessionData;
class PacketBuffer;

namespace Horizon
{
namespace Zone
{
class InterSession;
class InterPacketHandler : public Horizon::Base::InterPacketHandler<InterSession>
{
public:
	InterPacketHandler(std::shared_ptr<InterSession> session);
	~InterPacketHandler();

	/* Initializer */
	void InitializeHandlers() override;
};
}
}

#endif //HORIZON_INTERPACKETHANDLER_HPP

