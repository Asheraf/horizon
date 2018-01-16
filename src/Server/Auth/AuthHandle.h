//
// Created by SagunKho on 25/06/2017.
//

#ifndef HORIZON_AUTHHANDLE_H
#define HORIZON_AUTHHANDLE_H

#include "AuthPackets.h"
#include "Auth.hpp"

#include <boost/asio.hpp>

class AuthSession;

typedef void (AuthHandle::*AuthPacketHandler) (PacketBuffer &packet);

class AuthHandle
{
public:
	AuthHandle();
	~AuthHandle();
	bool HandleIncomingPacket(AuthSession *session, PacketBuffer &packet);
	void HandleLoginRequest(PacketBuffer &packet);
	void InitHandlers();

private:
	std::unordered_map<uint16_t, AuthPacketHandler> handlers;
};


#endif //HORIZON_AUTHHANDLE_H
