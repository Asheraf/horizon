//
// Created by SagunKho on 27/01/2018.
//

#ifndef HORIZON_AUTH_PACKETHANDLER_HPP
#define HORIZON_AUTH_PACKETHANDLER_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Common/Packet.hpp"
#include "Packets.hpp"

#include <memory>
#include <unordered_map>
#include <boost/function.hpp>
#include <future>
#include <boost/system/error_code.hpp>

namespace Horizon
{
namespace Auth
{
class AuthSession;

class PacketHandler
{
public:
	explicit PacketHandler(std::shared_ptr<AuthSession> session);
	virtual ~PacketHandler();

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
	virtual bool ValidateSessionData(uint32_t id, uint32_t client_version, uint8_t client_type);
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
	const PacketHandlerMap &getHandlers() const;

protected:
	std::shared_ptr<AuthSession> _session;
	PacketHandlerMap _handlers;
};
}
}

#endif //HORIZON_AUTH_PACKETHANDLER_HPP
