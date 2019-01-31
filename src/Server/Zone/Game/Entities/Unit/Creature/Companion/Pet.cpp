#include "Pet.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

Pet::Pet(uint32_t guid)
: Creature(guid, ENTITY_PET)
{
	//
}

Pet::Pet(uint32_t guid, MapCoords mcoords)
: Creature(guid, ENTITY_PET, mcoords)
{
	//
}

Pet::Pet(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Creature(guid, ENTITY_PET, mcoords, gcoords)
{
	//
}


Pet::~Pet()
{
	//
}
