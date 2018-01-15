//
// Created by SagunKho on 19/06/2017.
//

#ifndef HORIZON_AUTHSOCKETMGR_HPP
#define HORIZON_AUTHSOCKETMGR_HPP

#include "AuthSession.hpp"
#include "Core/Networking/SocketMgr.hpp"

/**
 * Auth Socket Manager
 * @brief Singleton class
 */
class AuthSocketMgr : public SocketMgr<AuthSession>
{
	typedef SocketMgr<AuthSession> BaseSocketMgr;

public:
	static AuthSocketMgr &Instance()
	{
		static AuthSocketMgr instance;
		return instance;
	}

	bool StartNetwork(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, int threads = 1) override
	{

		if (!BaseSocketMgr::StartNetwork(io_service, listen_ip, port, threads))
			return false;

		CoreLog->trace("Max allowed socket connections {}", (int) boost::asio::socket_base::max_connections);

		_acceptor->SetSocketFactory(std::bind(&BaseSocketMgr::GetSocketForAccept, this));
		_acceptor->AsyncAcceptWithCallback<&AuthSocketMgr::OnSocketAccept>();

		CoreLog->info("Networking initialized, listening on {} {} (Maximum Threads: {})", listen_ip, port, threads);

		return true;
	}

protected:
	NetworkThread<AuthSession>* CreateThreads() const override
	{
		return new NetworkThread<AuthSession>[GetNetworkThreadCount()];
	}

	static void OnSocketAccept(tcp::socket &&socket, uint32_t threadIndex)
	{
		Instance().OnSocketOpen(std::forward<tcp::socket>(socket), threadIndex);
	}
};

#define sAuthSocketMgr AuthSocketMgr::Instance()

#endif //HORIZON_AUTHSOCKETMGR_HPP
