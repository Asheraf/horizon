#include "Elemental.hpp"


Horizon::Zone::Game::Entities::Elemental::Elemental(uint32_t guid)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_ELEMENTAL)
{
	//
}

Horizon::Zone::Game::Entities::Elemental::Elemental(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_ELEMENTAL, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Elemental::Elemental(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_ELEMENTAL, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Elemental::~Elemental()
{
	//
}
