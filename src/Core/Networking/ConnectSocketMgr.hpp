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

#include "Core/Multithreading/LockedLookupTable.hpp"
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
	typedef LockedLookupTable<uint32_t, std::shared_ptr<SocketType>> SocketTableType;
	typedef LockedLookupTable<std::string, std::shared_ptr<SocketTableType>>  NetworkConnectorPool;
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
	std::shared_ptr<Connector> start(std::string const &connection_name, Server *server, std::string const &connect_ip, uint16_t port, uint32_t connections = 1)
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

		// Set the socket factory. & Start attempting to connect.
		connector->set_socket_factory(std::bind(&BaseSocketMgr::get_new_socket, this));
		connector->connect_with_callback(
					boost::bind(&ConnectSocketMgr<SocketType>::on_socket_open,
						this, boost::placeholders::_1, boost::placeholders::_2, boost::placeholders::_3), connections);

		return connector;
	}

	/**
	 * @brief Stop the Connector network and clear the connection pool.
	 */
	void stop_network() override
	{
		SocketMgr<SocketType>::stop_network();
	}

	/**
	 * Add a connected socket of a SocketType to the connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 * @param[in|out] socket     reference to the shared pointer of SocketType.
	 */
	void add_connector_pool_socket(std::string const &conn_name, std::shared_ptr<SocketType> const &socket)
	{
		std::shared_ptr<SocketTableType> socket_table = _network_connector_pool.at(conn_name);

		if (socket_table == nullptr) {
			socket_table = std::make_shared<SocketTableType>();
			_network_connector_pool.insert(conn_name, socket_table);
		}

		socket_table->insert(socket->get_socket_id(), socket);
	}

	/**
	 * Get the size of the connection pool for a given connection.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 */
	std::size_t connector_pool_size(std::string const &conn_name)
	{
		auto socket_table = _network_connector_pool.at(conn_name);

		if (socket_table != nullptr)
			return socket_table->size();

		return 0;
	}

	/**
	 * Get a random socket from the list of connected sockets in a connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 */
	std::shared_ptr<SocketType> get_connector_socket(std::string const &conn_name)
	{
		auto socket_table = _network_connector_pool.at(conn_name);

		if (socket_table != nullptr) {
			auto socket_map = socket_table->get_map();
			int size = socket_map.size();

			if (size > 0) {
				int rand_idx = (rand() % size);
				int idx = 0;

				for (auto sock : socket_map)
					if (idx++ == rand_idx)
						return sock.second;
			}
		}

		return nullptr;
	}

	/**
	 * Remove a connected socket of a SocketType from the connector pool.
	 * @param[in|out] conn_name   const reference to the connection name string.
	 * @param[in|out] socket     reference to the shared pointer of SocketType.
	 */
	void finalize_connector_socket(std::string const &conn_name, std::shared_ptr<SocketType> const &socket)
	{
		auto socket_table = _network_connector_pool.at(conn_name);

		if (socket_table != nullptr) {
			if (socket_table->at(socket->get_socket_id())) {
				socket_table->erase(socket->get_socket_id());
				CoreLog->info("SocketMgr::remove_connector_socket: successfully removed '{}' connected socket ID - {}.", conn_name, socket->get_socket_id());
			}
		}
	}

	/**
	 * @brief On Server Type Socket Open / Start Routine.
	 *        - Move the socket ownership from the caller to a new socket and add it to a thread.
	 * @param[in|out] conn_name      as the name of the connection.
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	virtual void on_socket_open(std::string const &conn_name, std::shared_ptr<tcp::socket> const &tcp_socket, uint32_t thread_index)
	{
		std::shared_ptr<SocketType> socket = SocketMgr<SocketType>::on_socket_open(std::move(tcp_socket), thread_index);
		// Add socket to connector map.
		add_connector_pool_socket(conn_name, socket);
	}

	void close_connection(std::string const &conn_name)
	{
		auto socket_table = _network_connector_pool.at(conn_name);

		if (socket_table != nullptr) {
			auto socket_map = socket_table->get_map();
			for (auto sock : socket_map)
				if (sock.second->is_open())
					sock.second->close_socket();
			
			_network_connector_pool.erase(conn_name);
		}
	}

private:
	NetworkConnectorPool _network_connector_pool;
};
}
}
#endif /* HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP */
