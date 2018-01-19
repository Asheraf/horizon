//
//  AuthSession.cpp
//  Horizon
//
//  Created by SagunKho on 18/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#include "AuthSession.hpp"

#include "MySqlConnection.hpp"
#include "Auth.hpp"
#include <random>
#include <algorithm>

AuthSession::AuthSession(tcp::socket &&socket)
: Socket(std::move(socket))
{
	InitHandlers();

	session_data = std::make_unique<SessionData>();
	session_data->setAuthCode(rand() + 1);
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

void AuthSession::Handle_CA_LOGIN(PacketBuffer &packet)
{
	PACKET_CA_LOGIN pkt;

	packet >> pkt;

	AuthLog->info("Authentication of account '{'{}' requested.", pkt.op_code, pkt.username, pkt.username);

	if (!VerifyCredentials(pkt.username, pkt.password))
		return;
}

void AuthSession::ProcessAuthentication()
{
	this->game_account->setLastIp(GetRemoteIPAddress().to_string());
	this->game_account->setLastLogin((int) time(NULL));

	Respond_AC_ACCEPT_LOGIN();

	AuthLog->info("Authenticated.");
}

bool AuthSession::VerifyCredentials(std::string username, std::string password)
{
	std::string query = "SELECT * FROM game_account WHERE username = ? AND password = ?";
	auto sql = AuthServer->MySQLBorrow();
	bool ret = true;

	try {
		sql::PreparedStatement *pstmt = sql->sql_connection->prepareStatement(query);
		pstmt->setString(1, username);
		pstmt->setString(2, password);
		sql::ResultSet *res = pstmt->executeQuery();

		if (res != nullptr && res->next()) {
			if ((ret = CheckIfAlreadyConnected(res->getUInt64("id")))) {
				AuthLog->info("Refused connection for account '{}', already online.", username);
			} else {
				this->game_account = std::make_unique<GameAccount>(res);
				ProcessAuthentication();
			}
		} else {
			Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
			AuthLog->info("Refused connection for unknown account '{}' or incorrect password.", username);
			ret = false;
		}

		delete res;
		delete pstmt;
	} catch (sql::SQLException &e) {
		AuthLog->error("AuthSession::VerifyCredentials: {}", e.what());
	}

	AuthServer->MySQLUnborrow(sql);

	return ret;
};

bool AuthSession::CheckIfAlreadyConnected(uint64_t id)
{
	std::shared_ptr<OnlineListType> onlineList = AuthServer->getAccountOnlineList();
	auto online_index = std::find(onlineList->begin(), onlineList->end(), id);

	// Check if session already exists.
	if (online_index != onlineList->end()) {
		onlineList->erase(online_index);
		Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_SESSION_CONNECTED);
		return true;
	}

	onlineList->push_back(id);
	return false;
}

void AuthSession::Handle_CA_REQ_HASH(PacketBuffer &packet)
{
	PACKET_CA_REQ_HASH pkt;

}

void AuthSession::Handle_CA_LOGIN2(PacketBuffer &packet)
{
	PACKET_CA_LOGIN2 pkt;
}

void AuthSession::Handle_CA_LOGIN3(PacketBuffer &packet)
{
	PACKET_CA_LOGIN3 pkt;

}

void AuthSession::Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &packet)
{
	PACKET_CA_CONNECT_INFO_CHANGED pkt;

}

void AuthSession::Handle_CA_EXE_HASHCHECK(PacketBuffer &packet)
{
	PACKET_CA_EXE_HASHCHECK pkt;

}

void AuthSession::Handle_CA_LOGIN_PCBANG(PacketBuffer &packet)
{
	PACKET_CA_LOGIN_PCBANG pkt;

}

void AuthSession::Handle_CA_LOGIN4(PacketBuffer &packet)
{
	PACKET_CA_LOGIN4 pkt;

}

void AuthSession::Handle_CA_LOGIN_HAN(PacketBuffer &packet)
{
	PACKET_CA_LOGIN_HAN pkt;

}

void AuthSession::Handle_CA_SSO_LOGIN_REQ(PacketBuffer &packet)
{
	PACKET_CA_SSO_LOGIN_REQ pkt;

}

void AuthSession::Handle_CA_LOGIN_OTP(PacketBuffer &packet)
{
	PACKET_CA_LOGIN_OTP pkt;

}

/**
 * Auth To Client
 */
void AuthSession::Respond_AC_ACCEPT_LOGIN()
{
	PACKET_AC_ACCEPT_LOGIN pkt;
	PacketBuffer buf;
//
//	buf << pkt.op_code << pkt.packet_len << pkt.auth_code << pkt.aid user_level;        ///< User level
//	uint32 last_login_ip;     ///< Last login IP
//	char last_login_time[26]; ///< Last login timestamp
//	uint8 sex;                ///< Account sex
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
