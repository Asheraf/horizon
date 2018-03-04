#ifndef HORIZON_ZONE_GAME_ENTITIES_MVP_HPP
#define HORIZON_ZONE_GAME_ENTITIES_MVP_HPP

#include "Server/Zone/Game/Models/Entities/Unit/Creature/Creature.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class MVP : public Creature
{
public:
	MVP(uint32_t guid);
	~MVP();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_MVP_HPP */