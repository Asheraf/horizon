#include "Mercenary.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

Mercenary::Mercenary(uint32_t guid)
: Creature(guid, ENTITY_MERCENARY)
{
	//
}

Mercenary::Mercenary(uint32_t guid, MapCoords mcoords)
: Creature(guid, ENTITY_MERCENARY, mcoords)
{
	//
}

Mercenary::Mercenary(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Creature(guid, ENTITY_MERCENARY, mcoords, gcoords)
{
	//
}


Mercenary::~Mercenary()
{
	//
}
