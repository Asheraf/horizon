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
: Entity::Entity(guid, type)
{
}

Unit::Unit(uint32_t guid, entity_types type, MapCoords mcoords)
: Entity::Entity(guid, type, mcoords)
{
}

Unit::Unit(uint32_t guid, entity_types type, MapCoords mcoords, GridCoords gcoords)
: Entity::Entity(guid, type, mcoords, gcoords)
{
}

Unit::~Unit()
{
	//
}

// Called from a network thread.
void Unit::initialize()
{
	Entity::initialize();
	update_status();
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
		printf("path exceeds 14 cells.\n");
	} else if (_walk_path.size() > 0) {
		on_movement_begin();
		notify_nearby_players_of_movement(coords);
		move();
	}

	return true;
}

void Unit::move()
{
	MapCoords my_coords = get_map_coords();
	AStar::Vec2i c = _walk_path.at(0); // get current step.
	// character speed = 150
	// move cost 14 if diagonal 10 otherwise
	//

	int step_time = 0;

	if (c.move_cost == 14) {
		step_time = 150 * 14 / 10;
	} else {
		step_time = 150;
	}

	getScheduler().Schedule(Milliseconds(step_time), ENTITY_SCHEDULE_WALK,
		[this, c, step_time, my_coords] (TaskContext /*movement*/)
		{
			MapCoords step_coords(c.x, c.y);

			set_direction((directions) my_coords.direction_to(step_coords));

			set_map_coords(step_coords);

			_walk_path.erase(_walk_path.begin());

			on_movement_step();
			
			printf("%d %d %d %d\n", c.x, c.y, c.move_cost, step_time);
			
			if (_dest_pos == MapCoords(c.x, c.y)) {
				_dest_pos = { 0, 0 };
				on_movement_end();
			}

			if (_changed_dest_pos != MapCoords(0, 0)) {
				_dest_pos = _changed_dest_pos;
				schedule_movement(_dest_pos);
				return;
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

void Unit::notify_nearby_players_of_movement(MapCoords const &to)
{
	GridMovementNotifier movement_notifier(static_cast<Entity *>(this)->weak_from_this());
	GridReferenceContainerVisitor<GridMovementNotifier, GridReferenceContainer<AllEntityTypes>> entity_visitor(movement_notifier);

	get_map()->visit_in_range(get_map_coords(), MAX_VIEW_RANGE, entity_visitor);
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
