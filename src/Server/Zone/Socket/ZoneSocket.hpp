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

#ifndef HORIZON_ZONE_ZONESOCKET_HPP
#define HORIZON_ZONE_ZONESOCKET_HPP

#include "Core/Networking/Socket.hpp"
#include "Server/Common/PacketBuffer.hpp"

#include <memory>
#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class PacketBuffer;

namespace Horizon
{
namespace Zone
{
class ZoneSession;
class ZoneSocket : public Horizon::Networking::Socket<ZoneSocket>
{
	typedef Socket<ZoneSocket> BaseSocket;
public:
	ZoneSocket(std::shared_ptr<tcp::socket> socket);
	~ZoneSocket() { }
	/* */
	void start() override;
	bool update() override;

	/* */
	std::shared_ptr<ZoneSession> get_session();
	void set_session(std::shared_ptr<ZoneSession> session);

	/* */
	PacketQueueType &get_packet_recv_queue() { return _packet_recv_queue; }

protected:
	void read_handler() override;
	void on_close() override;
	void on_error() override;

private:
	PacketQueueType _packet_recv_queue;
	std::shared_ptr<ZoneSession> _session;
};
}
}
#endif //HORIZON_ZONE_ZONESOCKET_HPP
