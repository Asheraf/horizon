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
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_AUTH_SOCKET_AUTHSOCKET_HPP
#define HORIZON_AUTH_SOCKET_AUTHSOCKET_HPP

#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Core/Networking/Socket.hpp"
#include "Server/Common/PacketBuffer.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Auth
{
class InterPacketHandler;
class PacketHandler;
class AuthSession;
class AuthSocket : public Horizon::Networking::Socket<AuthSocket>
{
	typedef Socket<AuthSocket> BaseSocket;
public:
	explicit AuthSocket(std::shared_ptr<tcp::socket> socket);
	~AuthSocket();
	/* */
	void start() override;
	bool update() override;

	/* Auth Session */
	std::shared_ptr<AuthSession> get_session();
	void set_session(std::shared_ptr<AuthSession> session);

	/* */
	PacketQueueType &get_packet_recv_queue() { return _packet_recv_queue; }

	void update_session(uint32_t diff);
	
protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;

private:
	PacketQueueType _packet_recv_queue;
	std::shared_ptr<AuthSession> _session;
};
}
}

#endif /* HORIZON_AUTH_SOCKET_AUTHSOCKET_HPP */
