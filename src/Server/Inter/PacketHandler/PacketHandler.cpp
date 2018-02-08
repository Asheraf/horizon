//
// Created by SagunKho on 29/01/2018.
//

#include "PacketHandler.hpp"

#include "Core/Logging/Logger.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Inter/Inter.hpp"
#include "Server/Inter/InterStorage.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include "Server/Inter/Session/Session.hpp"
#include "Server/Inter/SocketMgr/ClientSocketMgr.hpp"

#include <boost/bind.hpp>

Horizon::Inter::PacketHandler::PacketHandler(std::shared_ptr<Session> session)
: Horizon::Base::PacketHandler<Session>(session)
{
	// Construct
	InitializeHandlers();
}

Horizon::Inter::PacketHandler::~PacketHandler()
{
	// Destruct
}

/**
 * Handlers
 */

void Horizon::Inter::PacketHandler::InitializeHandlers()
{
#define HANDLER_FUNC(packet) addPacketHandler(Horizon::Base::inter_packets::packet, boost::bind((&PacketHandler::Handle_ ## packet), this, boost::placeholders::_1))
	HANDLER_FUNC(INTER_CONNECT_AUTH);
	HANDLER_FUNC(INTER_SESSION_DEL);
	HANDLER_FUNC(INTER_SESSION_SET);
	HANDLER_FUNC(INTER_SESSION_REQ);
	HANDLER_FUNC(INTER_GAME_ACCOUNT_DEL);
	HANDLER_FUNC(INTER_GAME_ACCOUNT_SET);
	HANDLER_FUNC(INTER_GAME_ACCOUNT_REQ);
#undef HANDLER_FUNC
}

void Horizon::Inter::PacketHandler::Handle_INTER_CONNECT_AUTH(PacketBuffer &buf)
{
	PACKET_INTER_CONNECT_AUTH pkt;
	bool success;

	buf.read(&pkt, 5);

	char pass[pkt.packet_len - 5];

	buf.read(pass, sizeof(pass));

	InterLog->info("Received request for connection of client from endpoint {}.", getSession()->getRemoteIPAddress());
	if (!(success = BCrypt::validatePassword(pass, InterServer->getNetworkConf().getInterServerPassword()))) {
		std::string password = pass;
		InterLog->info("Connection refused for endpoint {}, incorrect password {}.", getSession()->getRemoteIPAddress(), password);
		getSession()->CloseSocket();
	} else {
		InterLog->info("Connection successfully authorized for endpoint {}.", getSession()->getRemoteIPAddress());
	}
	
	getSession()->setClientType(pkt.client_type);

	Respond_INTER_ACK_RECEIVED(pkt.op_code, (uint8_t) success);
}

/**
 * Session
 */
void Horizon::Inter::PacketHandler::Handle_INTER_SESSION_SET(PacketBuffer &buf)
{
	PACKET_INTER_SESSION_SET pkt;
	SessionData session_data;
	buf >> pkt;
	session_data << pkt.s;
	SessionStore->add(pkt.s.auth_code, session_data);
}

void Horizon::Inter::PacketHandler::Handle_INTER_SESSION_DEL(PacketBuffer &buf)
{
	PACKET_INTER_SESSION_DEL pkt;
	buf >> pkt;
	SessionStore->remove(pkt.auth_code);
}

void Horizon::Inter::PacketHandler::Handle_INTER_SESSION_REQ(PacketBuffer &buf)
{
	PACKET_INTER_SESSION_REQ pkt;
	PACKET_INTER_SESSION_GET send_pkt;
	std::shared_ptr<SessionData> session_data;

	buf >> pkt;

	session_data = SessionStore->get(pkt.auth_code);

	if (session_data != nullptr) {
		*session_data >> send_pkt.s;
		SendPacket(send_pkt);
		InterLog->info("Found session data for id {} requested by server {}.", pkt.auth_code, (int) getSession()->getClientType());
	} else {
		Respond_INTER_ACK_RECEIVED(pkt.op_code, false);
		InterLog->info("Not found session data for id {} requested by server {}.", pkt.auth_code, (int) getSession()->getClientType());
	}
}

/**
 * Game Account
 */
void Horizon::Inter::PacketHandler::Handle_INTER_GAME_ACCOUNT_SET(PacketBuffer &buf)
{
	PACKET_INTER_GAME_ACCOUNT_SET pkt;
	GameAccount game_account;
	buf >> pkt;
	game_account << pkt.s;
	AccountStore->add(pkt.s.id, game_account);
}

void Horizon::Inter::PacketHandler::Handle_INTER_GAME_ACCOUNT_DEL(PacketBuffer &buf)
{
	PACKET_INTER_GAME_ACCOUNT_DEL pkt;
	buf >> pkt;
	AccountStore->remove(pkt.account_id);
}

void Horizon::Inter::PacketHandler::Handle_INTER_GAME_ACCOUNT_REQ(PacketBuffer &buf)
{
	PACKET_INTER_GAME_ACCOUNT_REQ pkt;
	PACKET_INTER_GAME_ACCOUNT_GET send_pkt;
	std::shared_ptr<GameAccount> game_account;

	buf >> pkt;

	game_account = AccountStore->get(pkt.account_id);

	if (game_account != nullptr) {
		*game_account >> send_pkt.s;
		SendPacket(send_pkt);
		InterLog->info("Found game account data for id {} requested by server {}.", pkt.account_id, (int) getSession()->getClientType());
	} else {
		Respond_INTER_ACK_RECEIVED(pkt.op_code, false);
		InterLog->info("Not found game account data for id {} requested by server {}.", pkt.account_id, (int) getSession()->getClientType());
	}
}

/**
 * Responders
 */
void Horizon::Inter::PacketHandler::Respond_INTER_ACK_RECEIVED(uint16_t packet_id, uint8_t response)
{
	PACKET_INTER_ACK_RECEIVED pkt;

	pkt.ack_packet_id = packet_id;
	pkt.response = response;

	SendPacket(pkt);
}

void Horizon::Inter::PacketHandler::Respond_INTER_CONNECT_INIT()
{
	SendPacket(PACKET_INTER_CONNECT_INIT());
}
