//
// Created by SagunKho on 27/01/2018.
//

#include "PacketHandler.hpp"

#include "Core/Database/MySqlConnection.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"
#include "Server/Auth/AuthSession.hpp"
#include "Server/Auth/Auth.hpp"
#include "Server/Inter/PacketHandler/Packets.hpp"
#include "Server/Auth/AuthSocketMgr.hpp"
#include "Server/Auth/PacketHandler/InterPacketHandler.hpp"
#include <string>

Horizon::Auth::PacketHandler::PacketHandler(std::shared_ptr<AuthSession> session)
	: _session(session)
{
	// Construct
	InitializeHandlers();
}

Horizon::Auth::PacketHandler::~PacketHandler()
{
	// Destruct
}

bool Horizon::Auth::PacketHandler::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (Horizon::Auth::packets) packet.getOpCode();
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
void Horizon::Auth::PacketHandler::SendPacket(T pkt)
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

void Horizon::Auth::PacketHandler::SendPacket(PacketBuffer &buf, std::size_t size)
{
	if (!_session->IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), size);
		_session->QueuePacket(std::move(buffer));
	}
}

void Horizon::Auth::PacketHandler::ProcessAuthentication()
{
	Respond_AC_ACCEPT_LOGIN();
}

bool Horizon::Auth::PacketHandler::ValidateSessionData(uint32_t id, uint32_t client_version, uint8_t client_type)
{
	std::shared_ptr<AuthSession> session = AuthServer->getOnlineAccount(id);
	std::shared_ptr<AuthSession> inter_session = sAuthSocketMgr.BorrowConnectedSession(INTER_SESSION_NAME);

	_session->getGameAccount()->setLastIp(_session->GetRemoteIPAddress().to_string());
	_session->getGameAccount()->setLastLogin((int) time(nullptr));
	// Session ID as Game Account Id.
	_session->getSessionData()->setGameAccountId(_session->getGameAccount()->getId());
	_session->getSessionData()->setAuthCode(_session->getGameAccount()->getId());
	_session->getSessionData()->setClientVersion(client_version);
	_session->getSessionData()->setClientType(client_type);

	// Check if session already exists.
	if (session != nullptr) {
		AuthServer->removeOnlineAccount(id);
		inter_session->getInterPacketHandler()->Respond_SESSION_DEL(_session->getSessionData()->getGameAccountId());
		sAuthSocketMgr.UnborrowConnectedSession(INTER_SESSION_NAME, inter_session);
		return true;
	}

	inter_session->getInterPacketHandler()->Respond_SESSION_SET(*_session->getSessionData());
	sAuthSocketMgr.UnborrowConnectedSession(INTER_SESSION_NAME, inter_session);
	AuthServer->addOnlineAccount(id, _session);
	return false;
}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN(PacketBuffer &packet)
{
	PACKET_CA_LOGIN pkt;
	bool authenticated = false;

	packet >> pkt;

	if (pkt.version < MINIMUM_PACKETVER || pkt.version > MAXIMUM_PACKETVER) {
		Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Authentication of account '{}' rejected. Unsupported Version.", pkt.username, pkt.version);
		return;
	}

	AuthLog->info("Authentication of account '{}' requested. (Client Version: {}, Type: {})", pkt.username, pkt.version, pkt.client_type);

	switch (AuthServer->getAuthConfig().pass_hash_method)
	{
	case PASS_HASH_NONE:
	case PASS_HASH_MD5:
		authenticated = _session->getGameAccount()->VerifyCredentials(AuthServer, pkt.username, pkt.password);
		break;
	case PASS_HASH_BCRYPT:
		authenticated = _session->getGameAccount()->VerifyCredentialsBCrypt(AuthServer, pkt.username, pkt.password);
		break;
	}

	if (authenticated) {
		if (_session->getGameAccount() == nullptr) {
			AuthLog->error("nullptr gameaccount!?!?!");
			return;
		}
		AuthLog->info("Authentication of account '{}' granted.", pkt.username);

		if (ValidateSessionData(_session->getGameAccount()->getId(), pkt.version, pkt.client_type)) {
			Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_SESSION_CONNECTED);
			AuthLog->info("Refused connection for account '{}', already online.", pkt.username);
		} else {
			ProcessAuthentication();
		}
	} else {
		Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Rejected unknown account '{}' or incorrect password.", pkt.username);
	}
}

void Horizon::Auth::PacketHandler::Handle_CA_REQ_HASH(PacketBuffer &/*packet*/)
{
	PACKET_CA_REQ_HASH pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN2(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN2 pkt;
}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN3(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN3 pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &/*packet*/)
{
	PACKET_CA_CONNECT_INFO_CHANGED pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_EXE_HASHCHECK(PacketBuffer &/*packet*/)
{
	PACKET_CA_EXE_HASHCHECK pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN_PCBANG(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_PCBANG pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN4(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN4 pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN_HAN(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_HAN pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_SSO_LOGIN_REQ(PacketBuffer &/*packet*/)
{
	PACKET_CA_SSO_LOGIN_REQ pkt;

}

void Horizon::Auth::PacketHandler::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_OTP pkt;

}

/**
 * Auth To Client
 */
void Horizon::Auth::PacketHandler::Respond_AC_ACCEPT_LOGIN()
{
	int max_servers = (int) AuthServer->totalCharacterServers();
	auto *pkt = new PACKET_AC_ACCEPT_LOGIN();
	PACKET_AC_ACCEPT_LOGIN::character_server_list *server_list;
	PacketBuffer buf;

	/**
	 * Reject if no character servers.
	 */
	if (!max_servers) {
		Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_REJECTED_FROM_SERVER);
		return;
	}

	server_list = new PACKET_AC_ACCEPT_LOGIN::character_server_list[max_servers];

	pkt->packet_len = sizeof(*pkt) + (sizeof(struct PACKET_AC_ACCEPT_LOGIN::character_server_list) * max_servers);
	pkt->auth_code = _session->getSessionData()->getAuthCode();
	pkt->aid = _session->getGameAccount()->getId();
	pkt->user_level = 1;
	pkt->last_login_ip = 0; // not used anymore.
	memset(pkt->last_login_time, '\0', sizeof(pkt->last_login_time)); // Not used anymore

	pkt->sex = (uint8_t) _session->getGameAccount()->getGender();

	for (int i = 0; i < max_servers; ++i) {
		std::shared_ptr<character_server_data> chr;

		if ((chr = AuthServer->getCharacterServer(i + 1)) == nullptr)
			continue;

		server_list[i].ip = inet_addr(chr->ip_address.c_str());
		server_list[i].port = chr->port;
		strncpy(server_list[i].name, chr->name.c_str(), sizeof(server_list[i].name));
		server_list[i].type = (uint16_t) chr->server_type;
		server_list[i].is_new = chr->is_new;
		server_list[i].usercount = 88;
	}

	buf.append<PACKET_AC_ACCEPT_LOGIN, PACKET_AC_ACCEPT_LOGIN::character_server_list>
		(pkt, sizeof(*pkt), server_list, max_servers);

	SendPacket(buf, (std::size_t) pkt->packet_len);

	delete[] server_list;
	delete pkt;
}

void Horizon::Auth::PacketHandler::Respond_AC_REFUSE_LOGIN(login_error_codes error_code)
{
	PACKET_AC_REFUSE_LOGIN pkt;
	pkt.error_code = (uint8_t) error_code;
	SendPacket(pkt);
}

void Horizon::Auth::PacketHandler::Respond_SC_NOTIFY_BAN()
{

}

void Horizon::Auth::PacketHandler::Respond_AC_ACK_HASH()
{

}

void Horizon::Auth::PacketHandler::Respond_AC_REFUSE_LOGIN_R2()
{

}

void Horizon::Auth::PacketHandler::Respond_CA_CHARSERVERCONNECT()
{

}

void Horizon::Auth::PacketHandler::InitializeHandlers()
{
	_handlers.insert(std::make_pair(CA_LOGIN, boost::bind(&PacketHandler::Handle_CA_LOGIN, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_REQ_HASH, boost::bind(&PacketHandler::Handle_CA_REQ_HASH, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_LOGIN2, boost::bind(&PacketHandler::Handle_CA_LOGIN2, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_LOGIN3, boost::bind(&PacketHandler::Handle_CA_LOGIN3, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_CONNECT_INFO_CHANGED, boost::bind(&PacketHandler::Handle_CA_CONNECT_INFO_CHANGED, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_EXE_HASHCHECK, boost::bind(&PacketHandler::Handle_CA_EXE_HASHCHECK, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_LOGIN_PCBANG, boost::bind(&PacketHandler::Handle_CA_LOGIN_PCBANG, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_LOGIN4, boost::bind(&PacketHandler::Handle_CA_LOGIN4, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_LOGIN_HAN, boost::bind(&PacketHandler::Handle_CA_LOGIN_HAN, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_SSO_LOGIN_REQ, boost::bind(&PacketHandler::Handle_CA_SSO_LOGIN_REQ, this, boost::placeholders::_1)));
	_handlers.insert(std::make_pair(CA_LOGIN_OTP, boost::bind(&PacketHandler::Handle_CA_LOGIN_OTP, this, boost::placeholders::_1)));
}

const PacketHandlerMap &Horizon::Auth::PacketHandler::getHandlers() const
{
	return _handlers;
}
