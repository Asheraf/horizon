//
// Created by SagunKho on 27/01/2018.
//

#include <Core/Logging/Logger.hpp>
#include <boost/bind.hpp>
#include "PacketHandler20171113.hpp"

Horizon::Auth::PacketHandler20171113::PacketHandler20171113(std::shared_ptr<AuthSession> session)
: PacketHandler20170315(session)
{
	InitializeHandlers();
}

Horizon::Auth::PacketHandler20171113::~PacketHandler20171113()
{
}

void Horizon::Auth::PacketHandler20171113::Handle_CA_LOGIN_OTP(PacketBuffer &/*packet*/)
{

}

void Horizon::Auth::PacketHandler20171113::Handle_Poly(PacketBuffer &buf)
{
	AuthLog->info("20171113 Poly Overloaded!");
}

void Horizon::Auth::PacketHandler20171113::InitializeHandlers()
{
	PacketHandler20170315::InitializeHandlers();
	_handlers.erase(CA_LOGIN);
	_handlers.insert(std::make_pair(CA_LOGIN, boost::bind(&PacketHandler::Handle_CA_LOGIN, this, boost::placeholders::_1)));
}