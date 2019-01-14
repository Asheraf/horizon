#include "Homunculus.hpp"

Horizon::Zone::Game::Entities::Homunculus::Homunculus(uint32_t guid)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_HOMUNCULUS)
{
	//
}

Horizon::Zone::Game::Entities::Homunculus::Homunculus(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_HOMUNCULUS, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Homunculus::Homunculus(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_HOMUNCULUS, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Homunculus::~Homunculus()
{
	//
}
