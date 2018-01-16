//
// Created by SagunKho on 16/01/2018.
//

#include "CharSession.h"

#include "CharHandle.h"

#include "Core/Logging/Logger.hpp"

CharSession::CharSession(tcp::socket &&socket)
  : Socket(std::move(socket)), _handle(new CharHandle())
{
	// Constructor
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

void CharSession::ReadHandler()
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
