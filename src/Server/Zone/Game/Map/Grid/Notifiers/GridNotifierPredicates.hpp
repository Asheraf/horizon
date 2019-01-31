//
//  GridNotifierPredicates.hpp
//  Horizon
//
//  Created by SagunKho on 28/01/2019.
//
#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERPREDICATES_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERPREDICATES_HPP

#include "Server/Zone/Game/Entities/Entity.hpp"

using namespace Horizon::Zone::Game;

class AllEntitiesInRange
{
	std::shared_ptr<Entity> _entity;
	uint8_t _range;

public:
	AllEntitiesInRange(Entity *entity, uint8_t range)
	: _entity(entity), _range(range)
	{}

	bool operator()(Entity *target)
	{
		if (_entity->is_in_range_of(std::shared_ptr<Entity>(target), _range))
			return true;

		return false;
	}
};

#endif /* GRIDNOTIFIERPREDICATES_HPP */
