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
	typedef void (*NetworkConnectorCallback) (std::string &conn_name, std::shared_ptr<tcp::socket> socket, uint32_t threadIndex);

	NetworkConnector(std::string connection_name, std::string const &connect_ip, uint16_t port)
	: _connection_name(connection_name), _endpoint(boost::asio::ip::address::from_string(connect_ip), port),
	  _socketFactory(std::bind(&NetworkConnector::DefaultSocketFactory, this))
	{
	}

	~NetworkConnector()
	{
		for (auto &thr : _socket_poll_threads)
			thr.second->join();
		_socket_poll_threads.clear();
	}

	template<NetworkConnectorCallback networkConnectorCallback>
	void ConnectWithCallback(int connections = 1)
	{
		for (int i = 0; i < connections; i++) {
			std::shared_ptr<tcp::socket> socket;
			uint32_t network_thread_idx;
			boost::system::error_code error;

			// Get a new socket from a thread with the minimum connections.
			std::tie(socket, network_thread_idx) = _socketFactory();

			do {
				CoreLog->error("Trying to establish connection for '{}' at tcp://{}:{}.", _connection_name, _endpoint.address().to_string(), _endpoint.port());

				// Try connecting to the endpoint.
				socket->connect(_endpoint, error);

				if (error != nullptr) {
					CoreLog->error("Error connecting to '{}' endpoint tcp://{}:{}. Error Message: '{}'. Retrying in 10 seconds...", _connection_name, _endpoint.address().to_string(), _endpoint.port(), error.message());
					std::this_thread::sleep_for(std::chrono::seconds(10));
					socket->close();
				} else {
					networkConnectorCallback(_connection_name, socket, network_thread_idx);
					uint64_t poll_thread_idx = ++_socket_poll_thread_index;

					// Start polling thread.
					std::shared_ptr<std::thread> poll_thread(new std::thread(std::bind(&NetworkConnector::ValidateConnection<networkConnectorCallback>,
                        this, socket, poll_thread_idx)),
                        [this] (std::thread *thr)
					{
						thr->join();
						delete thr;
					});

					_socket_poll_threads.insert(std::make_pair(poll_thread_idx, std::move(poll_thread)));
					CoreLog->error("Successfully issued '{}' connection request to  endpoint tcp://{}:{}.", _connection_name, _endpoint.address().to_string(), _endpoint.port());
				}
			} while (!socket->is_open());
		}
	}

	template<NetworkConnectorCallback networkConnectorCallback>
	void ValidateConnection(std::shared_ptr<tcp::socket> const &socket, uint64_t thread_index)
	{
		do {
			// Connection is alive, sleep for 10 seconds.
			std::this_thread::sleep_for(std::chrono::seconds(10));
		} while (socket->is_open());

		// Re-connection issue.
		this->ConnectWithCallback<networkConnectorCallback>(1);
		_socket_poll_threads.erase(thread_index);
	}

	void SetSocketFactory(std::function<std::pair<std::shared_ptr<tcp::socket>, uint32_t>()> &&func) { _socketFactory = func; }

private:
	std::pair<std::shared_ptr<tcp::socket>, uint32_t> DefaultSocketFactory() { return std::make_pair(nullptr, 0); }

	std::string _connection_name;
	tcp::endpoint _endpoint;
	std::function<std::pair<std::shared_ptr<tcp::socket>, uint32_t>()> _socketFactory;
	std::unordered_map<uint64_t, std::shared_ptr<std::thread>> _socket_poll_threads;
	std::atomic<uint64_t> _socket_poll_thread_index;
};

#endif //HORIZON_NETWORKCONNECTOR_HPP
