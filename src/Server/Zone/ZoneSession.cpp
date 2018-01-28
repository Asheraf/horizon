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

#include "ZoneSession.hpp"

#include "Core/Logging/Logger.hpp"
#include "ZonePackets.hpp"

Horizon::Zone::ZoneSession::ZoneSession(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
}

void Horizon::Zone::ZoneSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	ZoneLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void Horizon::Zone::ZoneSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	ZoneLog->info("Closed connection from {}.", ip_address);
}

bool Horizon::Zone::ZoneSession::Update()
{
	return ZoneSocket::Update();
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Zone::ZoneSession::ReadHandler()
{
	uint16_t op_code;

	while (GetReadBuffer().GetActiveSize()) {
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, GetReadBuffer().GetReadPointer(), GetReadBuffer().GetActiveSize());
		GetReadBuffer().ReadCompleted(GetReadBuffer().GetActiveSize());

//		if (!HandleIncomingPacket(pkt))
//			GetReadBuffer().Reset();
	}
}