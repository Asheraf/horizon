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

#ifndef HORIZON_ZONE_GAME_MAP_HPP
#define HORIZON_ZONE_GAME_MAP_HPP

#include "Path/AStar.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/Grid/GridHolder.hpp"

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
	Map(std::weak_ptr<MapThreadContainer>, std::string const &, uint16_t, uint16_t, std::vector<uint8_t> const &);
	~Map();

	std::shared_ptr<MapThreadContainer> get_map_container() { return _container.lock(); }

	std::string const &get_name() { return _name; }

	int get_area() { return _width * _height; }

	uint16_t get_width() { return _width; }
	uint16_t get_height() { return _height; }

	GridHolderType &getGridHolder() { return _gridholder; }

	bool ensure_grid(GridCoords coords);
	void ensure_all_grids();

	bool is_obstruction(uint16_t x, uint16_t y);

	MapCoords get_random_coords()
	{
		uint16_t x = 0;
		uint16_t y = 0;

		do {
			x = rand() % _width;
			y = rand() % _height;
		} while (is_obstruction(x, y));

		return { x, y };
	}

	template <class T>
	bool ensure_grid_for_entity(T *entity, MapCoords coords);

	template<class T, class CONTAINER>
	void visit(GridCoords const &grid, GridReferenceContainerVisitor<T, CONTAINER> &visitor);

	template<class T, class CONTAINER>
	void visit(GridCoords const &lower_bound, GridCoords const &upper_bound, GridReferenceContainerVisitor<T, CONTAINER> &visitor);

	template<class T, class CONTAINER>
	void visit_in_range(MapCoords const &map_coords, GridReferenceContainerVisitor<T, CONTAINER> &visitor, uint16_t range = MAX_VIEW_RANGE);

	AStar::Generator &get_pathfinder() { return _pathfinder; }
	
private:
	std::weak_ptr<MapThreadContainer> _container;
	std::string _name{""};
	uint16_t _width{0}, _height{0};
	GridCoords _max_grids;
	Cell _cells[MAX_CELLS_PER_MAP][MAX_CELLS_PER_MAP]{{0}};
	GridHolderType _gridholder;
	AStar::Generator _pathfinder;
};
}
}
}

template <class T>
bool Horizon::Zone::Game::Map::ensure_grid_for_entity(T *entity, MapCoords mcoords)
{
	std::string const &new_map_name = entity->get_map()->get_name();
	GridCoords new_gcoords = mcoords.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>();

	if (new_map_name.compare(get_name()) == 0 && entity->get_grid_coords() == new_gcoords)
		return false;

	if (entity->has_valid_grid_reference())
		entity->remove_grid_reference();

	entity->set_grid_coords(new_gcoords);

	_gridholder.get_grid(new_gcoords).template add_object(entity);
	
	return true;
}

template<class T, class CONTAINER>
inline void Horizon::Zone::Game::Map::visit(GridCoords const &grid, GridReferenceContainerVisitor<T, CONTAINER> &visitor)
{
	_gridholder.get_grid(grid).visit(visitor);
}

template<class T, class CONTAINER>
inline void Horizon::Zone::Game::Map::visit_in_range(MapCoords const &map_coords, GridReferenceContainerVisitor<T, CONTAINER> &visitor, uint16_t range)
{
	MapCoords lower_bounds = map_coords.at_range<MAX_CELLS_PER_MAP>(-range);
	MapCoords upper_bounds = map_coords.at_range<MAX_CELLS_PER_MAP>(range);

	visit(lower_bounds.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>(), upper_bounds.scale<MAX_CELLS_PER_GRID, MAX_GRIDS_PER_MAP>(), visitor);
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
