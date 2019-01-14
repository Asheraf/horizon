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
#include "Path/AStar.hpp"

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
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	GridHolderType &getGridHolder() { return _gridholder; }
	bool ensureGrid(GridCoords coords);
	void ensureAllGrids();

	bool checkCollisionInPath(uint16_t x, uint16_t y);

	template <class T>
	bool addEntityToMap(T *entity, MapCoords coords);

	AStar *get_pathfinder() { return _pathfinder; }

	void update(uint32_t diff);
	
private:
	std::string _name{""};
	uint16_t _width{0}, _height{0};
	uint16_t _grid_width{0}, _grid_height{0};
	boost::multi_array<Cell *, 2> _cells;
	GridHolderType _gridholder;
	boost::mutex _grid_init_mutex;
	// Path Finding 
	AStar *_pathfinder;
};
}
}
}

template <class T>
bool Horizon::Zone::Game::Map::addEntityToMap(T *entity, MapCoords mcoords)
{
	GridCoords gcoords(mcoords.x() / MAX_CELLS_PER_GRID, mcoords.y() / MAX_CELLS_PER_GRID);
	_gridholder.getGrid(gcoords)->addObject<T>(&*entity);
	entity->set_grid_coords(gcoords);
	return true;
}

#endif /* HORIZON_ZONE_GAME_MAP_HPP */
