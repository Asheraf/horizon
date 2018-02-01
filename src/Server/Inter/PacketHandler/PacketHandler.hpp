//
// Created by SagunKho on 29/01/2018.
//

#ifndef HORIZON_INTER_PACKETHANDLER_HPP
#define HORIZON_INTER_PACKETHANDLER_HPP

#include "Server/Common/Models/SessionData.hpp"
#include "Server/Common/PacketBuffer.hpp"
#include "Server/Common/Base/PacketHandler/PacketHandler.hpp"

#include <cstdint>
#include <memory>

class PacketBuffer;

namespace Horizon
{
namespace Inter
{
class Session;
class PacketHandler : public Horizon::Base::PacketHandler<Session>
{
public:
	PacketHandler(std::shared_ptr<Session> session);
	~PacketHandler();

	virtual void InitializeHandlers() override;
	/**
	 * Handlers
	 */
	void Handle_INTER_CONNECT_AUTH(PacketBuffer &buf);
	void Handle_INTER_SESSION_GET(PacketBuffer &buf);
	void Handle_INTER_SESSION_SET(PacketBuffer &buf);
	void Handle_INTER_SESSION_DEL(PacketBuffer &buf);
	void Handle_INTER_SESSION_REQ(PacketBuffer &buf);
	/**
	 * Response
	 */
	void Respond_INTER_ACK_RECEIVED(uint16_t packet_id, uint8_t response);
	void Respond_INTER_CONNECT_INIT();
};
}
}

#endif //HORIZON_INTER_PACKETHANDLER_HPP
