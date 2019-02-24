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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_COMMON_RAGEXE_PACKETS_HPP
#define HORIZON_COMMON_RAGEXE_PACKETS_HPP

#include "Server/Common/Horizon.hpp"
namespace Horizon
{
namespace Common
{
namespace Ragexe
{
enum packets
{
	AHC_GAME_GUARD = 0x03dd,
	CAH_ACK_GAME_GUARD = 0x03de,
	CS_LOGIN_QUERY = 0x09c5,
	CS_REQ_ENCRYPTION = 0x01c6,
	SC_ACK_ENCRYPTION = 0x01c7,
	SC_BILLING_INFO = 0x01b5,
	SC_LOGIN_ANSWER = 0x09c6,
	SC_LOGIN_ANSWER_WITH_ID = 0x09e0,
	SC_LOGIN_ERROR = 0x09c7,
	SC_NOTIFY_BAN = 0x0081,
	SC_SOCT = 0x09c9,
};

}
}
}
#endif /* HORIZON_COMMON_RAGEXE_PACKETS_HPP */
