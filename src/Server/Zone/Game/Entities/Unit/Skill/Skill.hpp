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

#ifndef HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP
#define HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP

#include "Server/Zone/Game/Entities/Unit/Unit.hpp"
#include "Server/Zone/Game/Entities/GridObject.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Skill : public Unit, public GridObject<Skill>
{
public:
	Skill(uint32_t guid);
	Skill(uint32_t guid, MapCoords mcoords);
	Skill(uint32_t guid, MapCoords mcoords, GridCoords gcoords);
	~Skill();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP */
