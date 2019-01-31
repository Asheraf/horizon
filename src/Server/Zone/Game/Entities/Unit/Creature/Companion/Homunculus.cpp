#include "Homunculus.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

Homunculus::Homunculus(uint32_t guid)
: Creature(guid, ENTITY_HOMUNCULUS)
{
	//
}

Homunculus::Homunculus(uint32_t guid, MapCoords mcoords)
: Creature(guid, ENTITY_HOMUNCULUS, mcoords)
{
	//
}

Homunculus::Homunculus(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Creature(guid, ENTITY_HOMUNCULUS, mcoords, gcoords)
{
	//
}


Homunculus::~Homunculus()
{
	//
}
