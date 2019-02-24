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
