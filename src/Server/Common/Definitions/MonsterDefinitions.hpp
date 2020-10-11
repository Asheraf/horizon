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
#ifndef HORIZON_ZONE_GAME_MONSTER_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_MONSTER_DEFINITIONS_HPP

#define MAX_MOB_DROP 10
#define MAX_MVP_DROP 10

struct monster_config_data
{
	int monster_id;
	char sprite_name[MAX_UNIT_NAME_LENGTH], name[MAX_UNIT_NAME_LENGTH], alt_name[MAX_UNIT_NAME_LENGTH];

	short view_range, chase_range;
	short group_id;
	unsigned short lv;
	//struct view_data vd;
	unsigned int option;
	//struct mob_skill skill[MAX_MOBSKILL];
	//struct spawn_info spawn[10];

	struct rewards
	{
		unsigned int base_exp, job_exp;
		unsigned int mvp_exp;
		struct { int item_id, rate; } items[MAX_MOB_DROP];
		struct { int item_id, rate; } items_mvp[MAX_MVP_DROP];
	} rewards;
};

#endif /* HORIZON_ZONE_GAME_MONSTER_DEFINITIONS_HPP */
