/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

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
