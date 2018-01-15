//
// Created by SagunKho on 25/06/2017.
//

#include "AuthHandle.h"
#include "AuthSession.hpp"
#include "Core/Logging/Logger.hpp"
#include "Utilities/Tokenizer.h"


AuthHandle::AuthHandle()
{

}

AuthHandle::~AuthHandle()
{

}

bool AuthHandle::HandleIncomingPacket(AuthSession *session, PacketBuffer &packet)
{
	switch ((enum AuthPackets) packet.getOpCode())
	{
	case CA_LOGIN:
		{
			PACKET_CA_LOGIN pkt;

			packet >> pkt.op_code;
			packet >> pkt.version;
			packet.read(reinterpret_cast<uint8_t *>(pkt.username), sizeof(pkt.username));
			packet.read(reinterpret_cast<uint8_t *>(pkt.password), sizeof(pkt.password));
			packet >> pkt.client_type;

			AuthLog->info("Authentication of account {} requested.", pkt.username);

			if (!HandleLoginRequest(session, &pkt)) {
				AuthLog->warn("Login request could not be handled!");
				return false;
			}
		}
		break;
	default: // well we don't handle this, lets just trace and ignore it.
		AuthLog->trace("Unknown packet with ID received: {0:x}", packet.getOpCode());
		return false;
	}

	return true;
}

bool AuthHandle::HandleLoginRequest(AuthSession *session, PACKET_CA_LOGIN *pkt)
{
	PACKET_AC_REFUSE_LOGIN_R2 refuse; // For refusal
	std::string username = pkt->username;


	return true;
}
