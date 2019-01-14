#include "MVP.hpp"

Horizon::Zone::Game::Entities::MVP::MVP(uint32_t guid)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_MVP)
{
	//
}

Horizon::Zone::Game::Entities::MVP::MVP(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_MVP, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::MVP::MVP(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_MVP, map_name, mcoords, gcoords)
{
	//
}

Horizon::Zone::Game::Entities::MVP::~MVP()
{
	//
}
