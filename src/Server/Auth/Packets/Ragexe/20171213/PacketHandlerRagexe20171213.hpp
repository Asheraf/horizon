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

#ifndef HORIZON_AUTH_RAGEXE_20171213_PACKETHANDLER_HPP
#define HORIZON_AUTH_RAGEXE_20171213_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/Structs/PACKET_AC_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/20171115/PacketHandlerRagexe20171115.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerRagexe20171213 : public PacketHandlerRagexe20171115
{
public:
	PacketHandlerRagexe20171213(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerRagexe20171213();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_AUTH_Ragexe_20171213_PACKETHANDLER_HPP */
