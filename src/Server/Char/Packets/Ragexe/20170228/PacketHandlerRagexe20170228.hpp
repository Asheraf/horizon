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

#ifndef HORIZON_CHAR_RAGEXE_20170228_PACKETHANDLER_HPP
#define HORIZON_CHAR_RAGEXE_20170228_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/Ragexe/20170228/Structs/PACKET_HC_NOTIFY_ZONESVR.hpp"
#include "Server/Char/Packets/Ragexe/20170104/PacketHandlerRagexe20170104.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRagexe20170228 : public PacketHandlerRagexe20170104
{
public:
	PacketHandlerRagexe20170228(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRagexe20170228();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_Ragexe_20170228_PACKETHANDLER_HPP */
