#ifndef HORIZON_ZONE_GAME_ENTITIES_PET_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PET_HPP

#include "Server/Zone/Game/Entities/Unit/Creature/Creature.hpp"

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
class Pet : public Creature, public GridObject<Pet>
{
public:
	Pet(uint32_t guid);
	Pet(uint32_t guid, MapCoords mcoords);
	Pet(uint32_t guid, MapCoords mcoords, GridCoords gcoords);
	~Pet();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_PET_HPP */
