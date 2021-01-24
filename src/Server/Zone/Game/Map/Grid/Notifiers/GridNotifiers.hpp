/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP

#include "Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/Entities/Skill/Skill.hpp"
#include "Server/Zone/Game/Entities/NPC/NPC.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Homunculus.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Mercenary.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Elemental.hpp"
#include "Server/Zone/Game/Entities/Creature/Companion/Pet.hpp"
#include "Server/Zone/Game/Entities/Creature/Hostile/Monster.hpp"
#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifierPredicates.hpp"

#define entity_ns(class) Horizon::Zone::Entities::class
struct GridViewPortUpdater
{
	std::weak_ptr<Horizon::Zone::Entity> _entity;

	GridViewPortUpdater(std::weak_ptr<Horizon::Zone::Entity> entity) : _entity(entity) { }

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
	std::weak_ptr<Horizon::Zone::Entity> _entity;
	entity_viewport_notification_type _notif_type;

	GridEntityExistenceNotifier(std::weak_ptr<Horizon::Zone::Entity> entity, entity_viewport_notification_type notif_type)
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
	std::weak_ptr<Horizon::Zone::Entity> _result;
	GUIDCheckPredicate _predicate;

	GridEntitySearcher(uint32_t guid)
	: _predicate(guid)
	{ }

	std::weak_ptr<Horizon::Zone::Entity> get_result() { return _result; }

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

struct GridNPCTrigger
{
	std::weak_ptr<Horizon::Zone::Entity> _source;
	RangeCheckPredicate _predicate;

	GridNPCTrigger(std::weak_ptr<Horizon::Zone::Entity> entity)
	: _source(entity), _predicate(entity)
	{ }

	template <class T>
	void check_and_trigger(GridRefManager<T> &m);

	void Visit(GridRefManager<entity_ns(NPC)> &m) { check_and_trigger(m); }

	template<class NOT_INTERESTED>
	void Visit(GridRefManager<NOT_INTERESTED> &) { }
};

#undef entity_ns

#include "GridNotifiersImpl.hpp"

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERS_HPP */
