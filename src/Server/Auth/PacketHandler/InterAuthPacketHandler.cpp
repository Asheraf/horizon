//
// Created by SagunKho on 28/01/2018.
//

#include "InterAuthPacketHandler.hpp"
#include "Server/Auth/AuthSession.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include <boost/bind.hpp>
#include <Libraries/BCrypt/BCrypt.hpp>
#include <Server/Auth/Auth.hpp>

Horizon::Auth::InterAuthPacketHandler::InterAuthPacketHandler(std::shared_ptr<AuthSession> session)
	: _session(session)
{
	// Construct
	InitializeHandlers();
}

Horizon::Auth::InterAuthPacketHandler::~InterAuthPacketHandler()
{
	// Destruct
}

void Horizon::Auth::InterAuthPacketHandler::InitializeHandlers()
{
	_handlers.insert(std::make_pair(Horizon::Inter::INTER_CONNECT_INIT, boost::bind(&InterAuthPacketHandler::Handle_CONNECT_INIT, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(Horizon::Inter::INTER_ACK_RECEIVED, boost::bind(&InterAuthPacketHandler::Handle_ACK_RECEIVED, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(Horizon::Inter::INTER_CONNECT_RESPONSE, boost::bind(&InterAuthPacketHandler::Handle_CONNECT_RESPONSE, this, boost::placeholders::_1)));
}

bool Horizon::Auth::InterAuthPacketHandler::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (Horizon::Inter::packets) packet.getOpCode();
	auto it = _handlers.find(opCode);

	if (it == _handlers.end()) {
		AuthLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	PacketHandlerFunc func = it->second;
	func(packet);

	return true;
}

template <class T>
void Horizon::Auth::InterAuthPacketHandler::SendPacket(T pkt)
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

void Horizon::Auth::InterAuthPacketHandler::SendPacket(PacketBuffer &buf, std::size_t size)
{
	if (!_session->IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), size);
		_session->QueuePacket(std::move(buffer));
	}
}

void Horizon::Auth::InterAuthPacketHandler::Handle_ACK_RECEIVED(PacketBuffer &buf)
{
	PACKET_INTER_CONNECT_INIT pkt;
	buf >> pkt;
}

void Horizon::Auth::InterAuthPacketHandler::Handle_CONNECT_INIT(PacketBuffer &buf)
{
	// Generate Diffie-Hellman Keys.
	Respond_CONNECT_AUTH();
}

void Horizon::Auth::InterAuthPacketHandler::Handle_CONNECT_RESPONSE(PacketBuffer &buf)
{
	PACKET_INTER_CONNECT_RESPONSE pkt;
	buf >> pkt;

	if (pkt.success == 1) {
		AuthLog->info("Connection to inter server authorized.");
	} else {
		AuthLog->info("Connection to inter server not authorized.");
		_session->CloseSocket();
	}
}

void Horizon::Auth::InterAuthPacketHandler::Respond_CONNECT_AUTH()
{
	PacketBuffer buf;
	uint16_t pass_len = (uint16_t) AuthServer->getNetworkConf().getInterServerPassword().length();
	uint16_t packet_len = (uint16_t) (pass_len + 4);

	buf.append((uint16_t) Horizon::Inter::INTER_CONNECT_AUTH);
	buf.append(packet_len);
	buf.append(AuthServer->getNetworkConf().getInterServerPassword().c_str(), pass_len);
	SendPacket(buf, packet_len);
}