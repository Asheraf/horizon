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
	typedef std::map<uint32_t, std::shared_ptr<SocketType>> SessionMap;
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
	virtual bool Start(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads = 1)
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

		_acceptor->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForNewConnection, this));
		_acceptor->AsyncAcceptWithCallback(boost::bind(&AcceptSocketMgr<SocketType>::OnSocketOpen, this, boost::placeholders::_1, boost::placeholders::_2));

		CoreLog->info("Networking initialized, listening on {} {} (Maximum Threads: {})", listen_ip, port, threads);

		return true;
	}

	/**
	 * @brief Stop the Acceptor network and clear the client session map.
	 */
	void StopNetwork() override
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);

		BaseSocketMgr::StopNetwork();

		_acceptor->Close();
		_session_map.clear();
	}
	
	/**
	 * Client (Player) Session Handlers
	 * @param[in] session_id Id of the session to get.
	 * @return shared_ptr to the session.
	 */
	std::shared_ptr<SocketType> GetSession(uint32_t session_id)
	{
		boost::shared_lock<boost::shared_mutex> lock(_socket_mtx);

		auto it = _session_map.find(session_id);

		if (it != _session_map.end())
			return _session_map.at(session_id);

		return nullptr;
	}

	/**
	 * Removes a client session.
	 * @param[in] session_id Id of the session to get.
	 * @return shared_ptr to the session.
	 */
	void RemoveSession(uint32_t session_id)
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);

		if (_session_map.find(session_id) != _session_map.end()) {
			_session_map.erase(session_id);
			CoreLog->info("SocketMgr::RemoveClientSession: successfully removed session ID - {}.", session_id);
		}
	}

	/**
	 * @brief On Socket Open / Start Event. Called as a callback from an Acceptor on successful socket acceptance.
	 *        Moves the socket ownership from the caller to a new socket and adds it to a network acceptor thread
	 * @param[in]     socket         shared pointer.
	 * @param[in]     thread_index   index of the thread that the socket is being moved from.
	 */
	void OnSocketOpen(std::shared_ptr<tcp::socket> const &socket, uint32_t thread_index)
	{
		boost::unique_lock<boost::shared_mutex> lock(_socket_mtx);
		
		std::shared_ptr<SocketType> session = BaseSocketMgr::OnSocketOpen(std::move(socket), thread_index);
		_session_map.insert(std::make_pair(session->getSocketId(), session));
	}

	/**
	 * @brief Routine called from an implemented socket when finalising / closing.
	 * @param[in|out] session pointer to the session that the socket belongs to.
	 */
	void ClearSession(std::shared_ptr<SocketType> session)
	{
		RemoveSession(session->getSocketId());
	}

private:
	std::unique_ptr<AsyncAcceptor> _acceptor;       ///< unique pointer to an AsyncAcceptor object.
	SessionMap _session_map;                        ///< std::map of all connected and handled sessions.
	boost::shared_mutex _socket_mtx;
};
}
}

#endif /* HORIZON_NETWORKING_ACCEPTSOCKETMGR_HPP */
