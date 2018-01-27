//
// Created by SagunKho on 27/01/2018.
//

#include "AuthPacketHandler20170315.hpp"
#include "Core/Logging/Logger.hpp"

AuthPacketHandler20170315::AuthPacketHandler20170315(std::shared_ptr<AuthSession> &session)
: AuthPacketHandler(session)
{
	InitializeHandlers();
}

AuthPacketHandler20170315::~AuthPacketHandler20170315()
{
}

void AuthPacketHandler20170315::Respond_AC_ACCEPT_LOGIN()
{
	// Override common handler.
	AuthLog->info("Overloaded!");
	Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
}

void AuthPacketHandler20170315::InitializeHandlers()
{
	AuthPacketHandler::InitializeHandlers();
}