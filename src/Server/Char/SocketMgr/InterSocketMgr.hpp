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

#ifndef HORIZON_CHAR_INTERSOCKETMGR_HPP
#define HORIZON_CHAR_INTERSOCKETMGR_HPP

#include "Core/Networking/ConnectSocketMgr.hpp"
#include "Server/Char/Socket/InterSocket.hpp"

namespace Horizon
{
namespace Char
{
/**
 * @brief Singleton class.
 */
class InterSocketMgr : public Horizon::Networking::ConnectSocketMgr<InterSocket>
{
	typedef Horizon::Networking::ConnectSocketMgr<InterSocket> BaseSocketMgr;
public:
	static InterSocketMgr *getInstance()
	{
		static InterSocketMgr instance;
		return &instance;
	}

	bool start(std::string const &connection_name, Server *server, std::string const &connect_ip, uint16_t port, uint32_t connections = 1)
	{
		if (BaseSocketMgr::start(connection_name, server, connect_ip, port, connections) == nullptr)
			return false;

		return true;
	}
};
}
}

#define InterSocktMgr Horizon::Char::InterSocketMgr::getInstance()

#endif /* HORIZON_CHAR_INTERSOCKETMGR_HPP */

