/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP
#define HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP

#include "Core/Networking/SocketMgr.hpp"

#include <shared_mutex>

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
	typedef std::map<std::string, std::shared_ptr<SocketType>> ConnectionMap;
	typedef SocketMgr<SocketType> BaseSocketMgr;
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
					std::bind(&ConnectSocketMgr<SocketType>::on_socket_open,
						this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3), connections);

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
	 * @brief On Server Type Socket Open / Start Routine.
	 *        - Move the socket ownership from the caller to a new socket and add it to a thread.
	 * @param[in] conn_name      as the name of the connection.
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	void on_socket_open(std::string const &conn_name, std::shared_ptr<tcp::socket> const &tcp_socket, uint32_t thread_index)
	{
		std::shared_ptr<SocketType> socket = SocketMgr<SocketType>::on_socket_open(std::move(tcp_socket), thread_index);
		add_socket_to_connections(conn_name, socket);
	}

	void add_socket_to_connections(std::string const &conn_name, std::shared_ptr<SocketType> sock)
	{
		std::unique_lock<std::shared_mutex> _connection_map_mtx;

		_connection_map.emplace(conn_name, sock);
	}

	std::shared_ptr<SocketType> get_socket_from_connections(std::string const &conn_name)
	{
		std::shared_lock<std::shared_mutex> _connection_map_mtx;

		try {
			return _connection_map.at(conn_name);
		} catch (std::out_of_range &e) {
			return std::shared_ptr<SocketType>();
		}
	}

	void remove_socket_from_connections(std::string const &conn_name)
	{
		std::unique_lock<std::shared_mutex> _connection_map_mtx;

		auto socket = _connection_map.find(conn_name);

		if (socket != _connection_map.end())
			socket->second->delayed_close_socket();

		_connection_map.erase(conn_name);
	}


private:
	std::shared_mutex _connection_map_mtx;
	ConnectionMap _connection_map;
};
}
}
#endif /* HORIZON_NETWORKING_CONNECTSOCKETMGR_HPP */
