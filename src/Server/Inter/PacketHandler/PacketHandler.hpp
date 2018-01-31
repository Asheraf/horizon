//
// Created by SagunKho on 29/01/2018.
//

#ifndef HORIZON_INTER_PACKETHANDLER_HPP
#define HORIZON_INTER_PACKETHANDLER_HPP

#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/Packet.hpp"
#include <cstdint>
#include <memory>

class PacketBuffer;

namespace Horizon
{
namespace Inter
{
class InterSession;
class PacketHandler
{
public:
	PacketHandler(std::shared_ptr<InterSession> session);
	~PacketHandler();

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
	void Handle_CONNECT_AUTH(PacketBuffer &buf);
	void Handle_SESSION_GET(PacketBuffer &buf);
	void Handle_SESSION_SET(PacketBuffer &buf);
	void Handle_SESSION_DEL(PacketBuffer &buf);
	/**
	 * Response
	 */
	void Respond_SESSION_SET(SessionData &session_data);
	void Respond_ACK_RECEIVED(uint16_t packet_id, uint8_t response);
	void Respond_CONNECT_INIT();

private:
	std::shared_ptr<InterSession> _session;
	PacketHandlerMap _handlers;
};
}
}

#endif //HORIZON_INTER_PACKETHANDLER_HPP
