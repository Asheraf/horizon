
#include "Entity.hpp"
#include "GridObject.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Game/Map/Map.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"

using namespace Horizon::Zone::Game;

Entity::Entity(uint32_t guid, entity_type type)
: _guid(guid), _type(type)
{
}

Entity::Entity(uint32_t guid, entity_type type, MapCoords map_coords)
: _guid(guid), _type(type), _map_coords(map_coords)
{
}

Entity::Entity(uint32_t guid, entity_type type, MapCoords map_coords, GridCoords grid_coords)
: _guid(guid), _type(type), _map_coords(map_coords), _grid_coords(grid_coords)
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
	std::shared_ptr<Map> map = get_map();

	if (!map)
		return;

	if (_type == ENTITY_PLAYER) {
		map->addEntityToMap<Entities::Player>((static_cast<Entities::Player *>(this)), _map_coords);
		setInZone();
	} else if (_type == ENTITY_NPC) {
		map->addEntityToMap<Entities::NPC>((static_cast<Entities::NPC *>(this)), _map_coords);
	}
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
