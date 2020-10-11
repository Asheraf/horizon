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

#ifndef HORIZON_NETWORKING_ASYNCACCEPTOR_HPP
#define HORIZON_NETWORKING_ASYNCACCEPTOR_HPP

#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <atomic>
#include <memory>
#include <tuple>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Networking
{
/**
 * @brief Asynchronous acceptor for sockets.
 */
class AsyncAcceptor
{
public:
	typedef std::function<void(std::shared_ptr<tcp::socket>, uint32_t thread_index)> AcceptCallback;

	/**
	 * @brief Constructor of the AsyncAcceptor object.
	 * @param[in|out] io_service reference to the io_service object.
	 * @param[in]     listen_ip  const reference to the ip address string for the acceptor to bind on.
	 * @param[in]     port       port number for the acceptor to bind on.
	 */
	AsyncAcceptor(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port)
	: _acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string(listen_ip), port)),
	_endpoint(boost::asio::ip::address::from_string(listen_ip), port),
	_socket(std::make_shared<tcp::socket>(io_service)), _closed(false), _socket_factory(std::bind(&AsyncAcceptor::default_socket_factory, this))
	{
	}

	template <class T> void AsyncAccept();

	/**
	 * @brief Asynchronously accepts sockets and executes a callback function.
	 *        This function is responsible for -
	 *        1) Listening for new connections on the main thread.
	 *        2) Executing the callback provided to this method whilst moving its ownership.
	 *        3) Execute recursively on successful acceptances until closed.
	 * @param[in] callback   the callback function to execute (@see type AcceptCallback)
	 */
	void async_accept_with_callback(AcceptCallback callback)
	{
		std::shared_ptr<tcp::socket> socket;

		uint32_t thread_index;

		std::tie(socket, thread_index) = _socket_factory();

		_acceptor.async_accept(*socket, [this, socket, callback, thread_index] (boost::system::error_code error)
		   {
			   if (!error) {
				   try {
					   socket->non_blocking(true);
					   callback(std::move(socket), thread_index);
				   } catch (boost::system::system_error const &err) {
					   HLog(error) << "Networking: AsyncAcceptor failed to initialize client's socket :" << err.what();
				   }
			   }

			   if (!_closed)
				   this->async_accept_with_callback(callback);
		   });
	}

	/**
	 * @brief Binds this instance to an endpoint, to listen for connections.
	 */
	bool bind()
	{
		boost::system::error_code errorCode;

		_acceptor.open(_endpoint.protocol(), errorCode);

		if (errorCode) {
			HLog(error) << "Failed to open acceptor " << errorCode.message().c_str();
			return false;
		}

		_acceptor.bind(_endpoint, errorCode);

		if (errorCode) {
			HLog(error) << "Could not bind to " << _endpoint.address().to_string().c_str() << ":" << _endpoint.port() << " - "
             << errorCode.message().c_str();
			return false;
		}

		_acceptor.listen(boost::asio::socket_base::max_connections, errorCode);

		if (errorCode) {
			HLog(error) << "Failed to start listening on " << _endpoint.address().to_string().c_str() << ":" << _endpoint.port() << " " << errorCode.message().c_str();
			return false;
		}

		return true;
	}

	/**
	 * @brief Closes the acceptor across all threads.
	 */
	void close()
	{
		if (_closed.exchange(true))
			return;

		boost::system::error_code error;
		_acceptor.close(error);
	}

	bool is_open() { return _closed.load(); }

	/**
	 * @brief Sets the socket factory for the acceptor.
	 */
	void set_socket_factory(std::function<std::pair<std::shared_ptr<tcp::socket>, uint32_t>()> &&func) { _socket_factory = func; }

private:
	std::pair<std::shared_ptr<tcp::socket>, uint32_t> default_socket_factory() { return std::make_pair(_socket, 0); }

	tcp::acceptor _acceptor;
	tcp::endpoint _endpoint;
	std::shared_ptr<tcp::socket> _socket;
	std::atomic<bool> _closed;
	std::function<std::pair<std::shared_ptr<tcp::socket>, uint32_t>()> _socket_factory;
};

template <class T>
void AsyncAcceptor::AsyncAccept()
{
	_acceptor.async_accept(_socket, [this] (boost::system::error_code error)
	   {
		   if (!error) {
			   try {
				   std::make_shared<T>(std::move(this->_socket))->start();
			   } catch (boost::system::system_error const &err) {
				   std::cerr << "Network Error: failed to retrieve client's remote address " << err.what() << std::endl;
			   }
		   }

		   if (!_closed)
			   this->AsyncAccept<T>();
	   });
}
}
}

#endif // HORIZON_NETWORKING_ASYNCACCEPTOR_HPP
