#ifndef HORIZON_ZONE_GAME_ENTITIES_CREATURE_HPP
#define HORIZON_ZONE_GAME_ENTITIES_CREATURE_HPP

#include "Server/Zone/Game/Models/Entities/Entity.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Creature : public Entity
{
public:
	Creature(uint32_t guid);
	~Creature();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_CREATURE_HPP */
