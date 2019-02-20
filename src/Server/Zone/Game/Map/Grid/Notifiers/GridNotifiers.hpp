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

#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP

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
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifierPredicates.hpp"

#define entity_ns(class) Horizon::Zone::Game::Entities::class
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

struct GridEntityExistenceNotifier
{
	std::weak_ptr<Horizon::Zone::Game::Entity> _entity;
	entity_viewport_notification_type _notif_type;

	GridEntityExistenceNotifier(std::weak_ptr<Horizon::Zone::Game::Entity> entity, entity_viewport_notification_type notif_type)
	: _entity(entity), _notif_type(notif_type)
	{ }

	template <class T>
	void notify(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m) { notify(m); }

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

struct GridEntitySearcher
{
	std::weak_ptr<Horizon::Zone::Game::Entity> _result;
	GUIDCheckPredicate _predicate;

	GridEntitySearcher(uint32_t guid)
	: _predicate(guid)
	{ }

	std::weak_ptr<Horizon::Zone::Game::Entity> get_result() { return _result; }

	template <class T>
	void search(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(Player)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(NPC)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(Elemental)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(Homunculus)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(Mercenary)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(Pet)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(Monster)> &m) { search(m); }
	void Visit(GridRefManager<entity_ns(Skill)> &m) { search(m); }

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
