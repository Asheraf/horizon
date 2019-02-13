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

#ifndef HORIZON_AUTH_RAGEXE_20171213_PACKET_AC_LOGIN_OTP_HPP
#define HORIZON_AUTH_RAGEXE_20171213_PACKET_AC_LOGIN_OTP_HPP

#include "Server/Auth/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_LOGIN_OTP.hpp"

#include "Server/Common/PacketBuffer.hpp"


namespace Horizon
{
namespace Auth
{
namespace Ragexe20171213
{
struct PACKET_AC_LOGIN_OTP : public Horizon::Auth::Ragexe::PACKET_AC_LOGIN_OTP
{
	PACKET_AC_LOGIN_OTP(uint16_t packet_id = AC_LOGIN_OTP) : Horizon::Auth::Ragexe::PACKET_AC_LOGIN_OTP(packet_id) { }

	/* Size: -1 bytes */
};
}
}
}

#endif /* HORIZON_AUTH_RAGEXE_20171213_PACKET_AC_LOGIN_OTP_HPP */
