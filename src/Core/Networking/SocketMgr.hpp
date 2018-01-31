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
	typedef std::shared_ptr<NetworkThread<SocketType>> NetworkThreadPtr;
	typedef std::vector<std::shared_ptr<SocketType>> SessionContainer;
	typedef std::map<uint32_t, std::shared_ptr<SocketType>> SessionMap;

	struct connector_pool_data
	{
		std::shared_ptr<NetworkConnector> connector;
		SessionContainer borrowed_pool;
		SessionContainer session_pool;
	};

	typedef std::unordered_map<std::string, connector_pool_data>  NetworkConnectorPool;
public:
	virtual ~SocketMgr()
	{
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

	bool StartThreadsForNetwork(uint32_t threads = 1)
	{
		for (uint32_t i = 0; i < threads; i++) {
			NetworkThreadPtr network_thr = std::make_shared<NetworkThread<SocketType>>();

			if (network_thr == nullptr) {
				CoreLog->error("Networking: Error in creating threads, SocketMgr.StartThreadForNetworks.");
				return false;
			}
			_thread_map.insert(std::make_pair(++_last_thread_id, network_thr));
			network_thr->Start();
		}

		return true;
	}

	void AddToConnectorPool(std::string const &connection_name, std::shared_ptr<NetworkConnector> connector)
	{
		auto it = _network_connector_pool.find(connection_name);

		if (it != _network_connector_pool.end()) {
			it->second.connector = std::move(connector);
		} else {
			struct connector_pool_data cpd;
			cpd.connector = std::move(connector);
			_network_connector_pool.insert(std::make_pair(connection_name, cpd));
		}
	}

	void AddSessionToConnectorPool(std::string const &conn_name, std::shared_ptr<SocketType> session)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end())
			it->second.session_pool.push_back(session);
	}

	std::shared_ptr<SocketType> BorrowConnectedSession(std::string const &conn_name)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end() && it->second.session_pool.size() > 0) {
			std::shared_ptr<SocketType> session = it->second.session_pool.front();
			it->second.borrowed_pool.push_back(session);
			it->second.session_pool.erase(std::remove(it->second.session_pool.begin(), it->second.session_pool.end(), session), it->second.session_pool.end());
			return session;
		}

		return nullptr;
	}

	std::shared_ptr<SocketType> GetClientSession(uint32_t session_id)
	{
		auto it = _client_sessions.find(session_id);

		if (it != _client_sessions.end())
			return _client_sessions.at(session_id);

		return nullptr;
	}

	void UnborrowConnectedSession(std::string const &conn_name, std::shared_ptr<SocketType> session)
	{
		auto it = _network_connector_pool.find(conn_name);

		if (it != _network_connector_pool.end()) {
			it->second.borrowed_pool.erase(std::remove(it->second.borrowed_pool.begin(), it->second.borrowed_pool.end(), session), it->second.borrowed_pool.end());
			it->second.session_pool.push_back(session);
		}
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

	void OnSocketOpenForConnect(std::string &conn_name, std::shared_ptr<tcp::socket> &&socket, uint32_t thread_index, enum socket_endpoint_type type)
	{
		std::shared_ptr<SocketType> new_session = std::make_shared<SocketType>(std::move(socket));

		try {
			// Set Socket data
			new_session->setSocketId(++_last_socket_id);
			// Set Socket Type
			new_session->setSocketType(type);
			// Add socket to thread.
			NetworkThreadPtr(_thread_map.at(thread_index))->AddSocket(new_session);
			// Add socket to connector map.
			AddSessionToConnectorPool(conn_name, new_session);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("Networking: Failed to retrieve client's remote address {}", error.what());
		}
	}
	/**
	 * Move the socket ownership from the caller to a new socket and add it to a thread.
	 * @param socket
	 * @param threadIndex
	 */
	void OnSocketOpenForAccept(std::shared_ptr<tcp::socket> &&socket, uint32_t thread_index, enum socket_endpoint_type type)
	{
		std::shared_ptr<SocketType> new_session = std::make_shared<SocketType>(std::move(socket));

		try {
			// Set Socket data
			new_session->setSocketId(++_last_socket_id);
			// Set Socket Type
			new_session->setSocketType(type);
			// Start Session
			new_session->Start();
			// Add socket to thread.
			NetworkThreadPtr(_thread_map.at(thread_index))->AddSocket(new_session);
			// Add a reference to the appropriate session container.
			_client_sessions.insert(std::make_pair(new_session->getSocketId(), new_session));
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

	std::pair<std::shared_ptr<tcp::socket>, uint32_t> GetSocketForAccept()
	{
		int min_idx = SelectThreadWithMinConnections();
		return std::make_pair(NetworkThreadPtr(_thread_map.at(min_idx))->GetSocketForAccept(), min_idx);
	}

	std::pair<std::shared_ptr<tcp::socket>, uint32_t> GetSocketForConnect()
	{
		int min_idx = SelectThreadWithMinConnections();
		return std::make_pair(NetworkThreadPtr(_thread_map.at(min_idx))->GetSocketForConnect(), min_idx);
	}

protected:
	SocketMgr() { }

	uint64_t _last_socket_id{};
	SessionMap _client_sessions;
	std::unique_ptr<AsyncAcceptor> _acceptor;
	uint32_t _last_thread_id{};
	std::unordered_map<uint32_t, NetworkThreadPtr> _thread_map;
	NetworkConnectorPool _network_connector_pool;
};

#endif /* HORIZON_SOCKETMGR_HPP */
