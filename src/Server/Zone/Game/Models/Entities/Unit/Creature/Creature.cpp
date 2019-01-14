#include "Creature.hpp"

Horizon::Zone::Game::Entities::Creature::Creature(uint32_t guid, entity_type type)
: Horizon::Zone::Game::Entities::Unit(guid, type)
{
	//
}

Horizon::Zone::Game::Entities::Creature::Creature(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Unit(guid, type, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Creature::Creature(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Unit(guid, type, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Creature::~Creature()
{
	//
}
