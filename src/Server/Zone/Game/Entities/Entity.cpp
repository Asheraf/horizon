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

#include "Entity.hpp"
#include "GridObject.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Entities/Traits/Status.hpp"
#include "Server/Zone/Zone.hpp"

using namespace Horizon::Zone;

Entity::Entity(uint32_t guid, entity_type type, std::shared_ptr<Map> map, MapCoords map_coords)
: _guid(guid), _type(type), _map_coords(map_coords)
{
	set_map(map);
}

Entity::~Entity()
{
}

void Entity::initialize()
{

	notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);

	_is_initialized = true;

	_status = std::make_shared<Entities::Traits::Status>(shared_from_this());

//	if (get_type() == ENTITY_PLAYER)
//		getScheduler().Schedule(Milliseconds(sZone->zone_config().get_entity_save_interval()), ENTITY_SCHEDULE_SAVE,
//			[this] (TaskContext context) {
//				sync_with_models();
//				context.Repeat();
//			});
}


bool Entity::schedule_movement(MapCoords coords)
{
	AStar::Vec2i source_coords = { map_coords().x(), map_coords().y() };
	AStar::Vec2i dest_coords = { coords.x(), coords.y() };

	if (_walk_path.size())
		_walk_path.clear();

	if (!map()) {
		HLog(error) << "Reference to map object has been lost for entity " << (void *) this << ".";
		return false;
	}

	// This method returns vector of coordinates from target to source.
	auto path = map()->get_pathfinder().findPath(source_coords, dest_coords);

	if (path.size() == 0)
		return false;

	_walk_path = path;
	std::reverse(_walk_path.begin(), _walk_path.end());
	_walk_path.erase(_walk_path.begin());

	_changed_dest_pos = {0, 0};

	if (_walk_path.size() > 14) {
		if (this->get_type() == ENTITY_PLAYER)
			static_cast<Entities::Player *>(this)->stop_movement();
	} else if (_walk_path.size() > 0) {
		on_movement_begin();
		move();
	}

	return true;
}

void Entity::move()
{
	MapCoords my_coords = map_coords();
	AStar::Vec2i c = _walk_path.at(0);

	getScheduler().Schedule(Milliseconds(status()->get_movement_speed()->get_with_cost(c.move_cost)), ENTITY_SCHEDULE_WALK,
		[this, c, my_coords] (TaskContext /*movement*/)
		{
			if (_instep_movement_stop)
				return;

			MapCoords step_coords(c.x, c.y);

			set_direction((directions) my_coords.direction_to(step_coords));

			notify_nearby_players_of_self(EVP_NOTIFY_OUT_OF_SIGHT);
			set_map_coords(step_coords);
			notify_nearby_players_of_self(EVP_NOTIFY_IN_SIGHT);

			_walk_path.erase(_walk_path.begin());

			on_movement_step();

			if (_changed_dest_pos != MapCoords(0, 0)) {
				_dest_pos = _changed_dest_pos;
				schedule_movement(_dest_pos);
				return;
			} else if (_dest_pos == MapCoords(c.x, c.y)) {
				_dest_pos = { 0, 0 };
				on_movement_end();
			}

			if (_walk_path.size() > 0)
				move();
		});
}

bool Entity::move_to_coordinates(uint16_t x, uint16_t y)
{
	if (getScheduler().Count(ENTITY_SCHEDULE_WALK)) {
		_changed_dest_pos = { x, y };
		return true;
	}

	_dest_pos = { x, y };

	schedule_movement(_dest_pos);

	return true;
}

void Entity::update(uint64_t /*diff*/)
{
	_scheduler.Update();
}

bool Entity::is_in_range_of(std::shared_ptr<Entity> e, uint8_t range)
{
	if (e->map()->get_name().compare(map()->get_name()))
		return false;

	return map_coords().is_within_range(e->map_coords(), range);
}

std::shared_ptr<Entity> Entity::get_nearby_entity(uint32_t guid)
{
	GridEntitySearcher searcher(guid);
	GridReferenceContainerVisitor<GridEntitySearcher, GridReferenceContainer<AllEntityTypes>> search_visitor(searcher);

	map()->visit_in_range(map_coords(), search_visitor);

	return searcher.get_result().lock();
}

void Entity::notify_nearby_players_of_self(entity_viewport_notification_type notif_type)
{
	GridEntityExistenceNotifier existence_notify(shared_from_this(), notif_type);
	GridReferenceContainerVisitor<GridEntityExistenceNotifier, GridReferenceContainer<AllEntityTypes>> entity_visitor(existence_notify);

	map()->visit_in_range(map_coords(), entity_visitor);
}
