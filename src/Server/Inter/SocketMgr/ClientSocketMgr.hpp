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

#ifndef HORIZON_INTER_INTERSOCKETMGR_H
#define HORIZON_INTER_INTERSOCKETMGR_H

#include "Core/Networking/AcceptSocketMgr.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"

namespace Horizon
{
namespace Inter
{
class Session;
/**
 * Auth Accept Socket Manager for clients.
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

#define ClientSocktMgr Horizon::Inter::ClientSocketMgr::getInstance()


#endif //HORIZON_INTERSOCKETMGR_H
