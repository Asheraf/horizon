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
 * Base Author - Sagun Khosla. <sagunxp@gmail.com>
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#include "Map.hpp"
#include "Core/Logging/Logger.hpp"
#include "Utility/Utility.hpp"
#include "Core/Multithreading/WorkerThreadPool.hpp"
#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"
#include "Grid/Notifiers/GridNotifiers.hpp"
#include "Grid/Container/GridReferenceContainer.hpp"
#include "Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Grid/Grid.hpp"

#include <future>
#include <type_traits>
#include <functional>

Horizon::Zone::Game::Map::Map(std::string const &name, uint16_t width, uint16_t height, std::vector<uint8_t> const &cells)
: _name(name), _width(width), _height(height),
  _grid_width((width / MAX_GRID_WIDTH)), _grid_height((height / MAX_GRID_WIDTH)),
  _cells(boost::extents[width][height]),
  _gridholder(_grid_width, _grid_height),
  _pathfinder(new AStar::Generator({width, height}, std::bind(&Map::checkCollisionInPath, this, std::placeholders::_1, std::placeholders::_2), true, &AStar::Heuristic::manhattan))
{
	for (int y = 0, idx = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			_cells[x][y] = new Cell(cells.at(idx++));
}

bool Horizon::Zone::Game::Map::checkCollisionInPath(uint16_t x, uint16_t y)
{
	if (x < 0 || y < 0 || x > _width || y > _height)
		return false;
	if (_cells[x][y]->isWalkable())
		return false;

	return true;
}

Horizon::Zone::Game::Map::~Map()
{
	CoreLog->info("Performing cleanup on map '{}'...", _name);

	for (int x = 0; x < _width; ++x)
		for (int y = 0; y < _height; ++y)
			std::free(_cells[x][y]);
}

bool Horizon::Zone::Game::Map::ensureGrid(GridCoords coords)
{
	_gridholder.initialize_grid(coords, false);
	return true;
}

void Horizon::Zone::Game::Map::ensureAllGrids()
{
	for (int x = 0; x < _grid_width; x++) {
		for (int y = 0; y < _grid_height; y++) {
			ensureGrid(GridCoords(x, y));
		}
	}
}

void Horizon::Zone::Game::Map::update(uint32_t diff)
{
	GridUpdater updater(diff);
	GridReferenceContainerVisitor<MapEntityContainer, GridUpdater> map_updater(updater);
	
	for (int x = 0; x < _grid_width; x++) {
		for (int y = 0; y < _grid_height; y++) {
			GridCoords gcoords(x, y);
			if (_gridholder.get_grid(gcoords) != nullptr)
				_gridholder.get_grid(gcoords)->Visit(map_updater);
		}
	}
}
