/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#ifndef HORIZON_INTER_PACKETS_H
#define HORIZON_INTER_PACKETS_H

#include "Server/Common/PacketBuffer.hpp"

namespace Horizon
{
namespace Inter
{
enum packets
{
	/* Inter-Auth Packets */
	AI_CHARSERV_GET_INFO        = 0x09,
};
}
}

#endif //HORIZON_INTER_PACKETS_H
