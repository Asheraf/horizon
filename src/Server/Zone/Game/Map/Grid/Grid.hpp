

#ifndef HORIZON_ZONE_GAME_GRID_HPP
#define HORIZON_ZONE_GAME_GRID_HPP

#include "Container/GridReferenceContainer.hpp"
#include "Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include <cassert>

template
<
	class ACTIVE_OBJECT,
	class GRID_OBJECT_TYPES
>
class Grid
{
friend class Horizon::Zone::Game::MapManager;
public:
	template <class SPECIFIC_OBJECT>
	void addObject(SPECIFIC_OBJECT *obj)
	{
		_container.template insert<SPECIFIC_OBJECT>(obj);
		assert(obj->valid());
	}

	template <class T>
	void Visit(GridReferenceContainerVisitor<GridReferenceContainer<GRID_OBJECT_TYPES>, T> &visitor)
	{
		visitor.Visit(_container);
	}

	/** Returns the number of object within the grid.
	 */
	template <class T>
	uint32_t getObjectCount() const { return uint32_t(_container.template count<T>()); }

private:
	GridReferenceContainer<GRID_OBJECT_TYPES> _container;
};

#endif /* HORIZON_ZONE_GAME_GRID_HPP */
