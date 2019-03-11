/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
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

	void update_session(uint32_t diff);
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
