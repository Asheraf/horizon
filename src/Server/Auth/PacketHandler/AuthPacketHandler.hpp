//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_AUTHPACKETHANDLER_HPP
#define HORIZON_AUTHPACKETHANDLER_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Packet.hpp"
#include "AuthPackets.hpp"

#include <memory>
#include <unordered_map>

class AuthSession;
class AuthPacketHandler;

typedef void (AuthPacketHandler::*AuthPacketHandlerFunc) (PacketBuffer &pkt);
typedef std::unordered_map<uint16_t, AuthPacketHandlerFunc> AuthHandlerMap;

class AuthPacketHandler
{
public:
	explicit AuthPacketHandler(std::shared_ptr<AuthSession> &session);
	virtual ~AuthPacketHandler();

	template <class T>
	void SendPacket(T pkt);

	void SendPacket(PacketBuffer &buf, std::size_t size);
	/**
	 *
	 */
	bool HandleIncomingPacket(PacketBuffer &packet);
	/**
	 *
	 */
	virtual bool VerifyCredentialsBCrypt(std::string username, std::string password);
	virtual bool VerifyCredentialsPlainText(std::string username, std::string password);
	virtual bool CheckIfAlreadyConnected(uint32_t id);
	virtual void ProcessAuthentication();

	/**
	 * Client To Auth
	 */
	virtual void Handle_CA_LOGIN(PacketBuffer &packet);
	virtual void Handle_CA_REQ_HASH(PacketBuffer &packet);
	virtual void Handle_CA_LOGIN2(PacketBuffer &packet);
	virtual void Handle_CA_LOGIN3(PacketBuffer &packet);
	virtual void Handle_CA_CONNECT_INFO_CHANGED(PacketBuffer &packet);
	virtual void Handle_CA_EXE_HASHCHECK(PacketBuffer &packet);
	virtual void Handle_CA_LOGIN_PCBANG(PacketBuffer &packet);
	virtual void Handle_CA_LOGIN4(PacketBuffer &packet);
	virtual void Handle_CA_LOGIN_HAN(PacketBuffer &packet);
	virtual void Handle_CA_SSO_LOGIN_REQ(PacketBuffer &packet);
	virtual void Handle_CA_LOGIN_OTP(PacketBuffer &packet);

	/**
	 * Auth To Client
	 */
	virtual void Respond_AC_ACCEPT_LOGIN();
	virtual void Respond_AC_REFUSE_LOGIN(login_error_codes error_code);
	virtual void Respond_SC_NOTIFY_BAN();
	virtual void Respond_AC_ACK_HASH();
	virtual void Respond_AC_REFUSE_LOGIN_R2();
	virtual void Respond_CA_CHARSERVERCONNECT();

	virtual void InitializeHandlers();
	const AuthHandlerMap &getHandlers() const;

private:
	std::shared_ptr<AuthSession> _session;
	AuthHandlerMap _handlers;
};

#endif //HORIZON_AUTHPACKETHANDLER_HPP
