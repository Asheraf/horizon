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

#ifndef HORIZON_CHAR_RAGEXE_20170906_PACKETHANDLER_HPP
#define HORIZON_CHAR_RAGEXE_20170906_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/Ragexe/20170906/Structs/PACKET_HC_ACCEPT_MAKECHAR.hpp"
#include "Server/Char/Packets/Ragexe/20170906/Structs/PACKET_HC_UPDATE_CHARINFO.hpp"
#include "Server/Char/Packets/Ragexe/20170906/Structs/PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Char/Packets/Ragexe/20170228/PacketHandlerRagexe20170228.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRagexe20170906 : public PacketHandlerRagexe20170228
{
public:
	PacketHandlerRagexe20170906(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRagexe20170906();

	virtual void initialize_handlers() override;

	virtual void Send_HC_ACCEPT_ENTER() override;

};
}
}

#endif /* HORIZON_CHAR_Ragexe_20170906_PACKETHANDLER_HPP */
