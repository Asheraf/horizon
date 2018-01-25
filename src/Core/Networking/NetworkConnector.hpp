//
// Created by SagunKho on 23/01/2018.
//

#ifndef HORIZON_NETWORKCONNECTOR_HPP
#define HORIZON_NETWORKCONNECTOR_HPP

#include <boost/asio.hpp>
#include <thread>
#include <Core/Logging/Logger.hpp>

using namespace boost::asio::ip;

class NetworkConnector
{
public:
	typedef void (*NetworkConnectorCallback) (tcp::socket &&newSocket, uint32_t thread_index);

	NetworkConnector(std::string connection_name, boost::asio::io_service &io_service, std::string const &connect_ip, uint16_t port)
	: _connection_name(connection_name), _endpoint(boost::asio::ip::address::from_string(connect_ip), port), _socket(io_service),
	  _socketFactory(std::bind(&NetworkConnector::DefaultSocketFactory, this))
	{
	}

	~NetworkConnector()
	{
	}

	template<NetworkConnectorCallback networkConnectorCallback>
	void ConnectWithCallback(int /*connections*/ = 1)
	{
		tcp::socket *socket;
		uint32_t thread_index;
		boost::system::error_code error;
		int connection_count = 0;

		do {
			CoreLog->error("Trying to establish connection for '{}' at tcp://{}:{}.", _connection_name, _endpoint.address().to_string(), _endpoint.port());

			// Get a new socket from a thread with the minimum connections.
			std::tie(socket, thread_index) = _socketFactory();

			// Try connecting to the endpoint.
			socket->connect(_endpoint, error);

			if (error) {
				CoreLog->error("Error connecting to '{}' endpoint tcp://{}:{}. Retrying in 10 seconds...", _connection_name, _endpoint.address().to_string(), _endpoint.port());
				std::this_thread::sleep_for(std::chrono::seconds(10));
			} else {
				networkConnectorCallback(std::move(*socket), thread_index);
				connection_count++;
				CoreLog->error("Successfully issued '{}' connection request to  endpoint tcp://{}:{}.", _connection_name, _endpoint.address().to_string(), _endpoint.port());
			}
		} while (error != nullptr);
	}

	void SetSocketFactory(std::function<std::pair<tcp::socket *, uint32_t>()> &&func) { _socketFactory = func; }

private:
	std::pair<tcp::socket *, uint32_t> DefaultSocketFactory() { return std::make_pair(&_socket, 0); }

	std::string _connection_name;
	tcp::endpoint _endpoint;
	tcp::socket _socket;
	std::function<std::pair<tcp::socket *, uint32_t>()> _socketFactory;
};

#endif //HORIZON_NETWORKCONNECTOR_HPP
