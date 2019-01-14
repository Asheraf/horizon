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

#ifndef HORIZON_INTER_INTERSOCKET_HPP
#define HORIZON_INTER_INTERSOCKET_HPP

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include "Server/Common/Base/PacketHandler/InterPackets.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Inter
{
class PacketHandler;
class InterSocket : public Horizon::Networking::Socket<InterSocket>
{
	typedef Socket<InterSocket> BaseSocket;
public:
	InterSocket(std::shared_ptr<tcp::socket> socket);
	~InterSocket() { }

	void start() override;
	bool update() override;

	/* Packet Handler */
	std::shared_ptr<PacketHandler> get_packet_handler() { return _packet_handler; }
	void set_packet_handler(std::shared_ptr<PacketHandler> packet_handler) { _packet_handler = packet_handler; }

	/* Client Type */
	inter_connect_client_types get_client_type() const { return _client_type; }
	void set_client_type(inter_connect_client_types type) { _client_type = type; }

protected:
	void read_handler() override;
	void on_close() override;

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	inter_connect_client_types _client_type;
};
}
}

#endif //HORIZON_INTER_INTERSOCKET_HPP
