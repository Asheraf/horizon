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
: Entity::Entity(guid, type, map_name, mcoords), _dest_pos{mcoords}
{
}

Unit::Unit(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Entity::Entity(guid, type, map_name, mcoords, gcoords), _dest_pos{mcoords}
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

void Unit::schedule_movement(MapCoords coords)
{
	AStar::coords source_coords = { get_map_coords().x(), get_map_coords().y() };
	AStar::coords dest_coords = { coords.x(), coords.y() };
	Map *map = MapMgr->getMap(get_map_name());
	boost::optional<AStar::CoordinateList> path;

	// Account for fast changes.
	if (map->get_pathfinder()->get_state() == AStar::STATE_COMPUTING)
		map->get_pathfinder()->cancel();

	// This method returns vector of coordinates from target to source.
	if (!(path = map->get_pathfinder()->navigate(source_coords, dest_coords)))
		return;

	path->erase(path->end() - 1);
	printf("started at %d %d\n", source_coords.x, source_coords.y);

	// Copy walk path in order source -> target.
	_walk_path.insert(_walk_path.end(), path->rbegin(), path->rend());

	if (_walk_path.size() > 0) {
		if (_dest_changed_pos == coords)
			_current_dest_pos = coords;

		auto it = std::find_if(_walk_path.begin(), _walk_path.end(), [&source_coords] (const AStar::coords &c) {
			return c.x == source_coords.x && c.y == source_coords.y;
		});

		if (it == _walk_path.end())
			printf("not found %d %d - step: %d.\n", source_coords.x, source_coords.y, _walk_step);

		move();
	}

	_dest_changed_pos = { 0, 0 };
}

std::chrono::time_point<std::chrono::high_resolution_clock> start_t = std::chrono::high_resolution_clock::now();
void Unit::move()
{
	AStar::coords c = _walk_path.at(0); // get current step.
	// character speed = 150
	// move cost 14 if diagonal 10 otherwise
	//
	int step_time = (150 * (c.move_cost / 10));

	getScheduler().Schedule(Milliseconds(step_time), ENTITY_SCHEDULE_WALK,
		[this, c] (TaskContext /*movement*/)
		{
			set_map_coords({ (uint16_t) c.x, (uint16_t) c.y });

			if (_current_dest_pos == get_map_coords()) {
				_walk_path.clear();
				printf("reached %d %d\n", c.x, c.y);
			} else {
				_walk_path.erase(_walk_path.begin());

				if (_dest_changed_pos != MapCoords(0, 0)) {
					_walk_path.clear();
					schedule_movement(_dest_changed_pos);
				} else if (_walk_path.size()) {
					update_position(_current_dest_pos.x(), _current_dest_pos.y());
					move();
				}
			}

			std::chrono::time_point<std::chrono::high_resolution_clock> current_t = std::chrono::high_resolution_clock::now();
			//printf("%d\n", (int) std::chrono::duration_cast<std::chrono::microseconds>(current_t - start_t).count());
			start_t = current_t;
		});
}

bool Unit::move_to_pos(uint16_t x, uint16_t y)
{
	_dest_pos = {x, y};
	return true;
}

void Unit::update(uint32_t diff)
{
	Entity::update(diff);

	if (_dest_pos != _current_dest_pos) {
		if (getScheduler().Count(ENTITY_SCHEDULE_WALK)) {
			_dest_changed_pos = _dest_pos;
		} else {
			_current_dest_pos = _dest_pos;
		}
	}

	if (!getScheduler().Count(ENTITY_SCHEDULE_WALK) && _current_dest_pos != get_map_coords())
		schedule_movement(_current_dest_pos);
}

// Called from a network thread through initialize()
// but should ideally support thread safety.
void Unit::update_status()
{
	if (getEntityType() == ENTITY_PLAYER)
		static_cast<Player *>(this)->update_status();
}
