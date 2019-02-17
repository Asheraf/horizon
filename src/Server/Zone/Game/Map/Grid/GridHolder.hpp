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

#ifndef HORIZON_ZONE_GAME_GRIDHOLDER_HPP
#define HORIZON_ZONE_GAME_GRIDHOLDER_HPP

#include "GridDefinitions.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Server/Zone/Game/Map/Grid/Grid.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"

#include <memory>
#include <boost/multi_array.hpp>

template
<
	class ACTIVE_OBJECT,
	class ZONE_OBJECT_TYPES
>
class GridHolder
{
friend class Horizon::Zone::Game::MapManager;
public:
	typedef Grid<ACTIVE_OBJECT, ZONE_OBJECT_TYPES> GridType;

	GridHolder(GridCoords bounds)
	: _bounds(bounds)
	{
	}

	~GridHolder()
	{
	}

	GridType &get_grid(GridCoords const &coords)
	{
		assert(coords.x() < _bounds.x());
		assert(coords.y() < _bounds.y());

		return _grids[coords.x()][coords.y()];
	}

	uint16_t height() { return _bounds.y(); }
	uint16_t width() { return _bounds.x(); }

	template<class VISITOR, class CONTAINER_TYPE>
	void visit_all(GridReferenceContainerVisitor<VISITOR, GridReferenceContainer<CONTAINER_TYPE>> &visitor)
	{
		for (uint16_t x = 0; x < _bounds.x(); ++x) {
			for (uint16_t y = 0; y < _bounds.y(); ++y) {
				GridCoords c(x, y);
				get_grid(c).visit(visitor);
			}
		}
	}

	template<class VISITOR, class CONTAINER_TYPE>
	void visit(GridCoords coords, GridReferenceContainerVisitor<VISITOR, GridReferenceContainer<CONTAINER_TYPE>> &visitor)
	{
		get_grid(coords).Visit(visitor);
	}

private:
	GridCoords _bounds;
	GridType _grids[MAX_GRIDS_PER_MAP][MAX_GRIDS_PER_MAP];
};

#endif /* HORIZON_ZONE_GAME_GRIDHOLDER_HPP */
