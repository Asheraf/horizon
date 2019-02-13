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

#ifndef HORIZON_CHAR_ZERO_20180103_PACKETHANDLER_HPP
#define HORIZON_CHAR_ZERO_20180103_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/Zero/20171220/PacketHandlerZero20171220.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerZero20180103 : public PacketHandlerZero20171220
{
public:
	PacketHandlerZero20180103(std::shared_ptr<CharSocket> socket);
	~PacketHandlerZero20180103();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_Zero_20180103_PACKETHANDLER_HPP */
