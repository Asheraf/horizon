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

#ifndef HORIZON_NETWORKING_NETWORKTHREAD_HPP
#define HORIZON_NETWORKING_NETWORKTHREAD_HPP

#include "Core/Logging/Logger.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include <cassert>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Networking
{
/**
 * @brief A Network Thread object that handles a number of sockets.
 *        Sockets are moved into the thread by SocketMgr, once accepted or connected.
 *        Once started, the object blocks to handle I/O events and requires explicit stopping.
 */
template <class SocketType>
class NetworkThread
{
public:
	NetworkThread()
	: _connections(0), _stopped(false), _updateTimer(_io_service)
	{
		// Constructor
	}

	/**
	 * @brief Destructor of the network thread,
	 *        performs a clean network finalisation routine before deleting.
	 */
	virtual ~NetworkThread()
	{
		Stop();

		if (_thread != nullptr)
			Wait();
	}

	/**
	 * @brief Halts the IO Service and marks the network thread as stopped.
	 */
	void Stop()
	{
		if (_stopped.exchange(true))
			return;

		_io_service.stop();
	}

	/**
	 * @brief Initializes the network thread and runs.
	 * @return true on success, false if thread is a nullptr.
	 */
	bool Start()
	{
		if (_thread != nullptr)
			return false;

		_thread.reset(new std::thread(&NetworkThread::Run, this));
		return true;
	}

	/**
	 * @brief Join the network thread with the main thread.
	 */
	void Wait()
	{
		assert(_thread);
		_thread->join();
	}

	/**
	 * @brief Adds a new socket to a queue that is processed
	 *        frequently within this network thread. The method
	 *        Update() is called regularly to add new sockets
	 *        to the thread's active socket list.
	 */
	virtual void AddSocket(std::shared_ptr<SocketType> sock)
	{
		std::lock_guard<std::mutex> lock(_new_socket_queue_lock);

		++_connections; // Increment network connections.

		_new_socket_queue.push_back(sock);  // Add socket to queue.

		SocketAdded(sock); // SocketAdded event for child classes.

		CoreLog->trace("A new socket has been added to a thread. (Thread Connections: {}) ", _connections);
	}

	/**
	 * @brief Gets a socket for a new connection.
	 *        This method is used as a socket factory in AsyncAcceptor and Connector classes.
	 *        Once a socket is accepted or connected, its ownership is moved into a network thread.
	 * @return a new shared pointer to a tcp::socket.
	 */
	std::shared_ptr<tcp::socket> GetSocketForNewConnection() { return std::make_shared<tcp::socket>(_io_service); }

	/**
	 * @brief Gets the total number of network connections or sockets
	 *        handled by this network thread.
	 * @return total number of connections in this network thread.
	 */
	int32_t GetConnectionCount() const { return _connections; }

protected:
	virtual void SocketAdded(std::shared_ptr<SocketType> /*sock*/) { }
	virtual void SocketRemoved(std::shared_ptr<SocketType> /*sock*/) { }

	/**
	 * @brief Run the I/O Service loop within this network thread.
	 *        Before running, this method gives the I/O service some work
	 *        by asynchronously running a deadline timer on @see Update()
	 */
	void Run()
	{
		CoreLog->trace("Thread for new I/O service initiated.");
		_updateTimer.expires_from_now(boost::posix_time::milliseconds(10));
		_updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));

		_io_service.run();

		_new_socket_queue.clear();
		_active_sockets.clear();
	}

	/**
	 * @brief Updates the network thread and schedules a recursive call to itself.
	 *        This method is responsible for the following tasks -
	 *        1) Issuing a routine to process the new sockets queue.
	 *        2) Closes sockets that cannot be updated. @see Socket<SocketType>::Update()
	 */
	void Update()
	{
		if (_stopped)
			return;

		_updateTimer.expires_from_now(boost::posix_time::milliseconds(10));
		_updateTimer.async_wait(std::bind(&NetworkThread<SocketType>::Update, this));

		AddNewSockets();

		_active_sockets.erase(std::remove_if(_active_sockets.begin(), _active_sockets.end(), [this] (std::shared_ptr<SocketType> sock)
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
			}), _active_sockets.end());
	}

	/**
	 * @brief Processess the new socket queue.
	 *        This method is responsible for -
	 *        1) Processing the entire list of new sockets and clearing it on every call.
	 *        2) removing / closing new sockets that are not open.
	 *        3) Starting the new socket once added to the container. (@see Socket<SocketType>::Start())
	 */
	void AddNewSockets()
	{
		std::lock_guard<std::mutex> lock(_new_socket_queue_lock);

		if (_new_socket_queue.empty())
			return;

		for (std::shared_ptr<SocketType> sock : _new_socket_queue) {
			if (!sock->IsOpen()) {
				SocketRemoved(sock);
				--_connections;
			} else {
				_active_sockets.push_back(sock);
				// Start receiving from the socket.
				sock->Start();
			}
		}

		_new_socket_queue.clear();
	}

private:
	typedef std::vector<std::shared_ptr<SocketType>> SocketContainer;

	std::atomic<int32_t> _connections;
	std::atomic<bool> _stopped;

	std::unique_ptr<std::thread> _thread;

	SocketContainer _active_sockets;
	SocketContainer _new_socket_queue;

	std::mutex _new_socket_queue_lock;

	boost::asio::io_service _io_service;
	boost::asio::deadline_timer _updateTimer;
};
}
}

#endif // HORIZON_NETWORKING_NETWORKTHREAD_HPP
