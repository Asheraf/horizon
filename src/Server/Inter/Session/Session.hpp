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

#ifndef HORIZON_INTER_SESSION_HPP
#define HORIZON_INTER_SESSION_HPP

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Inter
{
class PacketHandler;
class Session : public Socket<Session>
{
	typedef Socket<Session> InterSocket;
public:
	Session(std::shared_ptr<tcp::socket> socket);
	~Session() { }

	void Start() override;
	bool Update() override;

	/* Packet Handler */
	const std::shared_ptr<PacketHandler> &getPacketHandler() const { return _packet_handler; }
	void setPacketHandler(const std::shared_ptr<PacketHandler> &packet_handler) { Session::_packet_handler = packet_handler; }

	/* Client Type */
	inter_connect_client_type getClientType() const { return _client_type; }
	void setClientType(inter_connect_client_type type) { _client_type = type; }

protected:
	void ReadHandler() override;
	void OnClose() override;

private:
	std::shared_ptr<PacketHandler> _packet_handler;
	inter_connect_client_type _client_type;
};
}
}

#endif //HORIZON_INTER_SESSION_HPP
