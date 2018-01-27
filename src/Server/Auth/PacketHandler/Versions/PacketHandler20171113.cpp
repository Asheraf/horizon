//
// Created by SagunKho on 27/01/2018.
//

#include "PacketHandler20171113.hpp"

Horizon::Auth::PacketHandler20171113::PacketHandler20171113(std::shared_ptr<AuthSession> session)
: PacketHandler(session)
{
	InitializeHandlers();
}

Horizon::Auth::PacketHandler20171113::~PacketHandler20171113()
{
}

void Horizon::Auth::PacketHandler20171113::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{

}

void Horizon::Auth::PacketHandler20171113::InitializeHandlers()
{
	PacketHandler::InitializeHandlers();
}