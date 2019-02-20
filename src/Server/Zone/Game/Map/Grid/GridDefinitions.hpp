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

#ifndef HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP
#define HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP

#include "Core/Structures/TypeList.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include <cstdint>

namespace Horizon
{
	namespace Zone
	{
		namespace Game
		{
			namespace Entities
			{
				class Player;
				class NPC;
				class Elemental;
				class Homunculus;
				class Mercenary;
				class Pet;
				class Monster;
				class Skill;
			}
		}
	}
}

template <class ACTIVE_OBJECT, class ZONE_OBJECT_TYPES>
class GridHolder;

template <uint16_t MAX_COORDINATES>
class Coordinates;

template<class OBJECT_TYPES>
class GridReferenceContainer;

#define MAX_CELLS_PER_GRID 32
// Max Cells in a map are 416 and so 26 * 16.
#define MAX_GRIDS_PER_MAP 13
#define MAX_CELLS_PER_MAP MAX_CELLS_PER_GRID * MAX_GRIDS_PER_MAP

#define entity_ns(e) Horizon::Zone::Game::Entities::e
typedef TYPELIST_8(entity_ns(Player),
entity_ns(NPC),
entity_ns(Elemental),
entity_ns(Homunculus),
entity_ns(Mercenary),
entity_ns(Pet),
entity_ns(Monster),
entity_ns(Skill))
AllEntityTypes;
typedef GridHolder<entity_ns(Player), AllEntityTypes> GridHolderType;
#undef entity_ns

typedef Coordinates<MAX_GRIDS_PER_MAP> GridCoords;
typedef Coordinates<MAX_CELLS_PER_MAP> MapCoords;

typedef GridReferenceContainer<AllEntityTypes> MapEntityContainer;

#endif /* HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP */
