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

#ifndef HORIZON_ZONE_GAME_ENTITIES_MONSTER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MONSTER_HPP

#include "Server/Zone/Game/Entities/Unit/Creature/Creature.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Monster : public Creature, public GridObject<Monster>
{
public:
	Monster(uint32_t guid);
	Monster(uint32_t guid, MapCoords mcoords);
	Monster(uint32_t guid, MapCoords mcoords, GridCoords gcoords);
	~Monster();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MONSTER_HPP */
