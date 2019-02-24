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

#include "Unit.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Player/Player.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Core/Logging/Logger.hpp"
#include <chrono>
#include <boost/optional.hpp>

using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;

Unit::Unit(uint32_t guid, entity_types type)
: Entity::Entity(guid, type), _str(1, 0, 0), _agi(1, 0, 0), _vit(1, 0, 0), _int(1, 0, 0), _dex(1, 0, 0), _luk(1, 0, 0)
{
}

Unit::Unit(uint32_t guid, entity_types type, MapCoords mcoords)
: Entity::Entity(guid, type, mcoords), _str(1, 0, 0), _agi(1, 0, 0), _vit(1, 0, 0), _int(1, 0, 0), _dex(1, 0, 0), _luk(1, 0, 0)
{
}

Unit::Unit(uint32_t guid, entity_types type, MapCoords mcoords, GridCoords gcoords)
: Entity::Entity(guid, type, mcoords, gcoords), _str(1, 0, 0), _agi(1, 0, 0), _vit(1, 0, 0), _int(1, 0, 0), _dex(1, 0, 0), _luk(1, 0, 0)
{
}

Unit::~Unit()
{
	//
}

/**
 * @thread MapThreadContainer::_thread
 */
void Unit::initialize()
{
	Entity::initialize();
	update_status();
	notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);
}

bool Unit::schedule_movement(MapCoords coords)
{
	AStar::Vec2i source_coords = { get_map_coords().x(), get_map_coords().y() };
	AStar::Vec2i dest_coords = { coords.x(), coords.y() };

	if (_walk_path.size())
		_walk_path.clear();

	if (!get_map()) {
		ZoneLog->error("Reference to map object has been lost for unit {:p}.", (void *) this);
		return false;
	}

	// This method returns vector of coordinates from target to source.
	auto path = get_map()->get_pathfinder().findPath(source_coords, dest_coords);

	if (path.size() == 0)
		return false;

	_walk_path = path;
	std::reverse(_walk_path.begin(), _walk_path.end());
	_walk_path.erase(_walk_path.begin());

	printf("%d %d -> %d %d\n", source_coords.x, source_coords.y, dest_coords.x, dest_coords.y);

	_changed_dest_pos = {0, 0};

	if (_walk_path.size() > 14) {
		if (this->get_type() == ENTITY_PLAYER)
			static_cast<Player *>(this)->stop_movement();
	} else if (_walk_path.size() > 0) {
		on_movement_begin();
		move();
	}

	return true;
}

void Unit::move()
{
	if (_changed_dest_pos != MapCoords(0, 0)) {
		_dest_pos = _changed_dest_pos;
		schedule_movement(_dest_pos);
		return;
	}

	MapCoords my_coords = get_map_coords();
	AStar::Vec2i c = _walk_path.at(0);

	getScheduler().Schedule(Milliseconds(get_movement_speed(c.move_cost)), ENTITY_SCHEDULE_WALK,
		[this, c, my_coords] (TaskContext /*movement*/)
		{
			MapCoords step_coords(c.x, c.y);

			set_direction((directions) my_coords.direction_to(step_coords));

			notify_nearby_players_of_self(EVP_NOTIFY_OUT_OF_SIGHT);
			set_map_coords(step_coords);
			notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);

			_walk_path.erase(_walk_path.begin());

			on_movement_step();
			
			if (_dest_pos == MapCoords(c.x, c.y)) {
				_dest_pos = { 0, 0 };
				on_movement_end();
			}

			if (_walk_path.size() > 0)
				move();
		});
}

bool Unit::move_to_pos(uint16_t x, uint16_t y)
{
	if (getScheduler().Count(ENTITY_SCHEDULE_WALK)) {
		_changed_dest_pos = { x, y };
		return true;
	}

	_dest_pos = { x, y };

	schedule_movement(_dest_pos);

	return true;
}

void Unit::update(uint32_t diff)
{
	Entity::update(diff);
}

// Called from a network thread through initialize()
// but should ideally support thread safety.
void Unit::update_status()
{

}
