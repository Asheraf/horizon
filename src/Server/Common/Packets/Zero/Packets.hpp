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

#ifndef HORIZON_COMMON_ZERO_PACKETS_HPP
#define HORIZON_COMMON_ZERO_PACKETS_HPP

#include "Server/Common/Horizon.hpp"
namespace Horizon
{
namespace Common
{
namespace Zero
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
#endif /* HORIZON_COMMON_ZERO_PACKETS_HPP */
