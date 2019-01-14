#include "Skill.hpp"

Horizon::Zone::Game::Entities::Skill::Skill(uint32_t guid)
: Horizon::Zone::Game::Entities::Unit(guid, ENTITY_SKILL)
{
	//
}

Horizon::Zone::Game::Entities::Skill::Skill(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Unit(guid, ENTITY_SKILL, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Skill::Skill(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Unit(guid, ENTITY_SKILL, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Skill::~Skill()
{
	//
}
