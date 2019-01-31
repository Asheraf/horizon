#ifndef HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP
#define HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP

#include "Core/Structures/TypeList.hpp"
#include "Server/Zone/Game/Map/Coordinates.hpp"
#include "Grid/Container/GridReferenceContainer.hpp"

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

using namespace Horizon::Zone::Game::Entities;

template <class ACTIVE_OBJECT, class ZONE_OBJECT_TYPES>
class GridHolder;

#define MAX_CELLS_PER_GRID 32
// Max Cells in a map are 416 and so 26 * 16.
#define MAX_GRIDS_PER_MAP 13
#define MAX_CELLS_PER_MAP MAX_CELLS_PER_GRID * MAX_GRIDS_PER_MAP
#define GRID_UPDATE_DELAY 60000 ///< In milliseconds. (@TODO change to config)

typedef TYPELIST_8(Player, NPC, Elemental, Homunculus, Mercenary, Pet, Monster, Skill) AllEntityTypes;

typedef GridHolder<Player, AllEntityTypes> GridHolderType;

typedef Coordinates<MAX_GRIDS_PER_MAP> GridCoords;
typedef Coordinates<MAX_CELLS_PER_MAP> MapCoords;

typedef GridReferenceContainer<AllEntityTypes> MapEntityContainer;

#endif /* HORIZON_ZONE_GAME_GRIDDEFINITIONS_HPP */
