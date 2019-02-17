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

#ifndef HORIZON_ZONE_GAME_ENTITIES_CREATURE_HPP
#define HORIZON_ZONE_GAME_ENTITIES_CREATURE_HPP

#include "Server/Zone/Game/Entities/Unit/Unit.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Creature : public Unit
{
public:
	Creature(uint32_t guid, entity_types type);
	Creature(uint32_t guid, entity_types type, MapCoords mcoords);
	Creature(uint32_t guid, entity_types type, MapCoords mcoords, GridCoords gcoords);
	~Creature();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_CREATURE_HPP */
