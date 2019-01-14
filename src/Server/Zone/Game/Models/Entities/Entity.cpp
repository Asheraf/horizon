
#include "Entity.hpp"
#include "GridObject.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Models/Entities/Unit/Player/Player.hpp"

using namespace Horizon::Zone::Game;

Entity::Entity(uint32_t guid, entity_type type)
: _guid(guid), _type(type)
{
}

Entity::Entity(uint32_t guid, entity_type type, std::string const &map_name, MapCoords map_coords)
: _guid(guid), _type(type), _map_name(map_name), _map_coords(map_coords)
{
}

Entity::Entity(uint32_t guid, entity_type type, std::string const &map_name, MapCoords map_coords, GridCoords grid_coords)
: _guid(guid), _type(type), _map_name(map_name), _map_coords(map_coords), _grid_coords(grid_coords)
{
}

Entity::~Entity()
{
}

void Entity::initialize()
{
	addToGrid();
}

void Entity::addToGrid()
{
	Map *map = MapMgr->getMap(_map_name);

	if (_type == ENTITY_PLAYER) {
		map->addEntityToMap<Entities::Player>((static_cast<Entities::Player *>(this)), _map_coords);
		setInZone();
	}
}

void Entity::update(uint32_t diff)
{
	_scheduler.Update();
}
