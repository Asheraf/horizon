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

Horizon::Inter::InterSession::InterSession(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
	InitHandlers();
}

void Horizon::Inter::InterSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	InterLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void Horizon::Inter::InterSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	InterLog->info("Closed connection from {}.", ip_address);
}

bool Horizon::Inter::InterSession::Update()
{
	return InterSocket::Update();
}

void Horizon::Inter::InterSession::SendPacket(ByteBuffer &packet)
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
void Horizon::Inter::InterSession::ReadHandler()
{
	uint16_t op_code;

	while (GetReadBuffer().GetActiveSize()) {
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, std::move(GetReadBuffer()));

		if (!HandleIncomingPacket(pkt))
			GetReadBuffer().Reset();
	}
}

bool Horizon::Inter::InterSession::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (Horizon::Inter::packets) packet.getOpCode();

	return true;
}

/**
 * Sendable Packets
 */
void Horizon::Inter::InterSession::InitHandlers()
{
	//
}
