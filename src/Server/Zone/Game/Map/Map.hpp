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
#include "Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Path/AStar.hpp"
#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"

#include <cassert>
#include <unordered_map>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include <boost/multi_array.hpp>

namespace Horizon
{
namespace Zone
{
namespace Game
{
class Map
{
friend class MapManager;
public:
	Map(std::string const &name, uint16_t width, uint16_t height, std::vector<uint8_t> const &cells);
	~Map();

	std::string get_name() { return _name; }
	int getArea() { return _width * _height; }
	uint16_t getWidth() { return _width; }
	uint16_t getHeight() { return _height; }
	GridHolderType &getGridHolder() { return _gridholder; }
	bool ensureGrid(GridCoords coords);
	void ensureAllGrids();

	bool checkCollisionInPath(uint16_t x, uint16_t y);

	template <class T>
	bool addEntityToMap(T *entity, MapCoords coords);

	template<class T, class CONTAINER>
	void visit(GridCoords const &grid, GridReferenceContainerVisitor<T, CONTAINER> &visitor);

	template<class T, class CONTAINER>
	void visit(GridCoords const &lower_bound, GridCoords const &upper_bound, GridReferenceContainerVisitor<T, CONTAINER> &visitor);

	AStar::Generator &get_pathfinder() { return _pathfinder; }

	void update(uint32_t diff);
	
private:
	std::string _name{""};
	uint16_t _width{0}, _height{0};
	GridCoords _grid_bounds;
	Cell _cells[MAX_CELLS_PER_MAP][MAX_CELLS_PER_MAP]{{0}};
	GridHolderType _gridholder;
	AStar::Generator _pathfinder;
};
}
}
}

template <class T>
bool Horizon::Zone::Game::Map::addEntityToMap(T *entity, MapCoords mcoords)
{
	GridCoords gcoords(mcoords.x() / MAX_CELLS_PER_GRID, mcoords.y() / MAX_CELLS_PER_GRID);
	_gridholder.get_grid(gcoords).add_object<T>(entity);
	entity->set_grid_coords(gcoords);
	return true;
}

template<class T, class CONTAINER>
inline void Horizon::Zone::Game::Map::visit(GridCoords const &grid, GridReferenceContainerVisitor<T, CONTAINER> &visitor)
{
	_gridholder.get_grid(grid).visit(visitor);
}

template<class T, class CONTAINER>
inline void Horizon::Zone::Game::Map::visit(GridCoords const &lower_bound, GridCoords const &upper_bound, GridReferenceContainerVisitor<T, CONTAINER> &visitor)
{
	for (int y = upper_bound.y(); y >= lower_bound.y(); --y) {
		for (int x = lower_bound.x(); x <= upper_bound.x(); ++x) {
			visit(GridCoords(x, y), visitor);
		}
	}
}

#endif /* HORIZON_ZONE_GAME_MAP_HPP */
