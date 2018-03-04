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

#include <future>
#include <type_traits>
#include <functional>

Horizon::Zone::Game::Map::Map(std::string const &name, uint16_t width, uint16_t height, std::vector<uint8_t> const &cells)
: _name(name), _width(width), _height(height),
  _grid_width((width / MAX_CELLS_PER_GRID)), _grid_height((height / MAX_CELLS_PER_GRID)),
  _cells(boost::extents[_width][_height]),
  _grid(_grid_width, _grid_height)
{
	for (int x = 0, idx = 0; x < width; ++x)
		for (int y = 0; y < height; ++y)
			_cells[x][y] = std::make_shared<Cell>(x, y, cells.at(idx++));
}

Horizon::Zone::Game::Map::~Map()
{

}

bool Horizon::Zone::Game::Map::ensureGrid(GridCoords coords)
{
	int unusable_cells = 0;

	for (uint32_t grid_x = coords.x() * MAX_CELLS_PER_GRID; grid_x < coords.x() * MAX_CELLS_PER_GRID + MAX_CELLS_PER_GRID; grid_x++)
		for (uint32_t grid_y = coords.y() * MAX_CELLS_PER_GRID; grid_y < coords.y() * MAX_CELLS_PER_GRID + MAX_CELLS_PER_GRID; grid_y++)
			if (_cells[grid_x][grid_y]->type() == CELL_NO_WALKSHOOT_GROUND)
				unusable_cells++;

	if (unusable_cells == MAX_CELLS_PER_GRID * MAX_CELLS_PER_GRID)
		return false;

	_grid.initializeGrid(coords);

	return true;
}

bool Horizon::Zone::Game::Map::addPlayerToMap(std::shared_ptr<Player> player, MapCoords coords)
{
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

			workers = 0;
		}
	}
#undef MAX_THREADS
}
