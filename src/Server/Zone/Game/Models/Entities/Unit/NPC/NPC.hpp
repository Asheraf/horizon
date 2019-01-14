#ifndef HORIZON_ZONE_GAME_ENTITIES_NPC_HPP
#define HORIZON_ZONE_GAME_ENTITIES_NPC_HPP

#include "Server/Zone/Game/Models/Entities/Unit/Unit.hpp"

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
class NPC : public Unit, public GridObject<NPC>
{
public:
	NPC(uint32_t guid);
	NPC(uint32_t guid, std::string const &map_name, MapCoords mcoords);
	NPC(uint32_t guid, std::string const &map_name, MapCoords mcoords, GridCoords gcoords);
	~NPC();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_NPC_HPP */
