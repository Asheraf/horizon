
#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP

#include "Server/Zone/Game/Models/Entities/Entity.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Player : public Entity
{
public:
	Player(uint32_t guid);
	~Player();

private:
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP */
