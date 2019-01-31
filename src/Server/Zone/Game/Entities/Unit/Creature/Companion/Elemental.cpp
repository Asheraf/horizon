#include "Elemental.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

Elemental::Elemental(uint32_t guid)
: Creature(guid, ENTITY_ELEMENTAL)
{
	//
}

Elemental::Elemental(uint32_t guid, MapCoords mcoords)
: Creature(guid, ENTITY_ELEMENTAL, mcoords)
{
	//
}

Elemental::Elemental(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Creature(guid, ENTITY_ELEMENTAL, mcoords, gcoords)
{
	//
}


Elemental::~Elemental()
{
	//
}
