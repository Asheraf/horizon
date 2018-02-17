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

#ifndef HORIZON_ZONE_INTERFACE_INTERAPI_HPP
#define HORIZON_ZONE_INTERFACE_INTERAPI_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Interfaces/InterServerAPI.hpp"
#include "Server/Zone/PacketHandler/InterPacketHandler.hpp"
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
#include "Server/Zone/Session/InterSession.hpp"

namespace Horizon
{
namespace Zone
{
namespace Interface
{
class InterAPI : public Horizon::Interface::InterServerAPI<InterSession>
{
public:
	InterAPI() : InterServerAPI(InterSocktMgr->getConnectedSession(INTER_SESSION_NAME)) {}
	~InterAPI() {}

	static InterAPI *getInstance()
	{
		static InterAPI inter_api;
		return &inter_api;
	}
};
}
}
}

#define ZoneInterAPI Horizon::Zone::Interface::InterAPI::getInstance()

#endif // HORIZON_ZONE_INTERFACE_INTERAPI_HPP

