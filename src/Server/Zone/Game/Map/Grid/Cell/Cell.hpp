/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_CELL_HPP
#define HORIZON_ZONE_GAME_CELL_HPP

#include "Utility/Utility.hpp"

namespace Horizon
{
namespace Zone
{
namespace Game
{
#pragma pack(push, 1)
struct Cell
{
public:
    Cell(uint8_t type)
	: _walkable(0), _shootable(0), _is_water(0)
    {
		validateType(type);
    }

	Cell()
	: _walkable(0), _shootable(0), _is_water(0)
	{

	}

    ~Cell()
    {
        //
    }

	void setType(uint8_t type) { validateType(type); }

	void validateType(uint8_t type)
	{
		switch (type)
		{
			case 3: setWater(); // walkable water
			case 0: // walkable ground
			case 2: // ???
			case 4: // ???
			case 6: setWalkable(); // ???
			case 5: setShootable(); // gap (snipable)
			case 1: break; // non-walkable ground

//			case 0: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // walkable ground
//			case 1: cell.walkable = 0; cell.shootable = 0; cell.water = 0; break; // non-walkable ground
//			case 2: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // ???
//			case 3: cell.walkable = 1; cell.shootable = 1; cell.water = 1; break; // walkable water
//			case 4: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // ???
//			case 5: cell.walkable = 0; cell.shootable = 1; cell.water = 0; break; // gap (snipable)
//			case 6: cell.walkable = 1; cell.shootable = 1; cell.water = 0; break; // ???
			default:
				break;
		}
	}

	bool isWalkable() { return _walkable ? true : false; }
	void setWalkable() { _walkable = 1; }

	bool isShootable() { return _shootable ? true : false; }
	void setShootable() { _shootable = 1; }

	bool isWater() { return _is_water ? true : false; }
	void setWater() { _is_water = 1; }

private:
	unsigned _walkable : 1;
	unsigned _shootable : 1;
	unsigned _is_water : 1;
};
#pragma pack(pop)
}
}
}

#endif /* HORIZON_ZONE_GAME_CELL_HPP */
