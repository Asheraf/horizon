#include "Pet.hpp"

Horizon::Zone::Game::Entities::Pet::Pet(uint32_t guid)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_PET)
{
	//
}

Horizon::Zone::Game::Entities::Pet::Pet(uint32_t guid, std::string const &map_name, MapCoords mcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_PET, map_name, mcoords)
{
	//
}

Horizon::Zone::Game::Entities::Pet::Pet(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords)
: Horizon::Zone::Game::Entities::Creature(guid, ENTITY_PET, map_name, mcoords, gcoords)
{
	//
}


Horizon::Zone::Game::Entities::Pet::~Pet()
{
	//
}
