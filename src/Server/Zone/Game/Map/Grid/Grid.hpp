

#ifndef HORIZON_ZONE_GAME_GRID_HPP
#define HORIZON_ZONE_GAME_GRID_HPP

#include "Container/GridReferenceContainer.hpp"
#include "Container/GridReferenceContainerVisitor.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include <cassert>

template
<
	class ACTIVE_OBJECT,
	class ZONE_OBJECT_TYPES
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
	void Visit(GridReferenceContainerVisitor<T, GridReferenceContainer<ZONE_OBJECT_TYPES>> &visitor)
	{
		visitor.Visit(_container);
	}

private:
	GridReferenceContainer<ZONE_OBJECT_TYPES> _container;
};

#endif /* HORIZON_ZONE_GAME_GRID_HPP */
