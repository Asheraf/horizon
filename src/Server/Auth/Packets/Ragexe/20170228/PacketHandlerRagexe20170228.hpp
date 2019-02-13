/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_AUTH_RAGEXE_20170228_PACKETHANDLER_HPP
#define HORIZON_AUTH_RAGEXE_20170228_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Ragexe/20170228/Structs/PACKET_AC_ACCEPT_LOGIN.hpp"
#include "Server/Auth/Packets/PacketHandler.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerRagexe20170228 : public PacketHandler
{
public:
	PacketHandlerRagexe20170228(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerRagexe20170228();

	virtual void initialize_handlers() override;

	virtual void Send_AC_ACCEPT_LOGIN() override;

};
}
}

#endif /* HORIZON_AUTH_Ragexe_20170228_PACKETHANDLER_HPP */
