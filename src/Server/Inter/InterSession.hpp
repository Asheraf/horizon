/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#ifndef HORIZON_INTER_INTERSESSION_H
#define HORIZON_INTER_INTERSESSION_H

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Common/Packet.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

namespace Horizon
{
namespace Inter
{
class PacketHandler;
class InterSession : public Socket<InterSession>
{
	friend class InterMain;
	typedef Socket<InterSession> InterSocket;
	typedef void (InterSession::*InterPacketHandler) (PacketBuffer &pkt);
public:
	InterSession(std::shared_ptr<tcp::socket> socket);
	~InterSession() { }

	void Start() override;
	bool Update() override;

	/**
	 * Receivable Packets
	 */

	/**
	 * Sendable Responses
	 */

protected:
	void ReadHandler() override;
	void OnClose() override;

private:
	std::shared_ptr<PacketHandler> _packet_handler;
};
}
}

#endif //HORIZON_INTERSESSION_H
