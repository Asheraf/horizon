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

#include "CharSession.hpp"

#include "CharPackets.hpp"

CharSession::CharSession(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
	InitHandlers();
}

void CharSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	CharLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void CharSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	CharLog->info("Closed connection from {}.", ip_address);
}

bool CharSession::Update()
{
	return CharSocket::Update();
}

void CharSession::SendPacket(ByteBuffer &packet)
{
	if (!IsOpen())
		return;

	if (!packet.empty()) {
		MessageBuffer buffer;
		buffer.Write(packet.contents(), packet.size());
		QueuePacket(std::move(buffer));
	}
}

/**
 * Incoming buffer read handler.
 */
void CharSession::ReadHandler()
{
	uint16_t op_code;

	while (GetReadBuffer().GetActiveSize()) {
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, std::move(GetReadBuffer()));

		if (!HandleIncomingPacket(pkt))
			GetReadBuffer().Reset();
	}
}

bool CharSession::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (char_client_packets) packet.getOpCode();
	CharPacketHandler func = nullptr;

	/* Call the function handling */
	if ((func = handlers[opCode]) == nullptr) {
		CharLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	(this->*func)(packet);

	return true;
}

void CharSession::Handle_CH_ENTER(PacketBuffer &/*pkt*/)
{
	//
}

void CharSession::Handle_CH_SELECT_CHAR(PacketBuffer &/*pkt*/)
{
	//
}

void CharSession::Handle_CH_MAKE_CHAR(PacketBuffer &/*pkt*/)
{
	//
}

void CharSession::Handle_CH_DELETE_CHAR(PacketBuffer &/*pkt*/)
{
	//
}
/**
 * Sendable Packets
 */
void CharSession::Response_HC_ACCEPT_ENTER()
{
	//
}

void CharSession::Response_HC_REFUSE_ENTER()
{
	//
}

void CharSession::Response_HC_ACCEPT_MAKECHAR()
{
	//
}

void CharSession::Response_HC_REFUSE_MAKECHAR()
{
	//
}

void CharSession::Response_HC_ACCEPT_DELETECHAR()
{
	//
}

void CharSession::Response_HC_REFUSE_DELETECHAR()
{
	//
}

void CharSession::Response_HC_NOTIFY_ZONESVR()
{
	//
}

void CharSession::InitHandlers()
{
	/**
	 * Client To Auth
	 */
	handlers.insert(std::make_pair(CH_ENTER, &CharSession::Handle_CH_ENTER));
	handlers.insert(std::make_pair(CH_SELECT_CHAR, &CharSession::Handle_CH_SELECT_CHAR));
	handlers.insert(std::make_pair(CH_MAKE_CHAR, &CharSession::Handle_CH_MAKE_CHAR));
	handlers.insert(std::make_pair(CH_DELETE_CHAR, &CharSession::Handle_CH_DELETE_CHAR));
}
