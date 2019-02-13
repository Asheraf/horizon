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

#ifndef HORIZON_CHAR_RE_20170104_PACKETHANDLER_HPP
#define HORIZON_CHAR_RE_20170104_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/PacketHandler.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRE20170104 : public PacketHandler
{
public:
	PacketHandlerRE20170104(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRE20170104();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_RE_20170104_PACKETHANDLER_HPP */
