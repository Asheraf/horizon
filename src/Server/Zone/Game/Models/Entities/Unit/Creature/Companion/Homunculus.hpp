#ifndef HORIZON_ZONE_GAME_ENTITIES_HOMUNCULUS_HPP
#define HORIZON_ZONE_GAME_ENTITIES_HOMUNCULUS_HPP

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
class Homunculus : public Creature, public GridObject<Homunculus>
{
public:
	Homunculus(uint32_t guid);
	Homunculus(uint32_t guid, std::string const &map_name, MapCoords mcoords);
	Homunculus(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords);
	~Homunculus();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_HOMUNCULUS_HPP */
