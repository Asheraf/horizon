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

#ifndef HORIZON_AUTH_ZERO_PACKETS_HPP
#define HORIZON_AUTH_ZERO_PACKETS_HPP

namespace Horizon
{
namespace Auth
{
namespace Zero
{
enum packets
{
	AC_ACCEPT_LOGIN = 0x0ac4,
	CA_OTP_CODE = 0x0ad0,
};
}
}
}
#endif /* HORIZON_AUTH_ZERO_PACKETS_HPP */
