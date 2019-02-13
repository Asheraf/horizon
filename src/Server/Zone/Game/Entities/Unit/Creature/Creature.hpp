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
