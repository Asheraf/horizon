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
  _grid_width((width / MAX_CELLS_PER_GRID)), _grid_height((height / MAX_CELLS_PER_GRID)),
  _cells(boost::extents[width][height]),
  _gridholder(_grid_width, _grid_height),
  _pathfinder(new AStar({width, height}, true, &AStar::Heuristic::manhattan,
						std::bind(&Map::checkCollisionInPath, this, std::placeholders::_1, std::placeholders::_2)))
{
	for (int y = 0, idx = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			_cells[x][y] = new Cell(cells.at(idx++));
}

bool Horizon::Zone::Game::Map::checkCollisionInPath(uint16_t x, uint16_t y)
{
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
	int unusable_cells = 0;

	for (uint32_t grid_x = coords.x() * MAX_CELLS_PER_GRID; grid_x < coords.x() * MAX_CELLS_PER_GRID + MAX_CELLS_PER_GRID; grid_x++)
		for (uint32_t grid_y = coords.y() * MAX_CELLS_PER_GRID; grid_y < coords.y() * MAX_CELLS_PER_GRID + MAX_CELLS_PER_GRID; grid_y++)
			if (!_cells[grid_x][grid_y]->isWalkable() && !_cells[grid_x][grid_y]->isShootable())
				unusable_cells++;

	_grid_init_mutex.lock();
	_gridholder.initializeGrid(coords, (unusable_cells == MAX_CELLS_PER_GRID * MAX_CELLS_PER_GRID));
	_grid_init_mutex.unlock();

	return true;
}

void Horizon::Zone::Game::Map::ensureAllGrids()
{
#define MAX_THREADS 4
	WorkerThreadPool pool;
	std::future<typename std::result_of<std::function<void()>()>::type> fut[MAX_THREADS];

	for (int x = 0; x < _grid_width; x++) {
		for (int y = 0; y < _grid_height;) {
			GridCoords coords(x, y);
			int workers = 0;

			while (workers < MAX_THREADS && y < _grid_height) {
				fut[workers++] = pool.submit(
					[this, coords] ()
					{
						ensureGrid(coords);
					});
				y++;
			}

			workers = 0;

			while (workers < MAX_THREADS && y < _grid_height)
				fut[workers++].wait();
		}
	}
#undef MAX_THREADS
}

void Horizon::Zone::Game::Map::update(uint32_t diff)
{
	GridUpdater updater(diff);
	GridReferenceContainerVisitor<MapEntityContainer, GridUpdater> map_updater(updater);
	
	for (int x = 0; x < _grid_width; x++) {
		for (int y = 0; y < _grid_height; y++) {
			GridCoords gcoords(x, y);
			if (_gridholder.getGrid(gcoords) != nullptr)
				_gridholder.getGrid(gcoords)->Visit(map_updater);
		}
	}
}
