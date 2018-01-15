//
//  AuthSession.cpp
//  Horizon
//
//  Created by SagunKho on 18/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#include "AuthSession.hpp"

#include "AuthHandle.h"

#include "Core/Logging/Logger.hpp"

AuthSession::AuthSession(tcp::socket &&socket)
: Socket(std::move(socket)), _handle(new AuthHandle())
{
	// Constructor
}

void AuthSession::Start()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	AuthLog->info("Established connection from {}.", ip_address);

	AsyncRead();
}

void AuthSession::OnClose()
{
	std::string ip_address = GetRemoteIPAddress().to_string();

	AuthLog->info("Closed connection from {}.", ip_address);
}

bool AuthSession::Update()
{
	return AuthSocket::Update();
}

void AuthSession::SendPacket(ByteBuffer &packet)
{
	if (!IsOpen())
		return;

	if (!packet.empty()) {
		MessageBuffer buffer;
		buffer.Write(packet.contents(), packet.size());
		QueuePacket(std::move(buffer));
	}
}

void AuthSession::ReadHandler()
{
	uint16_t op_code;

	while (GetReadBuffer().GetActiveSize()) {
		memcpy(&op_code, GetReadBuffer().GetReadPointer(), sizeof(uint16_t));

		PacketBuffer pkt(op_code, std::move(GetReadBuffer()));

		if (!HandleRequest()->HandleIncomingPacket(this, pkt))
			GetReadBuffer().Reset();
	}

	AsyncRead();
}