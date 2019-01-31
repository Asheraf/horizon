#include "Skill.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

Skill::Skill(uint32_t guid)
: Unit(guid, ENTITY_SKILL)
{
	//
}

Skill::Skill(uint32_t guid, MapCoords mcoords)
: Unit(guid, ENTITY_SKILL, mcoords)
{
	//
}

Skill::Skill(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Unit(guid, ENTITY_SKILL, mcoords, gcoords)
{
	//
}


Skill::~Skill()
{
	//
}
