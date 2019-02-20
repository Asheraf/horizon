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

#include "NPC.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Map.hpp"

using namespace Horizon::Zone::Game::Entities;

static uint32_t last_npc_guid{NPC_START_GUID};

NPC::NPC(uint32_t guid)
: Unit(guid, ENTITY_NPC)
{
}

NPC::NPC(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Unit(guid, ENTITY_NPC, mcoords, gcoords)
{
}

NPC::NPC(uint32_t guid, npc_db_data &nd)
: Unit(guid, ENTITY_NPC, MapCoords(nd.x, nd.y))
{
	set_guid(last_npc_guid++);
	set_job_id(nd.sprite_id);
	set_name(nd.npc_name);
	set_direction(nd.direction);
}

NPC::~NPC()
{
	remove_grid_reference();
}

void NPC::initialize()
{
	Unit::initialize();

	get_map()->ensure_grid_for_entity(this, get_map_coords());
}

void NPC::update_status()
{

}

void NPC::stop_movement()
{

}

void NPC::on_movement_begin()
{

}

void NPC::on_movement_step()
{
	get_map()->ensure_grid_for_entity(this, get_map_coords());
}

void NPC::on_movement_end()
{

}
