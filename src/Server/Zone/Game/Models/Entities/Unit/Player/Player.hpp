
#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP

#include "Server/Zone/Game/Models/Entities/Entity.hpp"

namespace Horizon
{
	namespace Zone
	{
		class Session;

		namespace Game
		{
			template<class T>
			class GridObject;
		}
	}
	namespace Models
	{
		namespace Character
		{
			class Character;
		}
	}
}
using namespace Horizon::Models::Characters;

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Player : public Entity, public GridObject<Player>
{
public:
	Player(uint32_t guid, std::shared_ptr<Character> c);
	~Player();

	/* Character */
	void setCharacter(std::shared_ptr<Character> c) { _character = c; }
	std::shared_ptr<Character> getCharacter() { return _character; }
	
	/* Session */
	void setSession(std::shared_ptr<Horizon::Zone::Session> s) { _session = s; }
	std::shared_ptr<Horizon::Zone::Session> getSession() { return _session; }

private:
	std::shared_ptr<Character> _character;
	std::shared_ptr<Horizon::Zone::Session> _session;
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP */
