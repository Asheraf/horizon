#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP

#include "../GridDefinitions.hpp"
#include "GridNotifierPredicates.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/Skill/Skill.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Homunculus.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Mercenary.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Elemental.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Hostile/Monster.hpp"

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
    void Visit(GridRefManager<NPC> &m) { update(m); }
    void Visit(GridRefManager<Elemental> &m) { update(m); }
    void Visit(GridRefManager<Homunculus> &m) { update(m); }
    void Visit(GridRefManager<Mercenary> &m) { update(m); }
    void Visit(GridRefManager<Pet> &m) { update(m); }
    void Visit(GridRefManager<Monster> &m) { update(m); }
    void Visit(GridRefManager<Skill> &m) { update(m); }

	template <typename NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridViewPortUpdater
{
	std::shared_ptr<Player> _player;

	GridViewPortUpdater(std::shared_ptr<Player> player) : _player(player) { }

	template <class T>
	void update(GridRefManager<T> &m)
	{
		for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
			if (iter->source()->get_guid() == _player->get_guid())
				continue;
			_player->add_entity_to_viewport(static_cast<Entity *>(iter->source()));
		}
	}

	void Visit(GridRefManager<Player> &m) { update(m); }
	void Visit(GridRefManager<NPC> &m) { update(m); }
	void Visit(GridRefManager<Elemental> &m) { update(m); }
	void Visit(GridRefManager<Homunculus> &m) { update(m); }
	void Visit(GridRefManager<Mercenary> &m) { update(m); }
	void Visit(GridRefManager<Pet> &m) { update(m); }
	void Visit(GridRefManager<Monster> &m) { update(m); }
	void Visit(GridRefManager<Skill> &m) { update(m); }

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP */
