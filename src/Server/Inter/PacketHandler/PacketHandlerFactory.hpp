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

#ifndef HORIZON_INTER_PACKETHANDLERFACTORY_HPP
#define HORIZON_INTER_PACKETHANDLERFACTORY_HPP

#include "PacketHandler.hpp"

namespace Horizon
{
namespace Inter
{
class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	static std::shared_ptr<PacketHandler> CreatePacketHandler(std::shared_ptr<Session> session)
	{
		return std::make_shared<PacketHandler>(session);
	}
};
}
}

#endif //HORIZON_INTER_PACKETHANDLERFACTORY_HPP
