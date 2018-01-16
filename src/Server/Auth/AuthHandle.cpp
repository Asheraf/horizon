//
// Created by SagunKho on 25/06/2017.
//

#include "AuthHandle.h"
#include "AuthSession.hpp"
#include "Core/Logging/Logger.hpp"
#include "Utilities/Tokenizer.h"
#include "MySqlConnection.h"

AuthHandle::AuthHandle()
{
	InitHandlers();
}

AuthHandle::~AuthHandle()
{

}

bool AuthHandle::HandleIncomingPacket(AuthSession *session, PacketBuffer &packet)
{
	uint16_t opCode = packet.getOpCode();
	AuthPacketHandler func = nullptr;

	if (opCode < MIN_AUTH_PACKETS || opCode > MAX_AUTH_PACKETS) {
		AuthLog->trace("Unknown packet with ID received: {0:x}", opCode);
		return false;
	}

	/* Call the function handling */
	if ((func = handlers[opCode]) != nullptr)
		(this->*func)(packet);

	return true;
}

void AuthHandle::HandleLoginRequest(PacketBuffer &packet)
{
	PACKET_CA_LOGIN pkt;

	packet >> pkt.op_code;
	packet >> pkt.version;
	packet.read(reinterpret_cast<uint8_t *>(pkt.username), sizeof(pkt.username));
	packet.read(reinterpret_cast<uint8_t *>(pkt.password), sizeof(pkt.password));
	packet >> pkt.client_type;

	AuthLog->info("Authentication of account {} requested.", pkt.username);

	// Check MySQL Stuff here.
}

void AuthHandle::InitHandlers()
{
	handlers.insert(std::make_pair(CA_LOGIN, &AuthHandle::HandleLoginRequest));
}


