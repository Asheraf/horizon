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

#ifndef HORIZON_ZONE_GAME_GRID_NOTIFIERS_GRIDLOADER_HPP
#define HORIZON_ZONE_GAME_GRID_NOTIFIERS_GRIDLOADER_HPP

class GridLoader
{
public:
	GridLoader(std::shared_ptr<GridHolderType> grid, std::shared_ptr<Map> map, std::shared_ptr<Cell> cell)
	: _grid(grid), _map(map), _cell(cell)
	{
		//
	}

	void Visit(GridRefManager<Monster> &m)
	{
		// Do stuff here.
	}

	void Visit(GridRefManager<MVP> &m)
	{
		// Do stuff here.
	}

private:
	std::shared_ptr<GridHolderType> _grid;
	std::shared_ptr<Map> _map;
	std::shared_ptr<Cell> _cell
};

#endif /* HORIZON_ZONE_GAME_GRID_NOTIFIERS_GRIDLOADER_HPP */
