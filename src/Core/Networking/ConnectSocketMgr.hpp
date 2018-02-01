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

#ifndef HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP
#define HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP

#include "Core/Networking/SocketMgr.hpp"

namespace Horizon
{
namespace Networking
{
class Connector;
/**
 * @brief Socket manager that handles sockets that were created by the connector.
 */
template <class SocketType>
class ConnectSocketMgr : public SocketMgr<SocketType>
{
	typedef SocketMgr<SocketType> BaseSocketMgr;
	struct connector_pool_data
	{
		std::shared_ptr<Connector> connector;
		std::vector<std::shared_ptr<SocketType>> sessions;
	};
	typedef std::unordered_map<std::string, connector_pool_data>  NetworkConnectorPool;
public:
	ConnectSocketMgr() { }
	~ConnectSocketMgr() { }

	/**
	 * @brief Initialize and start connecting synchronously.
	 *        This method also starts the networking threads for connected sockets.
	 * @param[in|out] connection_name  const reference to the connection name string.
	 * @param[in|out] server           pointer to the server instance that issued the connection.
	 * @param[in|out] connect_ip       const reference to the ip_address string for the connection endpoint.
	 * @param[in]     port             port number for the connection endpoint.
	 * @param[in]     connections      number of connections to create and handle.
	 * @return true on success, false on failure.
	 */
	std::shared_ptr<Connector> Start(std::string const &connection_name, Server *server, std::string const &connect_ip, uint16_t port, uint32_t connections = 1)
	{
		std::shared_ptr<Connector> connector;

		if (!(connector = std::make_shared<Horizon::Networking::Connector>(connection_name, server, connect_ip, port))) {
			CoreLog->error("ConnectSocketMgr::Start '{}' failed to connect to tcp:://{}:{}.", connection_name, connect_ip, port);
			return nullptr;
		}

		if (!BaseSocketMgr::StartNetworkThreads(1)) {
			CoreLog->error("ConnectSocketMgr::Start failed to start network threads.");
			return nullptr;
		}

		// Add the connector to the session pool before anything.
		AddToConnectorPool(connection_name, connector);

		// Set the socket factory. & Start attempting to connect.
		connector->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForNewConnection, this));
		connector->ConnectWithCallback(
					boost::bind(&ConnectSocketMgr<SocketType>::OnSocketOpen,
						this, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3), connections);

		return connector;
	}

	/**
	 * @brief Stop the Connector network and clear the connection pool.
	 */
	void StopNetwork() override
	{
		SocketMgr<SocketType>::StopNetwork();
		_network_connector_pool.clear();
	}

	/**
	 * Add a connector to the connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 * @param[in|out] connector   reference to the shared pointer of type Connector.
	 */
	void AddToConnectorPool(std::string const &conn_name, std::shared_ptr<Connector> const &connector)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end()) {
			it->second.connector = std::move(connector);
		} else {
			struct connector_pool_data cpd;
			cpd.connector = std::move(connector);
			_network_connector_pool.insert(std::make_pair(conn_name, cpd));
		}
	}

	/**
	 * Add a connected session of a SocketType to the connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 * @param[in|out] session     reference to the shared pointer of SocketType.
	 */
	void AddSessionToConnectorPool(std::string const &conn_name, std::shared_ptr<SocketType> const &session)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end())
			it->second.sessions.push_back(session);
	}

	/**
	 * Get the size of the connection pool for a given connection.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 */
	std::size_t getConnectionPoolSize(std::string const &conn_name)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end())
			return it->second.sessions.size();

		return 0;
	}

	/**
	 * Get a random session from the list of connected sessions in a connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 */
	std::shared_ptr<SocketType> getConnectedSession(std::string const &conn_name)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end() && it->second.sessions.size() > 0) {
			int session_size = it->second.sessions.size() - 1;
			int rand_idx = session_size > 0 ? (rand() % session_size) : 0;

			return it->second.sessions.at(rand_idx);
		}

		return nullptr;
	}

	/**
	 * Remove a connected session of a SocketType from the connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 * @param[in|out] session     reference to the shared pointer of SocketType.
	 */
	void RemoveConnectedSession(std::string const &conn_name, std::shared_ptr<SocketType> const &session)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end()) {
			it->second.sessions.erase(std::remove(it->second.sessions.begin(), it->second.sessions.end(), session), it->second.sessions.end());
			CoreLog->info("SocketMgr::RemoveConnectedSession: successfully removed '{}' connected session ID - {}.", conn_name, session->getSocketId());
		}
	}

	/**
	 * @brief On Server Type Socket Open / Start Routine.
	 *        - Move the socket ownership from the caller to a new socket and add it to a thread.
	 * @param[in|out] conn_name      as the name of the connection.
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	virtual void OnSocketOpen(std::string const &conn_name, std::shared_ptr<tcp::socket> const &socket, uint32_t thread_index)
	{
		std::shared_ptr<SocketType> session = SocketMgr<SocketType>::OnSocketOpen(std::move(socket), thread_index);
		// Add socket to connector map.
		AddSessionToConnectorPool(conn_name, session);
	}

	/**
	 * @brief Routine called from an implemented socket when finalising / closing.
	 * @param[in|out] session pointer to the session that the socket belongs to.
	 */
	void ClearSession(std::string const &conn_name, std::shared_ptr<SocketType> session)
	{
		std::mutex clear_mtx;
		std::lock_guard<std::mutex> clearGuard(clear_mtx);

		RemoveConnectedSession(conn_name, session);
	}

private:
	NetworkConnectorPool _network_connector_pool;
};
}
}
#endif /* HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP */
