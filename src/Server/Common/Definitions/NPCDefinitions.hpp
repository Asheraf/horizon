/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#ifndef HORIZON_ZONE_GAME_NPC_DEFINITIONS_HPP
#define HORIZON_ZONE_GAME_NPC_DEFINITIONS_HPP

#include "EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"

#include <memory>
#include <string>

#define NPC_START_GUID 500000000

enum npc_type {
	FAKE_NPC               =    -1,
	NPC_TYPE_PORTAL        =    45,
	NPC_TYPE_PORTAL_HIDDEN =   139,
	NPC_TYPE_MOB_TOMB      =   565,
	NPC_TYPE_PORTAL_DBG    =   722,
	NPC_TYPE_FLAG          =   722,
	NPC_TYPE_INVISIBLE     = 32767
};

namespace Horizon
{
	namespace Zone
	{
		namespace Game
		{
			namespace Entities
			{
				class NPC;
			}
		}
	}
}

struct npc_db_data
{
	std::string npc_name{};
	std::string map_name{};
	MapCoords coords;
	directions direction{DIR_SOUTH};
	uint16_t sprite_id{0};
	std::string script{""};
	std::shared_ptr<Horizon::Zone::Game::Entities::NPC> _npc;
	bool script_is_file;
	uint16_t trigger_range;
};

#endif /* HORIZON_ZONE_GAME_NPC_DEFINITIONS_HPP */
