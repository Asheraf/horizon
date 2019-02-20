/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
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

#ifndef HORIZON_NETWORKING_CONNECTOR_HPP
#define HORIZON_NETWORKING_CONNECTOR_HPP

#include "Core/Logging/Logger.hpp"
#include "Server/Common/Server.hpp"

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <thread>

using namespace boost::asio::ip;

namespace Horizon
{
namespace Networking
{
/**
 * @brief Connector object that allows connecting to remote endpoints.
 *        Connections are passed to network connected threads that handle
 *        them separately from accepted threads.
 */
class Connector
{
public:
	typedef boost::function<void(std::string &, std::shared_ptr<tcp::socket>, uint32_t)> ConnectorCallback;

	/**
	 * @brief Connector contructor
	 * @param[in|out] connection_name constant reference to the name string of the connection being created.
	 * @param[in|out] server           pointer to the server object that is instantiating the connection.
	 * @param[in|out] connect_ip      constant reference to the ip string of the endpoint to connect to.
	 * @param[in]     port            port number of the endpoint to connect to.
	 */
	Connector(std::string const &connection_name, Server *server, std::string const &connect_ip, uint16_t port)
	: server(server), _connection_name(connection_name), _endpoint(boost::asio::ip::address::from_string(connect_ip), port),
	_socket_factory(std::bind(&Connector::default_socket_factory, this))
	{
	}

	/**
	 * @brief Destructor of the object that handles joining of all socket polling threads.
	 */
	Connector()
	{
	}

	/**
	 * @brief Attempts connections to the remote endpoint that the object was initiated with.
	 *        The responsibilities of this method are -
	 *        1) Attempt to open connections to an endpoint and retry on failure.
	 *        2) Execute callbacks to functions that handle the ownership of the connected socket.
	 *        3) Start threads that execute state-verification checks of each connection.
	 * @param[in] callback     the callback function that handles socket ownership.
	 * @param[in] connections  the number of connections to the endpoint that will be initiated and handled.
	 */
	void connect_with_callback(ConnectorCallback callback, int connections = 1)
	{
		for (int i = 0; i < connections && server->get_shutdown_stage() >= SHUTDOWN_INITIATED; i++) {
			std::shared_ptr<tcp::socket> socket;
			uint32_t network_thread_idx;
			boost::system::error_code error;

			// Get a new socket from a thread with the minimum connections.
			std::tie(socket, network_thread_idx) = _socket_factory();

			do {
				CoreLog->info("Trying to establish connection for '{}' at tcp://{}:{}.", _connection_name, _endpoint.address().to_string(), _endpoint.port());

				// Try connecting to the endpoint.
				socket->connect(_endpoint, error);

				if (error.value() != 0) {
					CoreLog->error("Error connecting to '{}' endpoint tcp://{}:{}. Error Message: '{}'. Retrying in 10 seconds...", _connection_name, _endpoint.address().to_string(), _endpoint.port(), error.message());
					std::this_thread::sleep_for(std::chrono::seconds(10));
					socket->close();
					error.clear();
				} else {
					callback(_connection_name, socket, network_thread_idx);
					CoreLog->info("Successfully connected to '{}' at endpoint tcp://{}:{}.", _connection_name, _endpoint.address().to_string(), _endpoint.port());
				}
			} while (!socket->is_open() && server->get_shutdown_stage() >= SHUTDOWN_INITIATED);
		}
	}

	/**
	 * @brief Sets a socket factory method that provides a socket for new connections.
	 */
	void set_socket_factory(std::function<std::pair<std::shared_ptr<tcp::socket>, uint32_t>()> &&func) { _socket_factory = func; }

private:
	std::pair<std::shared_ptr<tcp::socket>, uint32_t> default_socket_factory() { return std::make_pair(nullptr, 0); }

	Server *server;
	std::string _connection_name;
	tcp::endpoint _endpoint;
	std::function<std::pair<std::shared_ptr<tcp::socket>, uint32_t>()> _socket_factory;
};
}
}

#endif //HORIZON_NETWORKCONNECTOR_HPP
