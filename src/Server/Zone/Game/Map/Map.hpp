/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_MAP_HPP
#define HORIZON_ZONE_GAME_MAP_HPP

#include "Grid/GridDefinitions.hpp"
#include "Grid/GridHolder.hpp"

#include <cassert>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <boost/multi_array.hpp>
#include <boost/thread.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Cell;
class Map
{
friend class MapManager;
public:
	Map(std::string const &name, uint16_t width, uint16_t height, std::vector<uint8_t> const &cells);
	~Map();

	int getArea() { return _width * _height; }

	bool ensureGrid(GridCoords coords);
	void ensureAllGrids();

	bool addPlayerToMap(std::shared_ptr<Player> player, MapCoords coords);

private:
	std::string _name{""};
	uint16_t _width{0}, _height{0};
	uint16_t _grid_width{0}, _grid_height{0};
	boost::multi_array<std::shared_ptr<Cell>, 2> _cells;
	GridHolderType _grid;
	boost::mutex _grid_link_mutex;
};
}
}
}

#endif /* HORIZON_ZONE_GAME_MAP_HPP */
