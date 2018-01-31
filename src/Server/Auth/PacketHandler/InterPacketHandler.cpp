//
// Created by SagunKho on 28/01/2018.
//

#include "InterPacketHandler.hpp"
#include "Server/Auth/AuthSession.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include <boost/bind.hpp>
#include <Libraries/BCrypt/BCrypt.hpp>
#include <Server/Auth/Auth.hpp>

Horizon::Auth::InterPacketHandler::InterPacketHandler(std::shared_ptr<AuthSession> session)
	: _session(session)
{
	// Construct
	InitializeHandlers();
}

Horizon::Auth::InterPacketHandler::~InterPacketHandler()
{
	// Destruct
}

void Horizon::Auth::InterPacketHandler::InitializeHandlers()
{
#define HANDLER_FUNC(packet, handler) _handlers.insert(std::make_pair(packet, boost::bind(handler, this, boost::placeholders::_1)))
	HANDLER_FUNC(Horizon::Inter::INTER_CONNECT_INIT, &InterPacketHandler::Handle_CONNECT_INIT);
	HANDLER_FUNC(Horizon::Inter::INTER_ACK_RECEIVED, &InterPacketHandler::Handle_ACK_RECEIVED);
#undef HANDLER_FUNC
}

bool Horizon::Auth::InterPacketHandler::HandleIncomingPacket(PacketBuffer &packet)
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
void Horizon::Auth::InterPacketHandler::SendPacket(T pkt)
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

void Horizon::Auth::InterPacketHandler::SendPacket(PacketBuffer &buf, std::size_t size)
{
	if (!_session->IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), size);
		_session->QueuePacket(std::move(buffer));
	}
}

void Horizon::Auth::InterPacketHandler::Handle_ACK_RECEIVED(PacketBuffer &buf)
{
	PACKET_INTER_ACK_RECEIVED pkt;
	buf >> pkt;

	switch (pkt.ack_packet_id)
	{
	case Horizon::Inter::INTER_CONNECT_AUTH:
		if (pkt.response == 1) {
			AuthLog->info("Connection to inter server authorized.");
		} else {
			AuthLog->info("Connection to inter server not authorized.");
			_session->CloseSocket();
		}
		break;
	default:
		AuthLog->info("Received unknown packet response from Inter {0:x}", pkt.op_code);
		break;
	}
}

void Horizon::Auth::InterPacketHandler::Handle_CONNECT_INIT(PacketBuffer &buf)
{
	// Start authentication with inter-server using passwords.
	Respond_CONNECT_AUTH();
}

void Horizon::Auth::InterPacketHandler::Respond_CONNECT_AUTH()
{
	PacketBuffer buf;
	uint16_t pass_len = (uint16_t) AuthServer->getNetworkConf().getInterServerPassword().length();
	uint16_t packet_len = (uint16_t) (pass_len + 4);

	buf.append((uint16_t) Horizon::Inter::INTER_CONNECT_AUTH);
	buf.append(packet_len);
	buf.append(AuthServer->getNetworkConf().getInterServerPassword().c_str(), pass_len);
	SendPacket(buf, packet_len);
}

void Horizon::Auth::InterPacketHandler::Respond_SESSION_SET(SessionData &session_data)
{
	PACKET_INTER_SESSION_SET pkt;

	pkt.session_id = (uint32_t) session_data.getGameAccountId();
	pkt.s.game_account_id = session_data.getGameAccountId();
	pkt.s.auth_code = session_data.getAuthCode();
	pkt.s.client_type = session_data.getClientType();
	pkt.s.client_version = session_data.getClientVersion();

	SendPacket(pkt);
}

void Horizon::Auth::InterPacketHandler::Respond_SESSION_DEL(uint32_t id)
{
	PACKET_INTER_SESSION_DEL pkt;
	pkt.session_id = id;
	SendPacket(pkt);
}
