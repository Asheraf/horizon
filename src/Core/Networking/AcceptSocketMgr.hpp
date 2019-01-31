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

#ifndef HORIZON_NETWORKING_ACCEPTSOCKETMGR_HPP
#define HORIZON_NETWORKING_ACCEPTSOCKETMGR_HPP

#include "Core/Networking/SocketMgr.hpp"
#include "Core/Multithreading/ThreadSafeQueue.hpp"

#include <shared_mutex>

namespace Horizon
{
namespace Networking
{
class AsyncAcceptor;
/**
 * @brief Socket Manager for Accepted Sockets.
 *        Deals with client sockets that were accepted by the server.
 */
template <class SocketType>
class AcceptSocketMgr : public SocketMgr<SocketType>
{
	typedef std::map<uint32_t, std::shared_ptr<SocketType>> SocketMap;
	typedef SocketMgr<SocketType> BaseSocketMgr;
public:
	AcceptSocketMgr() { }
	~AcceptSocketMgr() { }

	/**
	 * @brief Initialize and start accepting connections asynchronously.
	 *        This method also starts the networking threads for accepted sockets.
	 * @param[in|out] &io_service  const reference to the IO_Service object.
	 * @param[in|out] &listen_ip   const reference to the ip_address string for the acceptor to bind on.
	 * @param[in]     port         port number for the acceptor to bind on.
	 * @param[in]     threads      number of network acceptor threads to start and run.
	 * @return true on success, false on failure.
	 */
	virtual bool start(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads = 1)
	{
		try {
			_acceptor = std::make_unique<AsyncAcceptor>(io_service, listen_ip, port);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("Exception caught in AcceptSocketMgr::Start ({}, {}) {}", listen_ip, port, error.what());
			return false;
		}

		if (!BaseSocketMgr::StartNetworkThreads(threads)) {
			CoreLog->error("AcceptSocketMgr failed to start network threads.");
			return false;
		}

		_acceptor->set_socket_factory(std::bind(&BaseSocketMgr::get_new_socket, this));
		_acceptor->async_accept_with_callback(std::bind(&AcceptSocketMgr<SocketType>::on_socket_open, this, std::placeholders::_1, std::placeholders::_2));

		CoreLog->info("Networking initialized, listening on {} {} (Maximum Threads: {})", listen_ip, port, threads);

		return true;
	}

	/**
	 * @brief Stop the Acceptor network and clear the client socket map.
	 * Should not be called from network thread.
	 */
	virtual void stop_network() override
	{
		BaseSocketMgr::stop_network();

		if (_acceptor->is_open())
			_acceptor->close();
		
		_socket_map.clear();
	}
	
	/**
	 * @brief Client (Player) Session Handlers.
	 * - Can be called from any main or network threads.
	 * @param[in] socket_id Id of the session to get.
	 * @return shared_ptr to the session.
	 */
	std::shared_ptr<SocketType> get_socket(uint32_t socket_id)
	{
		std::shared_lock<std::shared_mutex> lock(_socket_mtx);

		auto it = _socket_map.find(socket_id);

		if (it != _socket_map.end())
			return _socket_map.at(socket_id);

		return nullptr;
	}

	/**
	 * @brief Removes a client socket.
	 * - Can be called from any main or network threads.
	 * @param[in] socket_id Id of the socket to get.
	 * @return shared_ptr to the session.
	 */
	void remove_socket(uint32_t socket_id)
	{
		std::unique_lock<std::shared_mutex> lock(_socket_mtx);

		if (_socket_map.find(socket_id) != _socket_map.end()) {
			_socket_map.erase(socket_id);
			CoreLog->debug("SocketMgr::RemoveClientSession: successfully removed socket ID - {}.", socket_id);
		}
	}

	/**
	 * @brief On Socket Open / Start Event. Called as a callback from an Acceptor on successful socket acceptance.
	 *        Moves the socket ownership from the caller to a network thread.
	 * - Called from one of the network threads.
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	void on_socket_open(std::shared_ptr<tcp::socket> const &socket, uint32_t thread_index)
	{
		std::unique_lock<std::shared_mutex> lock(_socket_mtx);
		
		std::shared_ptr<SocketType> new_socket = BaseSocketMgr::on_socket_open(std::move(socket), thread_index);
		_socket_map.insert(std::make_pair(new_socket->get_socket_id(), new_socket));
	}

	/**
	 * @brief Sets a socket for removal on the next session update call.
	 * Called from main thread, through update_socket_sessions while holding
	 * the unique_lock for _socket_mtx. Can also called from one of the network
	 * threads when a socket is disconnecting.
	 * @param[in] socket_id  Id of the socket to be removed.
	 */
	void set_socket_for_removal(uint32_t socket_id)
	{
		if (_socket_map.find(socket_id) != _socket_map.end())
			_socket_remove_queue.push(std::move(socket_id));
	}

	/**
	 * @brief Updates every session in the socket map and removes ones in the removal queue.
	 * - Called from the main thread only.
	 * @param[in] diff
	 */
	void update_socket_sessions(uint32_t diff)
	{
		std::shared_ptr<uint32_t> remove_id;
		
		std::unique_lock<std::shared_mutex> lock(_socket_mtx);

		while ((remove_id = _socket_remove_queue.try_pop())) {
			auto sock = _socket_map.find(*remove_id);
			if (sock != _socket_map.end())
				_socket_map.erase(sock);
		}

		for (auto sock : _socket_map)
			if (sock.second->get_session() != nullptr)
				sock.second->get_session()->update(diff);
	}

	int16_t get_packet_length(uint16_t packet_id)
	{
		std::shared_lock<std::shared_mutex> lock(_packet_len_db_mtx);

		try {
			return _packet_length_db.at(packet_id);
		} catch (std::out_of_range &e) {
			return 0;
		}
	}

	void add_packet_length(uint16_t packet_id, int16_t length)
	{
		std::unique_lock<std::shared_mutex> lock(_packet_len_db_mtx);

		_packet_length_db.emplace(packet_id, length);
	}

private:
	std::unique_ptr<AsyncAcceptor> _acceptor;       ///< unique pointer to an AsyncAcceptor object.
	SocketMap _socket_map;                          ///< std::map of all connected and handled sockets.
	std::shared_mutex _socket_mtx, _packet_len_db_mtx;
	ThreadSafeQueue<uint32_t> _socket_remove_queue;
	std::map<uint16_t, int16_t> _packet_length_db;
};
}
}

#endif /* HORIZON_NETWORKING_ACCEPTSOCKETMGR_HPP */
