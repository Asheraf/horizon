//
//  AuthSession.hpp
//  Horizon
//
//  Created by SagunKho on 18/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#ifndef HORIZON_AUTHSESSION_HPP
#define HORIZON_AUTHSESSION_HPP

#include "Core/Networking/Socket.hpp"
#include "Core/Networking/Buffer/MessageBuffer.hpp"
#include "Common/Horizon.hpp"

#include "Server/Packet.hpp"
#include "AuthPackets.hpp"

#include <cstdio>
#include <boost/asio/ip/tcp.hpp>
#include <Server/Common/Models/GameAccount.hpp>
#include <Server/Common/Models/SessionData.hpp>

using boost::asio::ip::tcp;

class AuthSession : public Socket<AuthSession>
{
	typedef void (AuthSession::*AuthPacketHandler) (PacketBuffer &packet);
	friend class AuthMain;
	typedef Socket<AuthSession> AuthSocket;
public:
	AuthSession(tcp::socket &&socket);
	~AuthSession() { }

	void Start() override;
	bool Update() override;

	bool HandleIncomingPacket(PacketBuffer &packet);

	template <class T>
	void SendPacket(T pkt);

	/**
	 * Client To Auth
	 */
	void Handle_CA_LOGIN(PacketBuffer &packet);
	void Handle_CA_REQ_HASH(PacketBuffer &packet);
	void Handle_CA_LOGIN2(PacketBuffer &packet);
	void Handle_CA_LOGIN3(PacketBuffer &packet);
	void Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &packet);
	void Handle_CA_EXE_HASHCHECK(PacketBuffer &packet);
	void Handle_CA_LOGIN_PCBANG(PacketBuffer &packet);
	void Handle_CA_LOGIN4(PacketBuffer &packet);
	void Handle_CA_LOGIN_HAN(PacketBuffer &packet);
	void Handle_CA_SSO_LOGIN_REQ(PacketBuffer &packet);
	void Handle_CA_LOGIN_OTP(PacketBuffer &packet);

	/**
	 * Auth To Client
	 */
	void Respond_AC_ACCEPT_LOGIN();
	void Respond_AC_REFUSE_LOGIN(login_error_codes error_code);
	void Respond_SC_NOTIFY_BAN();
	void Respond_AC_ACK_HASH();
	void Respond_AC_REFUSE_LOGIN_R2();
	void Respond_CA_CHARSERVERCONNECT();

	bool VerifyCredentialsBCrypt(std::string username, std::string password);
	bool VerifyCredentialsPlainText(std::string username, std::string password);
	bool CheckIfAlreadyConnected(uint64_t id);
	void ProcessAuthentication();
	void InitHandlers();

protected:
	void ReadHandler() override;
	void OnClose() override;
	std::unordered_map<uint16_t, AuthPacketHandler> handlers;

private:
	std::unique_ptr<GameAccount> game_account;
	std::unique_ptr<SessionData> session_data;
};

#endif /* HORIZON_AUTHSESSION_HPP */
