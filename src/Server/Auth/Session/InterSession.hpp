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

#ifndef HORIZON_AUTH_INTERSESSION_HPP
#define HORIZON_AUTH_INTERSESSION_HPP

#include "Server/Common/Horizon.hpp"
#include "Core/Networking/Socket.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>
#include <boost/thread.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Auth
{
class InterPacketHandler;
class InterSession : public Socket<InterSession>
{
	typedef Socket<InterSession> AuthSocket;
public:
	explicit InterSession(std::shared_ptr<tcp::socket> socket);
	~InterSession() { }

	/* */
	void start() override;
	bool update() override;

	/* Packet Handler */
	std::shared_ptr<InterPacketHandler> getPacketHandler();
	void setPacketHandler(std::shared_ptr<InterPacketHandler> handler);
	/* */
protected:
	void onClose() override;
	void readHandler() override;
	/* */
private:
	std::shared_ptr<InterPacketHandler> _packet_handler;
	boost::shared_mutex _handler_lock;
};
}
}

#endif /* HORIZON_AUTH_INTERSESSION_HPP */
