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

#ifndef HORIZON_CHAR_INTERFACE_INTERAPI_HPP
#define HORIZON_CHAR_INTERFACE_INTERAPI_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Interfaces/InterServerAPI.hpp"
#include "Server/Char/Session/InterSession.hpp"

namespace Horizon
{
namespace Char
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

#define CharInterAPI Horizon::Char::Interface::InterAPI::getInstance()

#endif // HORIZON_CHAR_INTERFACE_INTERQUERY_HPP
