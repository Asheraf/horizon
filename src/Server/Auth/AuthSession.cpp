/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "AuthSession.hpp"

#include "MySqlConnection.hpp"
#include "Auth.hpp"
#include "Networking/Buffer/ByteConverter.hpp"
#include <Libraries/BCrypt/BCrypt.hpp>
#include <Server/Common/Utilities/Utilities.hpp>

#include <random>
#include <memory>

AuthSession::AuthSession(tcp::socket &&socket)
: Socket(std::move(socket))
{
	InitHandlers();

	session_data = std::make_unique<SessionData>();
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

template <class T>
void AuthSession::SendPacket(T pkt)
{
	PacketBuffer buf;

	buf << pkt;

	if (!IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), sizeof(T));
		QueuePacket(std::move(buffer));
	}
}

void AuthSession::SendPacket(PacketBuffer &buf, std::size_t size)
{
	if (!IsOpen())
		return;

	if (!buf.empty()) {
		MessageBuffer buffer;
		buffer.Write(buf.contents(), size);
		QueuePacket(std::move(buffer));
	}
}

void AuthSession::ReadHandler()
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

bool AuthSession::HandleIncomingPacket(PacketBuffer &packet)
{
	auto opCode = (auth_client_packets) packet.getOpCode();
	AuthPacketHandler func = nullptr;

	/* Call the function handling */
	if ((func = handlers[opCode]) == nullptr) {
		AuthLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	(this->*func)(packet);

	return true;
}

void AuthSession::ProcessAuthentication()
{
	this->game_account->setLastIp(GetRemoteIPAddress().to_string());
	this->game_account->setLastLogin((int) time(nullptr));
	// Session ID as Game Account Id.
	this->session_data->setAuthCode(this->game_account->getId());

	Respond_AC_ACCEPT_LOGIN();
}

bool AuthSession::VerifyCredentialsBCrypt(std::string username, std::string password)
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
			this->game_account = std::make_unique<GameAccount>(res);
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

bool AuthSession::VerifyCredentialsPlainText(std::string username, std::string password)
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
			this->game_account = std::make_unique<GameAccount>(res);
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

bool AuthSession::CheckIfAlreadyConnected(uint32_t id)
{
	std::shared_ptr<AuthSession> session = AuthServer->getOnlineAccount(id);

	// Check if session already exists.
	if (session != nullptr) {
		AuthServer->removeOnlineAccount(id);
		return true;
	}

	AuthServer->addOnlineAccount(id, shared_from_this());
	return false;
}

void AuthSession::Handle_CA_LOGIN(PacketBuffer &packet)
{
	PACKET_CA_LOGIN pkt;
	bool authenticated = false;

	packet >> pkt;

	AuthLog->info("Authentication of account '{}' requested.", pkt.username);

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
		AuthLog->info("Authentication of account '{}' granted.", pkt.username);

		if (CheckIfAlreadyConnected(this->game_account->getId())) {
			Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_SESSION_CONNECTED);
			AuthLog->info("Refused connection for account '{}', already online.", pkt.username);
			DelayedCloseSocket();
		} else {
			ProcessAuthentication();
		}
	} else {
		Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
		AuthLog->info("Rejected unknown account '{}' or incorrect password.", pkt.username);
	}
}

void AuthSession::Handle_CA_REQ_HASH(PacketBuffer &/*packet*/)
{
	PACKET_CA_REQ_HASH pkt;

}

void AuthSession::Handle_CA_LOGIN2(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN2 pkt;
}

void AuthSession::Handle_CA_LOGIN3(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN3 pkt;

}

void AuthSession::Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &/*packet*/)
{
	PACKET_CA_CONNECT_INFO_CHANGED pkt;

}

void AuthSession::Handle_CA_EXE_HASHCHECK(PacketBuffer &/*packet*/)
{
	PACKET_CA_EXE_HASHCHECK pkt;

}

void AuthSession::Handle_CA_LOGIN_PCBANG(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_PCBANG pkt;

}

void AuthSession::Handle_CA_LOGIN4(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN4 pkt;

}

void AuthSession::Handle_CA_LOGIN_HAN(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_HAN pkt;

}

void AuthSession::Handle_CA_SSO_LOGIN_REQ(PacketBuffer &/*packet*/)
{
	PACKET_CA_SSO_LOGIN_REQ pkt;

}

void AuthSession::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{
	PACKET_CA_LOGIN_OTP pkt;

}

/**
 * Auth To Client
 */
void AuthSession::Respond_AC_ACCEPT_LOGIN()
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
	pkt->auth_code = this->session_data->getAuthCode();
	pkt->aid = this->game_account->getId();
	pkt->user_level = 1;
	pkt->last_login_ip = 0; // not used anymore.
	memset(pkt->last_login_time, '\0', sizeof(pkt->last_login_time)); // Not used anymore

	pkt->sex = (uint8_t) (this->game_account->getGender() == ACCOUNT_MALE ? ACCOUNT_MALE : ACCOUNT_FEMALE);

	for (int i = 0; i < max_servers; ++i) {
		std::shared_ptr<character_server_data> chr;

		if ((chr = AuthServer->getCharacterServer(i + 1)) == nullptr)
			continue;

		server_list[i].ip = inet_addr(chr->ip_address.c_str());
		server_list[i].port = chr->port;
		strncpy(server_list[i].name, chr->name.c_str(), sizeof(server_list[i].name));
		server_list[i].type = (uint16_t) chr->server_type;
		server_list[i].is_new = (uint16_t) (chr->isNew ? 1 : 0);
		server_list[i].usercount = 88;
	} // 1677764800

	buf.append<PACKET_AC_ACCEPT_LOGIN, PACKET_AC_ACCEPT_LOGIN::character_server_list>
		(pkt, sizeof(*pkt), server_list, max_servers);

	SendPacket(buf, (std::size_t) pkt->packet_len);

	delete[] server_list;
	delete pkt;
}

void AuthSession::Respond_AC_REFUSE_LOGIN(login_error_codes error_code)
{
	PACKET_AC_REFUSE_LOGIN pkt;
	pkt.error_code = (uint8_t) error_code;
	SendPacket<PACKET_AC_REFUSE_LOGIN>(pkt);
}

void AuthSession::Respond_SC_NOTIFY_BAN()
{

}

void AuthSession::Respond_AC_ACK_HASH()
{

}

void AuthSession::Respond_AC_REFUSE_LOGIN_R2()
{

}

void AuthSession::Respond_CA_CHARSERVERCONNECT()
{

}

void AuthSession::InitHandlers()
{
	/**
	 * Receivable Packets
	 */
	handlers.insert(std::make_pair(CA_LOGIN, &AuthSession::Handle_CA_LOGIN));
	handlers.insert(std::make_pair(CA_REQ_HASH, &AuthSession::Handle_CA_REQ_HASH));
	handlers.insert(std::make_pair(CA_LOGIN2, &AuthSession::Handle_CA_LOGIN2));
	handlers.insert(std::make_pair(CA_LOGIN3, &AuthSession::Handle_CA_LOGIN3));
	handlers.insert(std::make_pair(CA_CONNECT_INFO_CHANGED, &AuthSession::Handle_CA_CONNECT_INFO_CHANGED));
	handlers.insert(std::make_pair(CA_EXE_HASHCHECK, &AuthSession::Handle_CA_EXE_HASHCHECK));
	handlers.insert(std::make_pair(CA_LOGIN_PCBANG, &AuthSession::Handle_CA_LOGIN_PCBANG));
	handlers.insert(std::make_pair(CA_LOGIN4, &AuthSession::Handle_CA_LOGIN4));
	handlers.insert(std::make_pair(CA_LOGIN_HAN, &AuthSession::Handle_CA_LOGIN_HAN));
	handlers.insert(std::make_pair(CA_SSO_LOGIN_REQ, &AuthSession::Handle_CA_SSO_LOGIN_REQ));
	handlers.insert(std::make_pair(CA_LOGIN_OTP, &AuthSession::Handle_CA_LOGIN_OTP));
}
