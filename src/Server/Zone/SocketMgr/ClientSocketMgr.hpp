/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#ifndef HORIZON_ZONE_ZONESOCKETMGR_HPP
#define HORIZON_ZONE_ZONESOCKETMGR_HPP

#include "Core/Networking/AcceptSocketMgr.hpp"
#include "Server/Zone/Session/Session.hpp"

namespace Horizon
{
namespace Zone
{
/**
 * @brief Singleton class
 */
class ClientSocketMgr : public Horizon::Networking::AcceptSocketMgr<Session>
{
	typedef Horizon::Networking::AcceptSocketMgr<Session> BaseSocketMgr;
public:
	static ClientSocketMgr *getInstance()
	{
		static ClientSocketMgr instance;
		return &instance;
	}

	bool Start(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads = 1)
	{
		if (!BaseSocketMgr::Start(io_service, listen_ip, port, threads))
			return false;

		return true;
	}
};
}
}

#define ClientSocktMgr Horizon::Zone::ClientSocketMgr::getInstance()

#endif //HORIZON_ZONE_ZONESOCKETMGR_HPP
