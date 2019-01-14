#ifndef HORIZON_ZONE_GAME_ENTITIES_MONSTER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MONSTER_HPP

#include "Server/Zone/Game/Models/Entities/Unit/Creature/Creature.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
template<class T>
class GridObject;
namespace Entities
{
class Monster : public Creature, public GridObject<Monster>
{
public:
	Monster(uint32_t guid);
	Monster(uint32_t guid, std::string const &map_name, MapCoords mcoords);
	Monster(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords);
	~Monster();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MONSTER_HPP */
