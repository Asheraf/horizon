//
// Created by SagunKho on 28/01/2018.
//

#ifndef HORIZON_AUTH_INTERAUTHPACKETHANDLER_HPP
#define HORIZON_AUTH_INTERAUTHPACKETHANDLER_HPP

#include "Horizon.hpp"
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
class InterAuthPacketHandler
{
public:
	InterAuthPacketHandler(std::shared_ptr<AuthSession> session);
	~InterAuthPacketHandler();

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
	void Handle_CONNECT_RESPONSE(PacketBuffer &buf);
	/**
	 * Response
	 */
	void Respond_CONNECT_AUTH();

private:
	std::shared_ptr<AuthSession> _session;
	PacketHandlerMap _handlers;
};
}
}

#endif //HORIZON_AUTH_INTERAUTHPACKETHANDLER_HPP
