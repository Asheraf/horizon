#include "Unit.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Player/Player.hpp"
#include "Server/Zone/Session/ZoneSession.hpp"
#include "Server/Zone/PacketHandler/PacketHandler.hpp"
#include <chrono>
#include <boost/optional.hpp>

using namespace Horizon::Zone::Game;
using namespace Horizon::Zone::Game::Entities;

Unit::Unit(uint32_t guid, entity_type type)
: Entity::Entity(guid, type)
{
}

Unit::Unit(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords)
: Entity::Entity(guid, type, map_name, mcoords)
{
}

Unit::Unit(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Entity::Entity(guid, type, map_name, mcoords, gcoords)
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

	Map *map = MapMgr->getMap(get_map_name());

	if (_walk_path.size())
		_walk_path.clear();

	// This method returns vector of coordinates from target to source.
	auto path = map->get_pathfinder()->findPath(source_coords, dest_coords);

	if (path.size() == 0)
		return false;

	_walk_path = path;
	std::reverse(_walk_path.begin(), _walk_path.end());
	_walk_path.erase(_walk_path.begin());

	printf("%d %d -> %d %d\n", source_coords.x, source_coords.y, dest_coords.x, dest_coords.y);

	_changed_dest_pos = {0, 0};

	if (_walk_path.size() > 14 || _walk_path.size() == 0) {
		static_cast<Player *>(this)->stop_movement();
	} else if (_walk_path.size() > 0) {
		update_position(_dest_pos.x(), _dest_pos.y());
		move();
	}

	return true;
}

void Unit::move()
{
	AStar::Vec2i c = _walk_path.at(0); // get current step.
	// character speed = 150
	// move cost 14 if diagonal 10 otherwise
	//

	if (_changed_dest_pos != MapCoords(0, 0)) {
		_dest_pos = _changed_dest_pos;
		schedule_movement(_dest_pos);
		return;
	}

	getScheduler().Schedule(Milliseconds(c.move_cost == 10 ? 150 : 210), ENTITY_SCHEDULE_WALK,
		[this, c] (TaskContext /*movement*/)
		{
			set_map_coords({ (uint16_t) c.x, (uint16_t) c.y });
			_walk_path.erase(_walk_path.begin());

			printf("%d %d %d\n", c.x, c.y, c.move_cost);

			if (_dest_pos == MapCoords(c.x, c.y)) {
				_dest_pos = { 0, 0 };
				printf("reached %d %d\n", c.x, c.y);
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

void Unit::update(uint32_t diff)
{
	Entity::update(diff);
}

// Called from a network thread through initialize()
// but should ideally support thread safety.
void Unit::update_status()
{
	if (getEntityType() == ENTITY_PLAYER)
		static_cast<Player *>(this)->update_status();
}
