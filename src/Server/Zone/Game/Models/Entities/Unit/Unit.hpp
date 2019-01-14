#ifndef HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP
#define HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP

#include "Server/Zone/Game/Models/Entities/Entity.hpp"
#include "Server/Zone/Game/Map/Path/AStar.hpp"


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
	Unit(uint32_t guid, entity_type type);
	Unit(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords);
	Unit(uint32_t guid, entity_type type, std::string const &map_name, MapCoords mcoords, GridCoords gcoords);
	~Unit();

	virtual void initialize() override;
	virtual bool move_to_pos(uint16_t x, uint16_t y);
	void schedule_movement(MapCoords mcoords);
	void move();
	virtual void update(uint32_t diff) override;
	virtual void update_status() = 0;
	virtual void update_position(uint16_t x, uint16_t y) = 0;
	virtual void stop_movement() = 0;
private:
	MapCoords _dest_changed_pos{0, 0}, _dest_pos{0, 0}, _current_dest_pos{0, 0};
	AStar::CoordinateList _walk_path;
	uint16_t _walk_step{0};
	bool _is_walking{false};

};
}
}
}
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_UNIT_HPP */
