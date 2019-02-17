/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
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
