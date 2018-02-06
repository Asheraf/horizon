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

#ifndef HORIZON_ZONE_INTERSOCKETMGR_HPP
#define HORIZON_ZONE_INTERSOCKETMGR_HPP

#include "Core/Networking/ConnectSocketMgr.hpp"
#include "Server/Zone/Session/InterSession.hpp"

namespace Horizon
{
namespace Zone
{
/**
 * @brief Singleton class.
 */
class InterSocketMgr : public Horizon::Networking::ConnectSocketMgr<InterSession>
{
	typedef Horizon::Networking::ConnectSocketMgr<InterSession> BaseSocketMgr;
public:
	static InterSocketMgr *getInstance()
	{
		static InterSocketMgr instance;
		return &instance;
	}

	bool Start(std::string const &connection_name, Server *server, std::string const &connect_ip, uint16_t port, uint32_t connections = 1)
	{
		if (BaseSocketMgr::Start(connection_name, server, connect_ip, port, connections) == nullptr)
			return false;

		return true;
	}
};
}
}

#define InterSocktMgr Horizon::Zone::InterSocketMgr::getInstance()

#endif /* HORIZON_ZONE_INTERSOCKETMGR_HPP */
