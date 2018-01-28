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

#ifndef HORIZON_NETWORKTHREAD_HPP
#define HORIZON_NETWORKTHREAD_HPP

#include "Core/Logging/Logger.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include <cassert>

using boost::asio::ip::tcp;

template <class SocketType>
class NetworkThread
{
public:
	NetworkThread()
	: _connections(0), _stopped(false), _acceptSocket(_io_service), _connectSocket(_io_service), _updateTimer(_io_service)
	{
		// Constructor
	}

	virtual ~NetworkThread()
	{
		Stop();

		if (_thread != nullptr)
			Wait();
	}

	void Stop()
	{
		_stopped = true;
		_io_service.stop();
	}

	bool Start()
	{
		if (_thread != nullptr)
			return false;

		_thread.reset(new std::thread(&NetworkThread::Run, this));
		return true;
	}

	/**
	 * Join all network threads, used to stop
	 */
	void Wait()
	{
		assert(_thread);
		_thread->join();
	}

	virtual void AddSocket(std::shared_ptr<SocketType> sock)
	{
		std::lock_guard<std::mutex> lock(_newSocketsLock);

		++_connections;
		_newSockets.push_back(sock);
		SocketAdded(sock);

		CoreLog->trace("A new socket has been added to a thread. (Thread Connections: {}) ", _connections);
	}

	std::shared_ptr<tcp::socket> GetSocketForAccept() { return std::make_shared<tcp::socket>(_io_service); }
	std::shared_ptr<tcp::socket> GetSocketForConnect() { return std::make_shared<tcp::socket>(_io_service); }
	int32_t GetConnectionCount() const { return _connections; }

protected:
	virtual void SocketAdded(std::shared_ptr<SocketType> /*sock*/) { }
	virtual void SocketRemoved(std::shared_ptr<SocketType> /*sock*/) { }

	void Run()
	{
		CoreLog->trace("Thread for new I/O service initiated.");
		_updateTimer.expires_from_now(boost::posix_time::milliseconds(10));
		_updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));

		_io_service.run();

		_newSockets.clear();
		_sockets.clear();
	}

	void Update()
	{
		if (_stopped)
			return;

		_updateTimer.expires_from_now(boost::posix_time::milliseconds(10));
		_updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));

		AddNewSockets();

		_sockets.erase(std::remove_if(_sockets.begin(), _sockets.end(), [this] (std::shared_ptr<SocketType> sock)
		{
			if (!sock->Update()) {
				if (sock->IsOpen())
					sock->CloseSocket();

				this->SocketRemoved(sock);
				--this->_connections;

				CoreLog->trace("Socket closed in a networking thread. (Thread Connections: {})", this->_connections);

				return true;
			}

			return false;
		}), _sockets.end());
	}

	void AddNewSockets()
	{
		std::lock_guard<std::mutex> lock(_newSocketsLock);

		if (_newSockets.empty())
			return;

		for (std::shared_ptr<SocketType> sock : _newSockets) {
			if (!sock->IsOpen()) {
				SocketRemoved(sock);
				sock->CloseSocket();
				--_connections;
			} else {
				_sockets.push_back(sock);
				// Start receiving from the socket.
				sock->Start();
			}
		}

		_newSockets.clear();
	}

private:
	typedef std::vector<std::shared_ptr<SocketType>> SocketContainer;

	std::atomic<int32_t> _connections;
	std::atomic<bool> _stopped;

	std::unique_ptr<std::thread> _thread;

	SocketContainer _sockets;

	std::mutex _newSocketsLock;
	SocketContainer _newSockets;

	boost::asio::io_service _io_service;
	tcp::socket _acceptSocket;
	tcp::socket _connectSocket;
	boost::asio::deadline_timer _updateTimer;
};

#endif //HORIZON_NETWORKTHREAD_HPP
