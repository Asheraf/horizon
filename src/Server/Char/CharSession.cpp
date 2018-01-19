//
// Created by SagunKho on 16/01/2018.
//

#include "CharSession.hpp"

#include "Core/Logging/Logger.hpp"
#include "CharPackets.hpp"

CharSession::CharSession(tcp::socket &&socket)
  : Socket(std::move(socket))
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

	AsyncRead();
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

void CharSession::Handle_CH_ENTER(PacketBuffer &pkt)
{
	//
}

void CharSession::Handle_CH_SELECT_CHAR(PacketBuffer &pkt)
{
	//
}

void CharSession::Handle_CH_MAKE_CHAR(PacketBuffer &pkt)
{
	//
}

void CharSession::Handle_CH_DELETE_CHAR(PacketBuffer &pkt)
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
