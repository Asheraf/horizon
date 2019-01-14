#ifndef HORIZON_ZONE_GAME_ENTITIES_MVP_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MVP_HPP

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
class MVP : public Creature, public GridObject<MVP>
{
public:
	MVP(uint32_t guid);
	MVP(uint32_t guid, std::string const &map_name, MapCoords mcoords);
	MVP(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords);
	~MVP();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MVP_HPP */
