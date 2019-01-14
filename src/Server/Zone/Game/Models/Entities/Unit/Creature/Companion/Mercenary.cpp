#include "Mercenary.hpp"

Horizon::Zone::Game::Entities::Mercenary::Mercenary(uint32_t guid)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_MERCENARY)
{
	//
}

Horizon::Zone::Game::Entities::Mercenary::Mercenary(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_MERCENARY, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Mercenary::Mercenary(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_MERCENARY, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Mercenary::~Mercenary()
{
	//
}
