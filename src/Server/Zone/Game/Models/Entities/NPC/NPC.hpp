#ifndef HORIZON_ZONE_GAME_ENTITIES_NPC_HPP
#define HORIZON_ZONE_GAME_ENTITIES_NPC_HPP

#include "Server/Zone/Game/Models/Entities/Entity.hpp"

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
class NPC : public Entity, public GridObject<NPC>
{
public:
	NPC(uint32_t guid);
	~NPC();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_NPC_HPP */
