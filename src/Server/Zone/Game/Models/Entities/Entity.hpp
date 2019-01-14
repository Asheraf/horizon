
#ifndef HORIZON_ZONE_GAME_ENTITIES_ENTITY_HPP
#define HORIZON_ZONE_GAME_ENTITIES_ENTITY_HPP

#include "Server/Common/Horizon.hpp"
#include "Server/Zone/Game/Models/Entities/GridObject.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include "Core/Multithreading/TaskScheduler/TaskScheduler.hpp"

#include <stdlib.h>
#include <memory>
#include <iostream>

enum entity_type
{
	ENTITY_OBJECT     = 0,
	ENTITY_PLAYER     = 1,
	ENTITY_MONSTER    = 2,
	ENTITY_MVP        = 4,
	ENTITY_PET        = 5,
	ENTITY_HOMUNCULUS = 6,
	ENTITY_MERCENARY  = 7,
	ENTITY_NPC        = 8,
	ENTITY_SKILL      = 9,
	ENTITY_ELEMENTAL  = 10
};

enum entity_type_mask
{
	ENTITY_MASK_OBJECT     = 0x000,
	ENTITY_MASK_PLAYER     = 0x001,
	ENTITY_MASK_CREATURE   = 0x002,
	ENTITY_MASK_PET        = 0x004,
	ENTITY_MASK_HOMUNCULUS = 0x008,
	ENTITY_MASK_MERCENARY  = 0x010,
	ENTITY_MASK_SKILL      = 0x020,
	ENTITY_MASK_NPC        = 0x040,
	ENTITY_MASK_ELEMENTAL  = 0x080,
	ENTITY_MASK_ALL        = 0xFFF
};

enum entity_task_schedule_group
{
	ENTITY_SCHEDULE_WALK = 0
};

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Entity : public std::enable_shared_from_this<Horizon::Zone::Game::Entity>
{
public:
	Entity(uint32_t guid, entity_type type);
	Entity(uint32_t guid, entity_type type, std::string const &map_name, MapCoords map_coords);
	Entity(uint32_t guid, entity_type type, std::string const &map_name, MapCoords map_coords, GridCoords grid_coords);
	~Entity();

	virtual void initialize();
	uint32_t getGUID() { return _guid; }
	bool isInZone() { return _in_zone; }
	void setInZone() { _in_zone = true; }

	entity_type getEntityType() { return _type; }
	void setEntityType(entity_type type) { _type = type; }

	/* Location Information */
	std::string &get_map_name() { return _map_name; }
	/* Map Coords */
	MapCoords &get_map_coords() { return _map_coords; }
	void set_map_coords(MapCoords const &coords) { _map_coords = coords; }
	/* Grid Coords */
	GridCoords &get_grid_coords() { return _grid_coords; }
	void set_grid_coords(GridCoords const &coords) { _grid_coords = coords; }
	void addToGrid();
	/* Update */
	virtual void update(uint32_t diff);
	/* Scheduler */
	TaskScheduler &getScheduler() { return _scheduler; }

private:
	uint32_t _guid{0};
	entity_type _type{ENTITY_OBJECT};
	bool _in_zone{false};
	std::string _map_name{""};
	MapCoords _map_coords{0, 0};
	GridCoords _grid_coords{0, 0};
	TaskScheduler _scheduler;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_ENTITY_HPP */
