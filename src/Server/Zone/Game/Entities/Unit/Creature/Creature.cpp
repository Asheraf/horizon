#include "Creature.hpp"

Horizon::Zone::Game::Entities::Creature::Creature(uint32_t guid, entity_type type)
: Horizon::Zone::Game::Entities::Unit(guid, type)
{
	//
}

Horizon::Zone::Game::Entities::Creature::Creature(uint32_t guid, entity_type type, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Unit(guid, type, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Creature::Creature(uint32_t guid, entity_type type, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Unit(guid, type, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Creature::~Creature()
{
	//
}
