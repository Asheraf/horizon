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

#ifndef HORIZON_AUTH_ZERO_20171123_PACKETHANDLER_HPP
#define HORIZON_AUTH_ZERO_20171123_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Zero/20171123/Structs/PACKET_AC_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/Zero/20171113/PacketHandlerZero20171113.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerZero20171123 : public PacketHandlerZero20171113
{
public:
	PacketHandlerZero20171123(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerZero20171123();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_AUTH_Zero_20171123_PACKETHANDLER_HPP */
