/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_HORIZON_H
#define HORIZON_HORIZON_H

#include "Definitions.hpp"
#include "Client.hpp"

#ifndef MINIMUM_PACKETVER
	#define MINIMUM_PACKETVER 20141022
#endif

#ifndef MAXIMUM_PACKETVER
	#define MAXIMUM_PACKETVER 20171113
#endif

// DEfault Client Packet Version.
#ifndef DEFAULT_PACKETVER
	#define DEFAULT_PACKETVER MINIMUM_PACKETVER
#endif

/* Maximum Character Slots (in multiples of 3) */
#ifndef MAX_CHARACTER_SLOTS
	#define MAX_CHARACTER_SLOTS 9
#endif

#ifndef DEFAULT_WALK_SPEED
	#define DEFAULT_WALK_SPEED 150
#endif

#endif //HORIZON_HORIZON_H
