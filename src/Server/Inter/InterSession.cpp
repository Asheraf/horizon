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

#include "Server/Inter/PacketHandler/PacketHandlerFactory.hpp"

#include "Core/Logging/Logger.hpp"
#include "Packets.hpp"

Horizon::Inter::InterSession::InterSession(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
	//
}

void Horizon::Inter::InterSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	InterLog->info("Established connection from {}.", ip_address);

	if (_packet_handler == nullptr) {
		_packet_handler = PacketHandlerFactory::CreatePacketHandler(shared_from_this());
		_packet_handler->Respond_CONNECT_INIT();
	}
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

/**
 * Incoming buffer read handler.
 */
void Horizon::Inter::InterSession::ReadHandler()
{
	while (GetReadBuffer().GetActiveSize()) {
		uint16_t op_code;
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, GetReadBuffer().GetReadPointer(), GetReadBuffer().GetActiveSize());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());

		if (_packet_handler == nullptr) {
			_packet_handler = PacketHandlerFactory::CreatePacketHandler(shared_from_this());
			_packet_handler->Respond_CONNECT_INIT();
		}

		if (!_packet_handler->HandleIncomingPacket(pkt))
			GetReadBuffer().Reset();
	}
}