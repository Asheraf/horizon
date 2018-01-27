//
// Created by SagunKho on 27/01/2018.
//

#include "AuthPacketHandler20171113.hpp"

AuthPacketHandler20171113::AuthPacketHandler20171113(std::shared_ptr<AuthSession> session)
: AuthPacketHandler(session)
{
	InitializeHandlers();
}

AuthPacketHandler20171113::~AuthPacketHandler20171113()
{
}

void AuthPacketHandler20171113::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{

}

void AuthPacketHandler20171113::InitializeHandlers()
{
	AuthPacketHandler::InitializeHandlers();
}