#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP

#include "../GridDefinitions.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Skill/Skill.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/NPC/NPC.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Companion/Homunculus.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Companion/Mercenary.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Companion/Elemental.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Hostile/Monster.hpp"
#include "Server/Zone/Game/Models/Entities/Unit/Creature/Hostile/MVP.hpp"

struct GridUpdater
{
    uint32_t _diff;

    GridUpdater(uint32_t diff) : _diff(diff) { }

    template <class T>
	void update(GridRefManager<T> &m)
    {
		for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter)
			iter->source()->update(_diff);
    }

    // Player, NPC, Elemental, Homunculus, Mercenary, Pet, Monster, MVP, Skill
    void Visit(GridRefManager<Player> &m) { update(m); }
    void Visit(GridRefManager<NPC> &m) { update(m); }
    void Visit(GridRefManager<Elemental> &m) { update(m); }
    void Visit(GridRefManager<Homunculus> &m) { update(m); }
    void Visit(GridRefManager<Mercenary> &m) { update(m); }
    void Visit(GridRefManager<Pet> &m) { update(m); }
    void Visit(GridRefManager<Monster> &m) { update(m); }
    void Visit(GridRefManager<MVP> &m) { update(m); }
    void Visit(GridRefManager<Skill> &m) { update(m); }
};

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP */
