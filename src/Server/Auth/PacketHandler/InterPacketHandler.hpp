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

#ifndef HORIZON_AUTH_INTERPACKETHANDLER_HPP
#define HORIZON_AUTH_INTERPACKETHANDLER_HPP

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Base/PacketHandler/InterPacketHandler.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"

class PacketBuffer;

namespace Horizon
{
namespace Auth
{
class InterSocket;
class InterPacketHandler : public Horizon::Base::InterPacketHandler<InterSocket>
{
public:
	InterPacketHandler(std::shared_ptr<InterSocket> session);
	~InterPacketHandler();

	void initialize_handlers() override;
};
}
}

#endif //HORIZON_AUTH_INTERPACKETHANDLER_HPP
