#ifndef HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP
#define HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP

#include "Server/Zone/Game/Models/Entities/Entity.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Unit : public Entity
{
public:
	Unit(uint32_t guid);
	~Unit();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP */
