//
// Created by SagunKho on 29/01/2018.
//

#include "PacketHandler.hpp"

#include "Core/Logging/Logger.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"
#include "Server/Inter/InterSession.hpp"
#include "Server/Inter/Inter.hpp"
#include "Server/Inter/InterSocketMgr.hpp"
#include "Server/Inter/InterStore.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"

#include <boost/bind.hpp>

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
#define HANDLER_FUNC(packet, handler) _handlers.insert(std::make_pair((packet), boost::bind((handler), this, boost::placeholders::_1)))
	HANDLER_FUNC(INTER_CONNECT_AUTH, &PacketHandler::Handle_CONNECT_AUTH);
	HANDLER_FUNC(INTER_SESSION_DEL, &PacketHandler::Handle_SESSION_DEL);
	HANDLER_FUNC(INTER_SESSION_SET, &PacketHandler::Handle_SESSION_SET);
#undef HANDLER_FUNC
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

	Respond_ACK_RECEIVED(pkt.op_code, (uint8_t) success);
}

void Horizon::Inter::PacketHandler::Handle_SESSION_SET(PacketBuffer &buf)
{
	PACKET_INTER_SESSION_SET pkt;
	buf >> pkt;
	SessionData sessionData(pkt.s.auth_code, pkt.s.client_version, pkt.s.client_type, pkt.s.game_account_id);
	InterStore->AddToSessionStore(pkt.session_id, sessionData);
}

void Horizon::Inter::PacketHandler::Handle_SESSION_DEL(PacketBuffer &buf)
{
	PACKET_INTER_SESSION_DEL pkt;
	buf >> pkt;

	InterStore->RemoveFromSessionStore(pkt.session_id);
}

void Horizon::Inter::PacketHandler::Respond_SESSION_SET(SessionData &session_data)
{
	PACKET_INTER_SESSION_SET pkt;

	pkt.session_id = (uint32_t) session_data.getGameAccountId();
	pkt.s.game_account_id = session_data.getGameAccountId();
	pkt.s.auth_code = session_data.getAuthCode();
	pkt.s.client_type = session_data.getClientType();
	pkt.s.client_version = session_data.getClientVersion();

	SendPacket(pkt);
}

void Horizon::Inter::PacketHandler::Respond_ACK_RECEIVED(uint16_t packet_id, uint8_t response)
{
	PACKET_INTER_ACK_RECEIVED pkt;
	pkt.ack_packet_id = packet_id;
	pkt.response = response;
	SendPacket(pkt);
}

void Horizon::Inter::PacketHandler::Respond_CONNECT_INIT()
{
	SendPacket(PACKET_INTER_CONNECT_INIT());
}