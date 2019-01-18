#ifndef HORIZON_ZONE_GAME_GRIDHOLDER_HPP
#define HORIZON_ZONE_GAME_GRIDHOLDER_HPP

#include "GridDefinitions.hpp"
#include "Grid.hpp"
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

	GridHolder(int width, int height)
	: _height(height), _width(width),
	  _grids(boost::extents[width][height])
	{
	}

	~GridHolder()
	{
		for (uint16_t x = 0; x < _width; ++x)
			for (uint16_t y = 0; y < _height; ++y)
				delete _grids[x][y];
	}

	GridType *get_grid(GridCoords &coords)
	{
		assert(coords.x() < _width);
		assert(coords.y() < _height);

		return _grids[coords.x()][coords.y()];
	}

	void initialize_grid(GridCoords &coords, bool unused)
	{
		assert(coords.x() < _width);
		assert(coords.y() < _height);

		_grids[coords.x()][coords.y()] = unused ? nullptr : new GridType();
	}

	uint16_t height() { return _height; }
	uint16_t width() { return _width; }

	template<class CONTAINER_TYPE, class VISITOR>
	void VisitAll(GridReferenceContainerVisitor<GridReferenceContainer<CONTAINER_TYPE>, VISITOR> &visitor)
	{
		for (uint16_t x = 0; x < _width; ++x) {
			for (uint16_t y = 0; y < _height; ++y) {
				GridCoords c(x, y);
				get_grid(c).Visit(visitor);
			}
		}
	}

	template<class CONTAINER_TYPE, class VISITOR>
	void Visit(GridCoords coords, GridReferenceContainerVisitor<GridReferenceContainer<CONTAINER_TYPE>, VISITOR> &visitor)
	{
		get_grid(coords).Visit(visitor);
	}

private:
	uint16_t _height{0}, _width{0};
	boost::multi_array<GridType *, 2> _grids;
};

#endif /* HORIZON_ZONE_GAME_GRIDHOLDER_HPP */
