#ifndef HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP

#include "Server/Zone/Game/Models/Entities/Unit/Creature/Creature.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Mercenary : public Creature
{
public:
	Mercenary(uint32_t guid);
	~Mercenary();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MERCENARY_HPP */
