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

#ifndef HORIZON_AUTH_ZERO_20180627_PACKETHANDLER_HPP
#define HORIZON_AUTH_ZERO_20180627_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Auth/Packets/Zero/20180627/Structs/PACKET_AC_REFUSE_LOGIN4.hpp"
#include "Server/Auth/Packets/Zero/20171123/PacketHandlerZero20171123.hpp"

namespace Horizon
{
namespace Auth
{

class AuthSocket;

class PacketHandlerZero20180627 : public PacketHandlerZero20171123
{
public:
	PacketHandlerZero20180627(std::shared_ptr<AuthSocket> socket);
	~PacketHandlerZero20180627();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_AUTH_Zero_20180627_PACKETHANDLER_HPP */
