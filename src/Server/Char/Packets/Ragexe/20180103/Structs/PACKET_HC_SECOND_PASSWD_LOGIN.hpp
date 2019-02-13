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

#ifndef HORIZON_CHAR_RAGEXE_20180103_PACKET_HC_SECOND_PASSWD_LOGIN_HPP
#define HORIZON_CHAR_RAGEXE_20180103_PACKET_HC_SECOND_PASSWD_LOGIN_HPP

#include "Server/Char/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Char/Packets/Ragexe/20171220/Structs/PACKET_HC_SECOND_PASSWD_LOGIN.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Char
{
namespace Ragexe20180103
{
struct PACKET_HC_SECOND_PASSWD_LOGIN : public Horizon::Char::Ragexe20171220::PACKET_HC_SECOND_PASSWD_LOGIN
{
	PACKET_HC_SECOND_PASSWD_LOGIN(uint16_t packet_id = HC_SECOND_PASSWD_LOGIN) : Horizon::Char::Ragexe20171220::PACKET_HC_SECOND_PASSWD_LOGIN(packet_id) { }

	/* Size: 64 bytes */
};
}
}
}

#endif /* HORIZON_CHAR_RAGEXE_20180103_PACKET_HC_SECOND_PASSWD_LOGIN_HPP */
