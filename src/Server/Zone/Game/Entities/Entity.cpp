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

#include "Entity.hpp"
#include "GridObject.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"

using namespace Horizon::Zone::Game;

Entity::Entity(uint32_t guid, entity_types type)
: _guid(guid), _type(type)
{
}

Entity::Entity(uint32_t guid, entity_types type, MapCoords map_coords)
: _guid(guid), _type(type), _map_coords(map_coords)
{
}

Entity::Entity(uint32_t guid, entity_types type, MapCoords map_coords, GridCoords grid_coords)
: _guid(guid), _type(type), _map_coords(map_coords), _grid_coords(grid_coords)
{
}

Entity::~Entity()
{
}

void Entity::initialize()
{
}

void Entity::update(uint32_t /*diff*/)
{
	_scheduler.Update();
}

bool Entity::is_in_range_of(std::shared_ptr<Entity> e, uint8_t range)
{
	if (e->get_map()->get_name().compare(get_map()->get_name()))
		return false;

	return get_map_coords().within_range(e->get_map_coords(), range);
}

std::shared_ptr<Entity> Entity::get_nearby_entity(uint32_t guid)
{
	GridEntitySearcher searcher(guid);
	GridReferenceContainerVisitor<GridEntitySearcher, GridReferenceContainer<AllEntityTypes>> search_visitor(searcher);

	get_map()->visit_in_range(get_map_coords(), search_visitor);

	return searcher.get_result().lock();
}
