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

#ifndef HORIZON_CHAR_CHARSOCKET_HPP
#define HORIZON_CHAR_CHARSOCKET_HPP

#include "Core/Networking/Socket.hpp"
#include "Server/Common/PacketBuffer.hpp" // PacketQueueType & ThreadSafeQueue

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>
#include <boost/optional.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Char
{
class CharSession;
class PacketHandler;
class CharSocket : public Horizon::Networking::Socket<CharSocket>
{
	typedef Socket<CharSocket> BaseSocket;
public:
	CharSocket(std::shared_ptr<tcp::socket> socket);
	~CharSocket();

	/* */
	void start() override;
	bool update() override;

	/* Auth Session */
	std::shared_ptr<CharSession> get_session();
	void set_session(std::shared_ptr<CharSession> session);

	PacketQueueType &get_packet_recv_queue() { return _packet_recv_queue; }

	void update_session(uint32_t diff);
	
protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;
	/* */
private:
	PacketQueueType _packet_recv_queue;
	std::shared_ptr<CharSession> _session;
};
}
}

#endif //HORIZON_CHAR_CHARSOCKET_HPP
