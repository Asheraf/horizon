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

#ifndef HORIZON_CHAR_RE_20170228_PACKETHANDLER_HPP
#define HORIZON_CHAR_RE_20170228_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/RE/20170104/PacketHandlerRE20170104.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRE20170228 : public PacketHandlerRE20170104
{
public:
	PacketHandlerRE20170228(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRE20170228();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_RE_20170228_PACKETHANDLER_HPP */
