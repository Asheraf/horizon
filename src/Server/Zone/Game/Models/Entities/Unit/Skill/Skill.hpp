
#ifndef HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP
#define HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP

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
class Skill : public Unit, public GridObject<Skill>
{
public:
	Skill(uint32_t guid);
	~Skill();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_SKILL_HPP */
