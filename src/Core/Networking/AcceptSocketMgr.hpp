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

#include <boost/bind.hpp>
#include <boost/thread.hpp>

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

		CoreLog->trace("Max allowed socket connections {}", (int) boost::asio::socket_base::max_connections);

		_acceptor->set_socket_factory(std::bind(&BaseSocketMgr::get_new_socket, this));
		_acceptor->async_accept_with_callback(boost::bind(&AcceptSocketMgr<SocketType>::on_socket_open, this, boost::placeholders::_1, boost::placeholders::_2));

		CoreLog->info("Networking initialized, listening on {} {} (Maximum Threads: {})", listen_ip, port, threads);

		return true;
	}

	/**
	 * @brief Stop the Acceptor network and clear the client socket map.
	 */
	virtual void stop_network() override
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);

		BaseSocketMgr::stop_network();

		if (_acceptor->is_open())
			_acceptor->close();
		
		_socket_map.clear();
	}
	
	/**
	 * Client (Player) Session Handlers
	 * @param[in] session_id Id of the session to get.
	 * @return shared_ptr to the session.
	 */
	std::shared_ptr<SocketType> get_socket(uint32_t session_id)
	{
		boost::shared_lock<boost::shared_mutex> lock(_socket_mtx);

		auto it = _socket_map.find(session_id);

		if (it != _socket_map.end())
			return _socket_map.at(session_id);

		return nullptr;
	}

	/**
	 * Removes a client session.
	 * @param[in] session_id Id of the session to get.
	 * @return shared_ptr to the session.
	 */
	void remove_socket(uint32_t session_id)
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);

		if (_socket_map.find(session_id) != _socket_map.end()) {
			_socket_map.erase(session_id);
			CoreLog->info("SocketMgr::RemoveClientSession: successfully removed session ID - {}.", session_id);
		}
	}

	/**
	 * @brief On Socket Open / Start Event. Called as a callback from an Acceptor on successful socket acceptance.
	 *        Moves the socket ownership from the caller to a new socket and adds it to a network acceptor thread
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	void on_socket_open(std::shared_ptr<tcp::socket> const &socket, uint32_t thread_index)
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);
		
		std::shared_ptr<SocketType> new_socket = BaseSocketMgr::on_socket_open(std::move(socket), thread_index);
		_socket_map.insert(std::make_pair(new_socket->get_socket_id(), new_socket));
	}

	/**
	 * @brief Routine called from an implemented socket when finalising / closing.
	 * @param[in|out] session pointer to the session that the socket belongs to.
	 */
	void clear_socket(std::shared_ptr<SocketType> socket)
	{
		remove_socket(socket->get_socket_id());
	}

	void update_socket_sessions(uint32_t diff)
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);

		for (auto sock : _socket_map)
			if (sock.second->get_session() != nullptr)
				sock.second->get_session()->update(diff);
	}

private:
	std::unique_ptr<AsyncAcceptor> _acceptor;       ///< unique pointer to an AsyncAcceptor object.
	SocketMap _socket_map;                          ///< std::map of all connected and handled sockets.
	boost::shared_mutex _socket_mtx;
};
}
}

#endif /* HORIZON_NETWORKING_ACCEPTSOCKETMGR_HPP */
