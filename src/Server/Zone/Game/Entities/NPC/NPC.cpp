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

#include "NPC.hpp"
#include "Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Status/Status.hpp"


using namespace Horizon::Zone::Game::Entities;

static uint32_t last_npc_guid{NPC_START_GUID};

NPC::NPC(std::string const &name, std::shared_ptr<Map> map, uint16_t x, uint16_t y, uint32_t job_id, directions dir)
: Entity(last_npc_guid++, ENTITY_NPC, map, MapCoords(x, y))
{
	set_name(name);
	set_job_id(job_id);
	set_direction(dir);

	_npc_data.npc_name = name;
	_npc_data.map_name = map->get_name();
	_npc_data.coords = get_map_coords();
	_npc_data.direction = dir;
}

NPC::NPC(std::string const &name, std::shared_ptr<Map> map, uint16_t x, uint16_t y, uint32_t job_id, directions dir, std::string const &script_file)
: Entity(last_npc_guid++, ENTITY_NPC, map, MapCoords(x, y))
{
	set_name(name);
	set_job_id(job_id);
	set_direction(dir);

	_npc_data.npc_name = name;
	_npc_data.map_name = map->get_name();
	_npc_data.coords = get_map_coords();
	_npc_data.direction = dir;
	_npc_data.script = script_file;
	_npc_data.script_is_file = true;
}

NPC::NPC(std::string const &name, std::shared_ptr<Map> map, uint16_t x, uint16_t y, uint32_t job_id, directions dir, std::shared_ptr<NPC> duplicate)
: Entity(last_npc_guid++, ENTITY_NPC, map, MapCoords(x, y))
{
	set_name(name);
	set_job_id(job_id);
	set_direction(dir);

	_npc_data.npc_name = name;
	_npc_data.map_name = map->get_name();
	_npc_data.coords = get_map_coords();
	_npc_data.direction = dir;
	_npc_data.script = duplicate->_npc_data.script;
	_npc_data.script_is_file = true;
}

NPC::NPC(std::string const &name, std::shared_ptr<Map> map, uint16_t x, uint16_t y, std::string const &script, uint8_t trigger_range)
: Entity(last_npc_guid++, ENTITY_NPC, map, MapCoords(x, y))
{
	set_name(name);
	set_job_id(NPC_TYPE_PORTAL);
	set_direction(DIR_NORTH);

	_npc_data.npc_name = name;
	_npc_data.map_name = map->get_name();
	_npc_data.coords = get_map_coords();
	_npc_data.direction = DIR_NORTH;
	_npc_data.script = script;
	_npc_data.script_is_file = false;
	_npc_data.trigger_range = trigger_range;
}

NPC::~NPC()
{
	remove_grid_reference();
}

void NPC::initialize()
{
	Entity::initialize();

	_npc_data._npc = downcast<NPC>();
	get_script_manager()->add_npc_to_db(get_guid(), _npc_data);

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
