/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
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
