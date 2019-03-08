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

#include "NPC.hpp"
#include "Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Status/Status.hpp"

using namespace Horizon::Zone::Game::Entities;

static uint32_t last_npc_guid{NPC_START_GUID};

NPC::NPC(std::string const &name, std::shared_ptr<Map> map, MapCoords const &coords, uint32_t job_id, directions dir)
: Entity(last_npc_guid++, ENTITY_NPC, map, coords)
{
	set_job_id(job_id);
	set_direction(dir);
}

NPC::~NPC()
{
	remove_grid_reference();
}

void NPC::initialize()
{
	Entity::initialize();

	get_status()->initialize();
	get_map()->ensure_grid_for_entity(this, get_map_coords());
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

void NPC::sync_with_models()
{
	
}
