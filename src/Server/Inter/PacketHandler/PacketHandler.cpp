//
// Created by SagunKho on 29/01/2018.
//

#include "PacketHandler.hpp"

#include "Packets.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Inter/InterSession.hpp"

#include <boost/bind.hpp>
#include <Libraries/BCrypt/BCrypt.hpp>
#include <Server/Inter/Inter.hpp>

Horizon::Inter::PacketHandler::PacketHandler(std::shared_ptr<InterSession> session)
	: _session(session)
{
	// Construct
	InitializeHandlers();
}

Horizon::Inter::PacketHandler::~PacketHandler()
{
	// Destruct
}

void Horizon::Inter::PacketHandler::InitializeHandlers()
{
	_handlers.insert(std::make_pair(INTER_CONNECT_AUTH, boost::bind(&PacketHandler::Handle_CONNECT_AUTH, this, boost::placeholders::_1)));
}

bool Horizon::Inter::PacketHandler::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (packets) packet.getOpCode();
	auto it = _handlers.find(opCode);

	if (it == _handlers.end()) {
		InterLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	PacketHandlerFunc func = it->second;
	func(packet);

	return true;
}

template <class T>
void Horizon::Inter::PacketHandler::SendPacket(T pkt)
{
	PacketBuffer buf;

	buf << pkt;

	if (!_session->IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), sizeof(T));
		_session->QueuePacket(std::move(buffer));
	}
}

void Horizon::Inter::PacketHandler::SendPacket(PacketBuffer &buf, std::size_t size)
{
	if (!_session->IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), size);
		_session->QueuePacket(std::move(buffer));
	}
}

void Horizon::Inter::PacketHandler::Handle_CONNECT_AUTH(PacketBuffer &buf)
{
	PACKET_INTER_CONNECT_AUTH pkt;
	bool success;

	buf.read(&pkt, 4);

	char pass[pkt.packet_len - 4];
	buf.read(pass, sizeof(pass));

	if (!(success = BCrypt::validatePassword(pass, InterServer->getNetworkConf().getInterServerPassword()))) {
		_session->CloseSocket();
	}

	Respond_CONNECT_RESPONSE(success);
}

void Horizon::Inter::PacketHandler::Respond_CONNECT_RESPONSE(bool success)
{
	PACKET_INTER_CONNECT_RESPONSE pkt;
	pkt.success = (uint8_t) success;

	SendPacket(pkt);
}

void Horizon::Inter::PacketHandler::Respond_ACK_RECEIVED(uint16_t packet_id)
{
	PACKET_INTER_ACK_RECEIVED pkt;
	pkt.ack_packet_id = packet_id;
	SendPacket(pkt);
}

void Horizon::Inter::PacketHandler::Respond_CONNECT_INIT()
{
	SendPacket(PACKET_INTER_CONNECT_INIT());
}