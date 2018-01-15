//
// Created by SagunKho on 25/06/2017.
//

#ifndef HORIZON_AUTHHANDLE_H
#define HORIZON_AUTHHANDLE_H

#include "AuthPackets.h"
#include "Auth.hpp"

#include <boost/asio.hpp>

class AuthSession;

class AuthHandle
{
public:
	AuthHandle();
	~AuthHandle();
	bool HandleIncomingPacket(AuthSession *session, PacketBuffer &packet);
	bool HandleLoginRequest(AuthSession *session, PACKET_CA_LOGIN *pkt);

};


#endif //HORIZON_AUTHHANDLE_H
