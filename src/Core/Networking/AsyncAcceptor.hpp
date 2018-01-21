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

#ifndef HORIZON_ASYNCACCEPTOR_HPP
#define HORIZON_ASYNCACCEPTOR_HPP

#include <boost/asio.hpp>
#include <functional>
#include <iostream>
#include <atomic>
#include <memory>
#include <tuple>

using boost::asio::ip::tcp;

class AsyncAcceptor
{
public:
	typedef void(*AcceptCallback) (tcp::socket &&newSocket, uint32_t thread_index);

	AsyncAcceptor(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port)
	: _acceptor(io_service, tcp::endpoint(boost::asio::ip::address::from_string(listen_ip), port)),
	_endpoint(boost::asio::ip::address::from_string(listen_ip), port),
	_socket(io_service), _closed(false), _socketFactory(std::bind(&AsyncAcceptor::DefaultSocketFactory, this))
	{
	}

	template <class T> void AsyncAccept();

	template <AcceptCallback acceptCallback>
	void AsyncAcceptWithCallback()
	{
		tcp::socket *socket;

		uint32_t thread_index;

		std::tie(socket, thread_index) = _socketFactory();

		_acceptor.async_accept(*socket, [this, socket, thread_index] (boost::system::error_code error)
		{
			if (!error) {
				try {
					socket->non_blocking(true);
					acceptCallback(std::move(*socket), thread_index);
				} catch (boost::system::system_error const &err) {
					CoreLog->error("Networking: AsyncAcceptor failed to initialize client's socket {}", err.what());
				}
			}

			if (!_closed)
				this->AsyncAcceptWithCallback<acceptCallback>();
		});
	}
	bool Bind()
	{
		boost::system::error_code errorCode;
		_acceptor.open(_endpoint.protocol(), errorCode);

		if (errorCode) {
			CoreLog->error("Failed to open acceptor %s", errorCode.message().c_str());
			return false;
		}

		_acceptor.bind(_endpoint, errorCode);
		if (errorCode) {
			CoreLog->error("Could not bind to %s:%u %s", _endpoint.address().to_string().c_str(), _endpoint.port(), errorCode.message().c_str());
			return false;
		}

		_acceptor.listen(boost::asio::socket_base::max_connections, errorCode);

		if (errorCode) {
			CoreLog->error("Failed to start listening on %s:%u %s", _endpoint.address().to_string().c_str(), _endpoint.port(), errorCode.message().c_str());
			return false;
		}

		return true;
	}

	void Close()
	{
		if (_closed.exchange(true))
			return;

		boost::system::error_code error;
		_acceptor.close(error);
	}

	void SetSocketFactory(std::function<std::pair<tcp::socket *, uint32_t>()> func) { _socketFactory = func; }

private:
	std::pair<tcp::socket*, uint32_t> DefaultSocketFactory() { return std::make_pair(&_socket, 0); }

	tcp::acceptor _acceptor;
	tcp::endpoint _endpoint;
	tcp::socket _socket;
	std::atomic<bool> _closed;
	std::function<std::pair<tcp::socket*, uint32_t>()> _socketFactory;
};

template <class T>
void AsyncAcceptor::AsyncAccept()
{
	_acceptor.async_accept(_socket, [this](boost::system::error_code error)
	{
		if (!error) {
			try {
				std::make_shared<T>(std::move(this->_socket))->Start();
			} catch (boost::system::system_error const &err) {
				std::cerr << "Network Error: failed to retrieve client's remote address " << err.what() << std::endl;
			}
		}

		if (!_closed)
			this->AsyncAccept<T>();
	});
}

#endif //HORIZON_ASYNCACCEPTOR_HPP
