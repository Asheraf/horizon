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

Horizon::Char::CharSession::CharSession(std::shared_ptr<tcp::socket> socket)
  : Socket(socket)
{
}

void Horizon::Char::CharSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	CharLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void Horizon::Char::CharSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	CharLog->info("Closed connection from {}.", ip_address);
}

bool Horizon::Char::CharSession::Update()
{
	return CharSocket::Update();
}

/**
 * Incoming buffer read handler.
 */
void Horizon::Char::CharSession::ReadHandler()
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
