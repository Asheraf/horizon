//
// Created by SagunKho on 28/01/2018.
//

#ifndef HORIZON_AUTH_INTERPACKETHANDLER_HPP
#define HORIZON_AUTH_INTERPACKETHANDLER_HPP

#include "Horizon.hpp"
#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Packet.hpp"

#include <boost/function.hpp>
#include <memory>
#include <unordered_map>

class PacketBuffer;

namespace Horizon
{
namespace Auth
{
class AuthSession;
class InterPacketHandler
{
public:
	InterPacketHandler(std::shared_ptr<AuthSession> session);
	~InterPacketHandler();

	template <class T>
	void SendPacket(T pkt);

	void SendPacket(PacketBuffer &buf, std::size_t size);
	/**
	 *
	 */
	bool HandleIncomingPacket(PacketBuffer &packet);

	virtual void InitializeHandlers();
	const PacketHandlerMap &getHandlers() const;

	/**
	 * Handlers
	 */
	void Handle_ACK_RECEIVED(PacketBuffer &buf);
	void Handle_CONNECT_INIT(PacketBuffer &buf);
	/**
	 * Response
	 */
	void Respond_CONNECT_AUTH();
	void Respond_SESSION_SET(SessionData &session_data);
	void Respond_SESSION_DEL(uint32_t id);

private:
	std::shared_ptr<AuthSession> _session;
	PacketHandlerMap _handlers;
};
}
}

#endif //HORIZON_AUTH_INTERPACKETHANDLER_HPP
