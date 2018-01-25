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
#ifndef HORIZON_SOCKETMGR_HPP
#define HORIZON_SOCKETMGR_HPP

#include "Core/Logging/Logger.hpp"
#include "Core/Networking/AsyncAcceptor.hpp"
#include "Core/Networking/NetworkThread.hpp"
#include "NetworkConnector.hpp"

#include <boost/asio.hpp>
#include <assert.h>
#include <iostream>
#include <memory>
#include <boost/scoped_ptr.hpp>

template <class SocketType>
class SocketMgr
{
public:
	virtual ~SocketMgr() {
		assert(_thread_map.empty());
	}

	virtual bool StartNetwork(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads)
	{
		assert(threads > 0);

		try {
			_acceptor = std::make_unique<AsyncAcceptor>(io_service, listen_ip, port);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("Exception caught in SocketMgr.StartNetwork ({}, {}) {}", listen_ip, port, error.what());
			return false;
		}

		StartThreadsForNetwork(threads);
		return true;
	}

	virtual bool StartConnection(std::string  const &connection_name, boost::asio::io_service &io_service, std::string const &connect_ip, uint16_t port, uint32_t /*connections*/ = 1)
	{
		try {
			_connector = std::make_unique<NetworkConnector>(connection_name, io_service, connect_ip, port);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("SocketMgr.StartConnect '{}' to tcp:://{}:{}. Exception: {}", connection_name, connect_ip, port, error.what());
			return false;
		}

		return true;
	}

	bool StartThreadsForNetwork(uint32_t threads = 1)
	{
		for (uint32_t i = 0; i < threads; i++) {
			NetworkThreadPtr network_thr = std::make_shared<NetworkThread<SocketType>>();

			if (network_thr == nullptr) {
				CoreLog->error("Networking: Error in creating threads, SocketMgr.StartThreadForNetworks.");
				return false;
			}
			_thread_map.insert(std::make_pair(++last_thread_id, network_thr));
			network_thr->Start();
		}

		return true;
	}

	/**
	 * Perform a network finalisation routine.
	 */
	virtual void StopNetwork()
	{
		_acceptor->Close();

		CoreLog->info("Stopped {} network threads.", _thread_map.size());

		/**
		 * Clear the thread map.
		 */
		if (!_thread_map.empty()) {
			for (auto &thr : _thread_map)
				thr.second->Stop();

			_thread_map.clear();
		}

		Wait();
	}

	/**
	 * Call a join on all network threads.
	 */
	void Wait()
	{
		if (!_thread_map.empty()) {
			for (auto &thr : _thread_map)
				thr.second->Wait();
		}
	}

	/**
	 * Move the socket ownership from the caller to a new socket and add it to a thread.
	 * @param socket
	 * @param threadIndex
	 */
	void OnSocketOpen(tcp::socket &&socket, uint32_t threadIndex)
	{
		try {
			std::shared_ptr<SocketType> newSocket = std::make_shared<SocketType>(std::move(socket));
			// Set Socket data
			newSocket->setSocketId(++last_socket_id);
			// Start Session
			newSocket->Start();
			// Add socket to thread.
			NetworkThreadPtr(_thread_map.at(threadIndex))->AddSocket(newSocket);
			// Add a reference to the session container.
			_sessions.push_back(newSocket);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("Networking: Failed to retrieve client's remote address {}", error.what());
		}
	}

	uint32_t GetNetworkThreadCount() const { return (uint32_t) _thread_map.size(); }

	uint32_t SelectThreadWithMinConnections() const
	{
		uint32_t min_idx = 1;

		for (auto &thr : _thread_map)
			if (thr.second->GetConnectionCount() < NetworkThreadPtr(_thread_map.at(min_idx))->GetConnectionCount())
				min_idx = thr.first;

		return min_idx;
	}

	std::pair<tcp::socket*, uint32_t> GetSocketForAccept()
	{
		int min_idx = SelectThreadWithMinConnections();
		return std::make_pair(NetworkThreadPtr(_thread_map.at(min_idx))->GetSocketForAccept(), min_idx);
	}

	std::pair<tcp::socket *, uint32_t> GetSocketForConnect()
	{
		int min_idx = SelectThreadWithMinConnections();
		return std::make_pair(NetworkThreadPtr(_thread_map.at(min_idx))->GetSocketForConnect(), min_idx);
	}

protected:
	typedef std::shared_ptr<NetworkThread<SocketType>> NetworkThreadPtr;
	typedef std::vector<std::shared_ptr<SocketType>> SessionContainer;

	uint64_t last_socket_id;
	SessionContainer _sessions;
	std::unique_ptr<AsyncAcceptor> _acceptor;
	std::unique_ptr<NetworkConnector> _connector;
	uint32_t last_thread_id;
	std::unordered_map<uint32_t, NetworkThreadPtr> _thread_map;
};

#endif /* HORIZON_SOCKETMGR_HPP */
