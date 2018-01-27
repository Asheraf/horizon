//
// Created by SagunKho on 27/01/2018.
//

#include "AuthPacketHandler.hpp"

#include "Core/Database/MySqlConnection.hpp"
#include "Server/Auth/AuthSession.hpp"
#include "Server/Auth/Auth.hpp"
#include "Libraries/BCrypt/BCrypt.hpp"

#include <string>

AuthPacketHandler::AuthPacketHandler(std::shared_ptr<AuthSession> &session)
	: _session(session)
{
	// Construct
	InitializeHandlers();
}

AuthPacketHandler::~AuthPacketHandler()
{
	// Destruct
}

bool AuthPacketHandler::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (auth_client_packets) packet.getOpCode();
	auto it = _handlers.find(opCode);

	if (it == _handlers.end()) {
		AuthLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	AuthPacketHandlerFunc func = it->second;
	(this->*func)(packet);

	return true;
}

template <class T>
void AuthPacketHandler::SendPacket(T pkt)
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

void AuthPacketHandler::SendPacket(PacketBuffer &buf, std::size_t size)
{
	if (!_session->IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), size);
		_session->QueuePacket(std::move(buffer));
	}
}

void AuthPacketHandler::ProcessAuthentication()
{
	_session->getGameAccount()->setLastIp(_session->GetRemoteIPAddress().to_string());
	_session->getGameAccount()->setLastLogin((int) time(nullptr));
	// Session ID as Game Account Id.
	_session->getSessionData()->setAuthCode(_session->getGameAccount()->getId());

	Respond_AC_ACCEPT_LOGIN();
}

bool AuthPacketHandler::VerifyCredentialsBCrypt(std::string username, std::string password)
{
	std::string query = "SELECT * FROM game_account WHERE username = ?";
	auto sql = AuthServer->MySQLBorrow();
	bool ret = false;

	try {
		sql::PreparedStatement *pstmt = sql->sql_connection->prepareStatement(query);
		pstmt->setString(1, username);
		sql::ResultSet *res = pstmt->executeQuery();

		if (res != nullptr && res->next()
		    && BCrypt::validatePassword(password, res->getString("password"))) {
			/**
			 * Create Game Account Data
			 */
			_session->setGameAccount(std::forward<std::shared_ptr<GameAccount>>(std::make_shared<GameAccount>(res)));
			ret = true;
		}

		delete res;
		delete pstmt;
	} catch (sql::SQLException &e) {
		AuthLog->error("AuthSession::VerifyCredentialsBCrypt: {}", e.what());
	}

	AuthServer->MySQLUnborrow(sql);

	return ret;
}

bool AuthPacketHandler::VerifyCredentialsPlainText(std::string username, std::string password)
{
	std::string query = "SELECT * FROM game_account WHERE username = ? AND password = ?";
	auto sql = AuthServer->MySQLBorrow();
	bool ret = false;

	try {
		sql::PreparedStatement *pstmt = sql->sql_connection->prepareStatement(query);
		pstmt->setString(1, username);
		pstmt->setString(2, password);
		sql::ResultSet *res = pstmt->executeQuery();

		if (res != nullptr && res->next()) {
			/**
			 * Create Game Account Data
			 */
			_session->setGameAccount(std::forward<std::shared_ptr<GameAccount>>(std::make_shared<GameAccount>(res)));
			ret = true;
		}

		delete res;
		delete pstmt;
	} catch (sql::SQLException &e) {
		AuthLog->error("AuthSession::VerifyCredentials: {}", e.what());
	}

	AuthServer->MySQLUnborrow(sql);

	return ret;
}

bool AuthPacketHandler::CheckIfAlreadyConnected(uint32_t id)
{
	std::shared_ptr<AuthSession> session = AuthServer->getOnlineAccount(id);

	// Check if session already exists.
	if (session != nullptr) {
		AuthServer->removeOnlineAccount(id);
		return true;
	}

	AuthServer->addOnlineAccount(id, _session);
	return false;
}

void AuthPacketHandler::Handle_CA_LOGIN(PacketBuffer &packet)
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
		authenticated = VerifyCredentialsPlainText(pkt.username, pkt.password);
		break;
	case PASS_HASH_BCRYPT:
		authenticated = VerifyCredentialsBCrypt(pkt.username, pkt.password);
		break;
	}

	if (authenticated) {
		if (_session->getGameAccount() == nullptr) {
			AuthLog->error("nullptr gameaccount!?!?!");
			return;
		}
		AuthLog->info("Authentication of account '{}' granted.", pkt.username);

		if (CheckIfAlreadyConnected(_session->getGameAccount()->getId())) {
			Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_SESSION_CONNECTED);
			AuthLog->info("Refused connection for account '{}', already online.", pkt.username);
			_session->DelayedCloseSocket();
		} else {
			ProcessAuthentication();
		}
	} else {
		Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Rejected unknown account '{}' or incorrect password.", pkt.username);
	}
}

void AuthPacketHandler::Handle_CA_REQ_HASH(PacketBuffer &/*packet*/)
{
	PACKET_CA_REQ_HASH pkt;

}

void AuthPacketHandler::Handle_CA_LOGIN2(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN2 pkt;
}

void AuthPacketHandler::Handle_CA_LOGIN3(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN3 pkt;

}

void AuthPacketHandler::Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &/*packet*/)
{
	PACKET_CA_CONNECT_INFO_CHANGED pkt;

}

void AuthPacketHandler::Handle_CA_EXE_HASHCHECK(PacketBuffer &/*packet*/)
{
	PACKET_CA_EXE_HASHCHECK pkt;

}

void AuthPacketHandler::Handle_CA_LOGIN_PCBANG(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_PCBANG pkt;

}

void AuthPacketHandler::Handle_CA_LOGIN4(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN4 pkt;

}

void AuthPacketHandler::Handle_CA_LOGIN_HAN(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_HAN pkt;

}

void AuthPacketHandler::Handle_CA_SSO_LOGIN_REQ(PacketBuffer &/*packet*/)
{
	PACKET_CA_SSO_LOGIN_REQ pkt;

}

void AuthPacketHandler::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_OTP pkt;

}

/**
 * Auth To Client
 */
void AuthPacketHandler::Respond_AC_ACCEPT_LOGIN()
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

void AuthPacketHandler::Respond_AC_REFUSE_LOGIN(login_error_codes error_code)
{
	PACKET_AC_REFUSE_LOGIN pkt;
	pkt.error_code = (uint8_t) error_code;
	SendPacket(pkt);
}

void AuthPacketHandler::Respond_SC_NOTIFY_BAN()
{

}

void AuthPacketHandler::Respond_AC_ACK_HASH()
{

}

void AuthPacketHandler::Respond_AC_REFUSE_LOGIN_R2()
{

}

void AuthPacketHandler::Respond_CA_CHARSERVERCONNECT()
{

}

void AuthPacketHandler::InitializeHandlers()
{
	_handlers.insert(std::make_pair(CA_LOGIN, &AuthPacketHandler::Handle_CA_LOGIN));
	_handlers.insert(std::make_pair(CA_REQ_HASH, &AuthPacketHandler::Handle_CA_REQ_HASH));
	_handlers.insert(std::make_pair(CA_LOGIN2, &AuthPacketHandler::Handle_CA_LOGIN2));
	_handlers.insert(std::make_pair(CA_LOGIN3, &AuthPacketHandler::Handle_CA_LOGIN3));
	_handlers.insert(std::make_pair(CA_CONNECT_INFO_CHANGED, &AuthPacketHandler::Handle_CA_CONNECT_INFO_CHANGED));
	_handlers.insert(std::make_pair(CA_EXE_HASHCHECK, &AuthPacketHandler::Handle_CA_EXE_HASHCHECK));
	_handlers.insert(std::make_pair(CA_LOGIN_PCBANG, &AuthPacketHandler::Handle_CA_LOGIN_PCBANG));
	_handlers.insert(std::make_pair(CA_LOGIN4, &AuthPacketHandler::Handle_CA_LOGIN4));
	_handlers.insert(std::make_pair(CA_LOGIN_HAN, &AuthPacketHandler::Handle_CA_LOGIN_HAN));
	_handlers.insert(std::make_pair(CA_SSO_LOGIN_REQ, &AuthPacketHandler::Handle_CA_SSO_LOGIN_REQ));
	_handlers.insert(std::make_pair(CA_LOGIN_OTP, &AuthPacketHandler::Handle_CA_LOGIN_OTP));
}

const AuthHandlerMap &AuthPacketHandler::getHandlers() const
{
	return _handlers;
}
