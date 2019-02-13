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

#ifndef HORIZON_CHAR_RAGEXE_20171220_PACKETHANDLER_HPP
#define HORIZON_CHAR_RAGEXE_20171220_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_SECOND_PASSWD_LOGIN.hpp"
#include "Server/Char/Packets/Ragexe/20170906/PacketHandlerRagexe20170906.hpp"

namespace Horizon
{
namespace Char
{

class CharSocket;

class PacketHandlerRagexe20171220 : public PacketHandlerRagexe20170906
{
public:
	PacketHandlerRagexe20171220(std::shared_ptr<CharSocket> socket);
	~PacketHandlerRagexe20171220();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_CHAR_Ragexe_20171220_PACKETHANDLER_HPP */
