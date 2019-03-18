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

#pragma once
#ifndef HORIZON_HORIZON_HPP
#define HORIZON_HORIZON_HPP

#include "Definitions/Definitions.hpp"
#include "Client.hpp"

#define MINIMUM_PACKETVER 20171206

#define MAXIMUM_PACKETVER 20199999
#define DEFAULT_PACKETVER MINIMUM_PACKETVER

#define RENEWAL

#define MAX_LEVEL 175
#define MAX_STATUS_POINTS 130

/* Maximum Character Slots (in multiples of 3) */
#define MAX_CHARACTER_SLOTS 9
#define DEFAULT_MOVEMENT_SPEED 150
#define MAX_VIEW_RANGE 14
#define MAX_NPC_TRIGGER_RANGE 5

#define MIN_INVENTORY_SIZE 100
#define MAX_INVENTORY_SIZE 300
#define MIN_STORAGE_SIZE 600
#define MAX_STORAGE_SIZE 600
#define MAX_ITEM_STACK_SIZE 30000

static_assert(MAX_LEVEL > 0,
			  "MAX_LEVEL should be greater than 0.");
static_assert(MAX_ITEM_STACK_SIZE > 0,
			  "MAX_ITEM_STACK_SIZE should be greater than 0.");
static_assert(MINIMUM_PACKETVER <= MAXIMUM_PACKETVER,
			  "MINIMUM_PACKETVER cannot be greater than MAXIMUM_PACKETVER");
static_assert(MAX_CHARACTER_SLOTS % 3 == 0,
			  "MAX_CHARACTER_SLOTS must be in multiples of 3!");
static_assert(DEFAULT_MOVEMENT_SPEED > 0 && DEFAULT_MOVEMENT_SPEED < 1000,
			  "DEFAULT_MOVEMENT_SPEED must be greater than 0 and less than 1000.");
static_assert(MAX_VIEW_RANGE > 0,
			  "View range affects visibility range for players and should not be 0.");
static_assert(MAX_NPC_TRIGGER_RANGE > 0 && MAX_NPC_TRIGGER_RANGE < MAX_VIEW_RANGE,
			  "MAX_NPC_TRIGGER_RANGE must be less than MAX_VIEW_RANGE and greater than 0.");
static_assert(MIN_INVENTORY_SIZE > 0 && MAX_INVENTORY_SIZE > MIN_INVENTORY_SIZE,
			  "Max Inventory should be greater than minimum storage size of 1.");
static_assert(MIN_STORAGE_SIZE > 0 && MAX_STORAGE_SIZE >= MIN_STORAGE_SIZE,
			  "Max storage should be greater than minimum storage size of 1.");

#endif //HORIZON_HORIZON_HPP
