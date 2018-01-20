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

#ifndef HORIZON_CHARSESSION_H
#define HORIZON_CHARSESSION_H


#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"

#include "Server/Packet.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>

using boost::asio::ip::tcp;

class CharSession : public Socket<CharSession>
{
	friend class CharMain;
	typedef Socket<CharSession> CharSocket;
	typedef void (CharSession::*CharPacketHandler) (PacketBuffer &pkt);
public:
	CharSession(tcp::socket &&socket);
	~CharSession() { }

	void Start() override;
	bool Update() override;

	void SendPacket(ByteBuffer& packet);

	bool HandleIncomingPacket(PacketBuffer &packet);

	void InitHandlers();

	/**
	 * Receivable Packets
	 */
	void Handle_CH_ENTER(PacketBuffer &pkt);
	void Handle_CH_SELECT_CHAR(PacketBuffer &pkt);
	void Handle_CH_MAKE_CHAR(PacketBuffer &pkt);
	void Handle_CH_DELETE_CHAR(PacketBuffer &pkt);
	/**
	 * Sendable Responses
	 */
	void Response_HC_ACCEPT_ENTER();
	void Response_HC_REFUSE_ENTER();
	void Response_HC_ACCEPT_MAKECHAR();
	void Response_HC_REFUSE_MAKECHAR();
	void Response_HC_ACCEPT_DELETECHAR();
	void Response_HC_REFUSE_DELETECHAR();
	void Response_HC_NOTIFY_ZONESVR();

protected:
	std::unordered_map<uint16_t, CharPacketHandler> handlers;
	void ReadHandler() override;
	void OnClose() override;
};

#endif //HORIZON_CHARSESSION_H
