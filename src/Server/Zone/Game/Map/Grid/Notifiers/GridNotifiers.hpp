#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP

#include "GridNotifierPredicates.hpp"
#include "Server/Zone/Game/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Unit/Skill/Skill.hpp"
#include "Server/Zone/Game/Entities/Unit/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Homunculus.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Mercenary.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Elemental.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Unit/Creature/Hostile/Monster.hpp"

#define entity_ns(class) Horizon::Zone::Game::Entities::class
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
    void Visit(GridRefManager<entity_ns(NPC)> &m) { update(m); }
    void Visit(GridRefManager<entity_ns(Elemental)> &m) { update(m); }
    void Visit(GridRefManager<entity_ns(Homunculus)> &m) { update(m); }
    void Visit(GridRefManager<entity_ns(Mercenary)> &m) { update(m); }
    void Visit(GridRefManager<entity_ns(Pet)> &m) { update(m); }
    void Visit(GridRefManager<entity_ns(Monster)> &m) { update(m); }
    void Visit(GridRefManager<entity_ns(Skill)> &m) { update(m); }

	template <typename NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridViewPortUpdater
{
	std::weak_ptr<Horizon::Zone::Game::Entity> _entity;

	GridViewPortUpdater(std::weak_ptr<Horizon::Zone::Game::Entity> entity) : _entity(entity) { }

	template <class T>
	void update(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(NPC)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(Elemental)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(Homunculus)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(Mercenary)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(Pet)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(Monster)> &m) { update(m); }
	void Visit(GridRefManager<entity_ns(Skill)> &m) { update(m); }

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridMovementNotifier
{
	std::weak_ptr<Horizon::Zone::Game::Entity> _entity;

	GridMovementNotifier(std::weak_ptr<Horizon::Zone::Game::Entity> entity) : _entity(entity) { }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m) { notify(m); }

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

template <typename ZC_PACKET_T>
struct GridPlayerNotifier
{
	std::weak_ptr<Horizon::Zone::Game::Entity> _player;
	ZC_PACKET_T _pkt;
	player_notifier_types _type;

	GridPlayerNotifier(ZC_PACKET_T &pkt, std::weak_ptr<Horizon::Zone::Game::Entity> player, player_notifier_types type = GRID_NOTIFY_AREA)
	: _player(player), _pkt(pkt), _type(type)
	{ }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m) { notify(m); }

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};
#undef e

#include "GridNotifiersImpl.hpp"

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP */
