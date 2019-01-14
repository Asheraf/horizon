#include "NPC.hpp"

Horizon::Zone::Game::Entities::NPC::NPC(uint32_t guid)
: Horizon::Zone::Game::Entities::Unit(guid, ENTITY_NPC)
{
	//
}

Horizon::Zone::Game::Entities::NPC::NPC(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Unit(guid, ENTITY_NPC, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::NPC::NPC(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Unit(guid, ENTITY_NPC, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::NPC::~NPC()
{
	//
}
