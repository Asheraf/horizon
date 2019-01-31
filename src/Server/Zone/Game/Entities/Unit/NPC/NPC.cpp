#include "NPC.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"

using namespace Horizon::Zone::Game::Entities;

NPC::NPC(uint32_t guid)
: Unit(guid, ENTITY_NPC)
{
	//
}

NPC::NPC(uint32_t guid, MapCoords mcoords, GridCoords gcoords)
: Unit(guid, ENTITY_NPC, mcoords, gcoords)
{
	//
}

NPC::NPC(uint32_t guid, npc_data &nd)
: Unit(guid, ENTITY_NPC, MapCoords(nd.x, nd.y))
{
	set_job_id(nd.sprite_id);
	set_name(nd.npc_name);
	set_direction(nd.direction);
}

NPC::~NPC()
{

}

void NPC::initialize()
{
	Unit::initialize();
}

void NPC::update_status()
{

}

void NPC::stop_movement()
{

}

void NPC::update_viewport()
{

}
