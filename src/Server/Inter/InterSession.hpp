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

#ifndef HORIZON_INTERSESSION_H
#define HORIZON_INTERSESSION_H

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

	void SendPacket(ByteBuffer& packet);

	bool HandleIncomingPacket(PacketBuffer &packet);

	void InitHandlers();

	/**
	 * Receivable Packets
	 */

	/**
	 * Sendable Responses
	 */

protected:
	std::unordered_map<uint16_t, InterPacketHandler> handlers;
	void ReadHandler() override;
	void OnClose() override;
};
}
}

#endif //HORIZON_INTERSESSION_H
