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

#ifndef HORIZON_AUTH_INTERSOCKET_HPP
#define HORIZON_AUTH_INTERSOCKET_HPP

#include "Server/Common/Horizon.hpp"
#include "Core/Networking/Socket.hpp"

#include <cstdio>
#include <memory>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Auth
{
class InterPacketHandler;
class InterSession;
class InterSocket : public Horizon::Networking::Socket<InterSocket>
{
	typedef Socket<InterSocket> BaseSocket;
public:
	explicit InterSocket(std::shared_ptr<tcp::socket> socket);
	~InterSocket() { }
	/* */
	void start() override;
	bool update() override;

	std::shared_ptr<InterSession> get_session();
	void set_session(std::shared_ptr<InterSession> session);
	
protected:
	void on_close() override;
	void read_handler() override;
	/* */
private:
	std::shared_ptr<InterSession> _session;
};
}
}

#endif /* HORIZON_AUTH_INTERSOCKET_HPP */
