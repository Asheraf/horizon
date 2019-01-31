#include "Monster.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

Monster::Monster(uint32_t guid)
: Creature(guid, ENTITY_MONSTER)
{
	//
}

Monster::Monster(uint32_t guid, MapCoords mcoords)
: Creature(guid, ENTITY_MONSTER, mcoords)
{
	//
}

Monster::Monster(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Creature(guid, ENTITY_MONSTER, mcoords, gcoords)
{
	//
}

Monster::~Monster()
{
	//
}
