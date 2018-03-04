
#ifndef HORIZON_ZONE_GAME_CELL_HPP
#define HORIZON_ZONE_GAME_CELL_HPP

#include "Utility/Utility.hpp"
#include "Core/Logging/Logger.hpp"

enum cell_types
{
	CELL_WALKSHOOT_GROUND            = 0,
	CELL_NO_WALKSHOOT_GROUND         = 1,
	// CELL_UNUSED_WALK_SHOOT_GROUND     = 2,
	CELL_WALKSHOOT_WATER             = 3,
	// CELL_UNUSED2_WALK_SHOOT_GROUND    = 4,
	CELL_SHOOTABLE_ONLY              = 5,
	CELL_WALKSHOOT_GROUND2           = 6
};

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Cell
{
public:
    Cell(uint16_t x, uint16_t y)
    : _x(x), _y(y)
    {
    }

    Cell(uint16_t x, uint16_t y, uint8_t type)
    : _x(x), _y(y), _type(type)
    {
		switch (type)
		{
		case 0: setWalkable(); setShootable(); break; // walkable ground
		case 1: break; // non-walkable ground
		case 2: setWalkable(); setShootable(); break; // ???
		case 3: setWalkable(); setShootable(); setWater(); break; // walkable water
		case 4: setWalkable(); setShootable(); break; // ???
		case 5: setShootable(); break; // gap (snipable)
		case 6: setWalkable(); setShootable(); break; // ???
		default:
			CoreLog->info("Unrecognized cell type '{}'\n", type);
			break;
		}
    }

    ~Cell()
    {
        //
    }

    uint16_t x() { return _x; }
    uint16_t y() { return _y; }

    uint8_t type() { return _type; }
    void setType(uint8_t type) { _type = type; }

	bool isWalkable() { return _walkable; }
	void setWalkable() { _walkable = true; }

	bool isShootable() { return _shootable; }
	void setShootable() { _shootable = true; }

	bool isWater() { return _is_water; }
	void setWater() { _is_water = true; }

private:
    uint16_t _x{0}, _y{0};
    uint8_t _type{0};
	bool _walkable{false};
	bool _shootable{false};
	bool _is_water{false};
};
}
}
}

#endif /* HORIZON_ZONE_GAME_CELL_HPP */
