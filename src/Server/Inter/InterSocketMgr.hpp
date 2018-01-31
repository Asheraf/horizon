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

#include "Core/Networking/SocketMgr.hpp"

namespace Horizon
{
namespace Inter
{
/**
 * Auth Socket Manager
 * @brief Singleton class
 */
class InterSocketMgr : public SocketMgr<InterSession>
{
	typedef SocketMgr<InterSession> BaseSocketMgr;

public:
	static InterSocketMgr &Instance()
	{
		static InterSocketMgr instance;
		return instance;
	}

	bool StartNetwork(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads = 1) override
	{
		if (!BaseSocketMgr::StartNetwork(io_service, listen_ip, port, threads)) {
			CoreLog->error("InterSocketMgr failed to start network.");
			return false;
		}

		CoreLog->trace("Max allowed socket connections {}", (int) boost::asio::socket_base::max_connections);

		_acceptor->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForAccept, this));
		_acceptor->AsyncAcceptWithCallback<&InterSocketMgr::OnSocketAccept>();

		CoreLog->info("Networking initialized, listening on {} {} (Maximum Threads: {})", listen_ip, port, threads);

		return true;
	}

	bool StartNetworkConnection(std::string const &connection_name, Server *server, std::string const &connect_ip, uint16_t port, uint32_t connections = 1)
	{
		std::shared_ptr<NetworkConnector> connector;

		if (!(connector = std::make_shared<NetworkConnector>(connection_name, server, connect_ip, port))) {
			CoreLog->error("SocketMgr.StartConnect '{}' to tcp:://{}:{}.", connection_name, connect_ip, port);
			return false;
		}
		// Add the connector to the session pool before anything.
		this->AddToConnectorPool(connection_name, connector);
		// Set the socket factory. & Start attempting to connect.
		connector->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForConnect, this));
		connector->ConnectWithCallback<&InterSocketMgr::OnSocketConnect>(connections);
		return true;
	}

protected:
	static void OnSocketAccept(std::shared_ptr<tcp::socket> socket, uint32_t threadIndex)
	{
		Instance().OnSocketOpenForAccept(std::forward<std::shared_ptr<tcp::socket>>(socket), threadIndex, SOCKET_ENDPOINT_TYPE_CLIENT);
	}

	static void OnSocketConnect(std::string &conn_name, std::shared_ptr<tcp::socket> socket, uint32_t threadIndex)
	{
		Instance().OnSocketOpenForConnect(conn_name, std::forward<std::shared_ptr<tcp::socket>>(socket), threadIndex, SOCKET_ENDPOINT_TYPE_SERVER);
	}
};
}
}

#define sInterSocketMgr Horizon::Inter::InterSocketMgr::Instance()

#endif //HORIZON_INTERSOCKETMGR_H
