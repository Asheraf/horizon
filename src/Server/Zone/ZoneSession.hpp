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

#ifndef HORIZON_ZONESESSION_H
#define HORIZON_ZONESESSION_H


#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"

#include "Server/Packet.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class ZoneSession : public Socket<ZoneSession>
{
	friend class ZoneMain;
	typedef Socket<ZoneSession> ZoneSocket;
	typedef void (ZoneSession::*ZonePacketHandler) (PacketBuffer &pkt);
public:
	ZoneSession(tcp::socket &&socket);
	~ZoneSession() { }

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
	std::unordered_map<uint16_t, ZonePacketHandler> handlers;
	void ReadHandler() override;
	void OnClose() override;
};

#endif //HORIZON_ZONESESSION_H
