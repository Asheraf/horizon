
#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP

#include "Server/Zone/Game/Entities/Unit/Unit.hpp"

namespace Horizon
{
	namespace Zone
	{
		class ZoneSession;

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
			class Position;
		}
	}
}

namespace Horizon
{
namespace Zone
{
namespace Game
{
namespace Entities
{
class Player : public std::enable_shared_from_this<Player>, public Unit, public GridObject<Player>
{
public:
	Player(uint32_t guid, std::shared_ptr<ZoneSession> session);
	Player(uint32_t guid, MapCoords mcoords, std::shared_ptr<ZoneSession> session);
	Player(uint32_t guid, MapCoords mcoords, GridCoords gcoords, std::shared_ptr<ZoneSession> session);
	~Player();

	/* Character */
	std::shared_ptr<Horizon::Models::Character::Character> get_character();

	/* Session */
	void set_session(std::weak_ptr<ZoneSession> session) { _session.swap(session); }
	std::shared_ptr<ZoneSession> get_session() { return _session.lock(); }

	virtual void initialize() override;

	/* */
	void update(uint32_t diff) override;

	/* */
	void update_position(uint16_t x, uint16_t y) override;
	void update_status() override;
	void stop_movement() override;
	void update_viewport() override;

	void add_entity_to_viewport(Entity *entity);

private:
	std::weak_ptr<ZoneSession> _session;
};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYER_HPP */
