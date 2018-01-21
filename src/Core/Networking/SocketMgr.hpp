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

#include <boost/asio.hpp>
#include <assert.h>
#include <iostream>
#include <memory>

template <class SocketType>
class SocketMgr
{
public:
	virtual ~SocketMgr() {
		assert(!_threads && !_acceptor && !_threadCount);
	}
	virtual bool StartNetwork(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, int threads)
	{
		assert(threads > 0);

		try {
			_acceptor = new AsyncAcceptor(io_service, listen_ip, port);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("Exception caught in SocketMgr.StartNetwork ({}, {}) {}", listen_ip, port, error.what());
			return false;
		}

		_threadCount = threads;
		_threads = CreateThreads();

		assert(_threads);

		if (_threads == nullptr) {
			CoreLog->error("Networking: Error in creating threads. SocketMgr.StartNetwork.");
			return false;
		}

		uint32_t i = 0;
		for ( i = 0; i < _threadCount; i++) {
			_threads[i].Start();
		}

		return true;
	}

	virtual void StopNetwork()
	{
		_acceptor->Close();

		if (_threadCount != 0) {
			for (uint32_t i = 0; i < _threadCount; i++) {
				_threads[i].Stop();
			}
		}

		CoreLog->info("Stopped {} network threads.", _threadCount);

		Wait();

		delete _acceptor;
		_acceptor = nullptr;
		delete[] _threads;
		_threads = nullptr;
		_threadCount = 0;
	}

	void Wait()
	{
		if (_threadCount != 0) {
			for (uint32_t i = 0; i < _threadCount; ++i){
				_threads[i].Wait();
			}
		}
	}

	virtual void OnSocketOpen(tcp::socket &&socket, uint32_t threadIndex)
	{
		try {
			std::shared_ptr<SocketType> newSocket = std::make_shared<SocketType>(std::move(socket));
			newSocket->Start();

			_threads[threadIndex].AddSocket(newSocket);
		} catch (boost::system::system_error const &error) {
			CoreLog->error("Networking: Failed to retrieve client's remote address {}", error.what());
		}
	}

	uint32_t GetNetworkThreadCount() const { return _threadCount; }

	uint32_t SelectThreadWithMinConnections() const
	{
		uint32_t min = 0;

		for (uint32_t i = 1; i < _threadCount; i++)
			if (_threads[i].GetConnectionCount() < _threads[min].GetConnectionCount())
				min = i;

		return min;
	}

	std::pair<tcp::socket*, uint32_t> GetSocketForAccept()
	{
		uint32_t threadIndex = SelectThreadWithMinConnections();
		return std::make_pair(_threads[threadIndex].GetSocketForAccept(), threadIndex);
	}

protected:
	SocketMgr() : _acceptor(nullptr), _threads(nullptr), _threadCount(1) { }
	virtual NetworkThread<SocketType>* CreateThreads() const = 0;

	AsyncAcceptor *_acceptor;
	NetworkThread<SocketType> *_threads;
	uint32_t _threadCount;
};

#endif /* HORIZON_SOCKETMGR_HPP */
