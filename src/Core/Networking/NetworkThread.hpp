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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_NETWORKING_NETWORKTHREAD_HPP
#define HORIZON_NETWORKING_NETWORKTHREAD_HPP

#include "Core/Logging/Logger.hpp"

#include <thread>
#include <atomic>
#include <mutex>
#include <cassert>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/deadline_timer.hpp>

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
	typedef std::vector<std::shared_ptr<SocketType>> SocketContainer;
public:
	NetworkThread()
	: _connections(0), _finalizing(false), _update_timer(_io_service)
	{
		// Constructor
	}

	/**
	 * @brief Destructor of the network thread,
	 *        performs a clean network finalisation routine before deleting.
	 */
	virtual ~NetworkThread()
	{
		finalize();
	}

	/**
	 * @brief Halts the IO Service and marks the network thread as stopped.
	 */
	void finalize()
	{
		if (_finalizing.exchange(true))
			return;
	}

	void join()
	{
		_io_service.stop();

		if (_thread != nullptr && _thread->joinable()) {
			_thread->join();
			_thread.reset(nullptr);
		}
	}

	/**
	 * @brief Initializes the network thread and runs.
	 * @return true on success, false if thread is a nullptr.
	 */
	bool start()
	{
		if (_thread != nullptr)
			return false;

		_thread.reset(new std::thread(&NetworkThread::run, this));
		return true;
	}

	/**
	 * @brief Adds a new socket to a queue that is processed
	 *        frequently within this network thread. The method
	 *        update() is called regularly to add new sockets
	 *        to the thread's active socket list.
	 */
	virtual void add_socket(std::shared_ptr<SocketType> sock)
	{
		std::lock_guard<std::mutex> lock(_new_socket_queue_lock);

		_new_socket_queue.push_back(sock);  // Add socket to queue.
	}

	/**
	 * @brief Gets a socket for a new connection.
	 *        This method is used as a socket factory in AsyncAcceptor and Connector classes.
	 *        Once a socket is accepted or connected, its ownership is moved into a network thread.
	 * @return a new shared pointer to a tcp::socket.
	 */
	std::shared_ptr<tcp::socket> get_new_socket() { return std::make_shared<tcp::socket>(_io_service); }

	/**
	 * @brief Gets the total number of network connections or sockets
	 *        handled by this network thread.
	 * @return total number of connections in this network thread.
	 */
	int32_t connection_count() const { return _connections; }

protected:
	/**
	 * @brief Run the I/O Service loop within this network thread.
	 *        Before running, this method gives the I/O service some work
	 *        by asynchronously running a deadline timer on @see update()
	 */
	void run()
	{
		CoreLog->trace("Network thread {:p} is ready for managing connections.", (void *) this);

		_update_timer.expires_from_now(boost::posix_time::milliseconds(10));
		_update_timer.async_wait(std::bind(&NetworkThread<SocketType>::update, this));

		_io_service.run();

		_new_socket_queue.clear();
		_active_sockets.clear();
	}

	/**
	 * @brief Updates the network thread and schedules a recursive call to itself.
	 *        This method is responsible for the following tasks -
	 *        1) Issuing a routine to process the new sockets queue.
	 *        2) Closes sockets that cannot be updated. @see Socket<SocketType>::update()
	 */
	void update()
	{
		_update_timer.expires_from_now(boost::posix_time::milliseconds(10));
		_update_timer.async_wait(std::bind(&NetworkThread<SocketType>::update, this));

		add_new_sockets();

		_active_sockets.erase(std::remove_if(_active_sockets.begin(), _active_sockets.end(),
			[this] (std::shared_ptr<SocketType> sock)
			{
				if (!sock->update() || _finalizing) {

					if (sock->is_open())
						sock->close_socket();

					--_connections;

					CoreLog->info("Socket closed in networking thread {:p}. (Connections: {})", (void *) (_thread.get()), _connections);

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
	 *        3) Starting the new socket once added to the container. (@see Socket<SocketType>::start())
	 */
	void add_new_sockets()
	{
		if (_finalizing)
			return;

		std::lock_guard<std::mutex> lock(_new_socket_queue_lock);

		if (_new_socket_queue.empty())
			return;

		for (std::shared_ptr<SocketType> sock : _new_socket_queue) {
			if (sock->is_open()) {
				_active_sockets.push_back(sock);
				// Start receiving from the socket.
				sock->start();

				++_connections; // Increment network connections.

				CoreLog->trace("A new socket has been added to network thread {:p}. (Connections: {}) ", (void *) (_thread.get()), _connections);
			}
		}

		_new_socket_queue.clear();
	}

private:
	std::atomic<int32_t> _connections;
	std::atomic<bool> _finalizing;

	std::unique_ptr<std::thread> _thread;

	SocketContainer _active_sockets;
	SocketContainer _new_socket_queue;

	std::mutex _new_socket_queue_lock;

	boost::asio::io_service _io_service;
	boost::asio::deadline_timer _update_timer;
};
}
}

#endif // HORIZON_NETWORKING_NETWORKTHREAD_HPP
