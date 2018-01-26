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

#include "InterSession.hpp"

#include "Core/Logging/Logger.hpp"
#include "InterPackets.hpp"

InterSession::InterSession(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
	InitHandlers();
}

void InterSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	InterLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void InterSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	InterLog->info("Closed connection from {}.", ip_address);
}

bool InterSession::Update()
{
	return InterSocket::Update();
}

void InterSession::SendPacket(ByteBuffer &packet)
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
void InterSession::ReadHandler()
{
	uint16_t op_code;

	while (GetReadBuffer().GetActiveSize()) {
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, std::move(GetReadBuffer()));

		if (!HandleIncomingPacket(pkt))
			GetReadBuffer().Reset();
	}
}

bool InterSession::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (inter_client_packets) packet.getOpCode();
	InterPacketHandler func = nullptr;

	/* Call the function handling */
	if ((func = handlers[opCode]) == nullptr) {
		InterLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	(this->*func)(packet);

	return true;
}
/**
 * Sendable Packets
 */

void InterSession::InitHandlers()
{
	//
}
