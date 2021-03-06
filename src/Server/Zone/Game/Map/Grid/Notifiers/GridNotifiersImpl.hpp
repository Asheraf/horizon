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

#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERSIMPL_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERSIMPL_HPP

#include "Server/Zone/Game/Map/Script/ScriptManager.hpp"
#include "Server/Common/Definitions/NPCDefinitions.hpp"

template <class T>
void GridViewPortUpdater::update(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Entities;

	if (_entity.expired())
		return;

	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		std::shared_ptr<Player> pl = _entity.lock()->template downcast<Player>();

		if (iter->source() == nullptr || iter->source()->guid() == pl->guid())
			continue;

		pl->add_entity_to_viewport(iter->source()->shared_from_this());
	}
}


template <class T>
void GridEntityExistenceNotifier::notify(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Entities;

	std::shared_ptr<Horizon::Zone::Entity> src_entity = _entity.lock();

	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		std::shared_ptr<Player> tpl = iter->source()->template downcast<Player>();

		if (src_entity == nullptr || src_entity->guid() == tpl->guid())
			continue;

		bool is_in_range = tpl->is_in_range_of(src_entity);

		HLog(debug) << "Source entity " << src_entity->name() << " within range check: " << is_in_range;

		if (_notif_type <= EVP_NOTIFY_IN_SIGHT && is_in_range) {
			if (src_entity->is_walking()) {
				tpl->realize_entity_movement(src_entity);
			} else if (tpl->is_walking()) {
				tpl->add_entity_to_viewport(src_entity);
			} else {
				tpl->spawn_entity_in_viewport(src_entity);
			}
		} else if (_notif_type > EVP_NOTIFY_OUT_OF_SIGHT || (_notif_type == EVP_NOTIFY_OUT_OF_SIGHT && !is_in_range)) {
			if (src_entity->type() == ENTITY_PLAYER) {
				src_entity->template downcast<Player>()->remove_entity_from_viewport(tpl, _notif_type);
			}

			tpl->remove_entity_from_viewport(src_entity, _notif_type);
		}
	}
}

template <class T>
void GridEntitySearcher::search(GridRefManager<T> &m)
{
	// Found check.
	if (!_result.expired())
		return;

	using namespace Horizon::Zone;
	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		std::weak_ptr<Entity> entity = iter->source()->shared_from_this();
		if (!entity.expired() && _predicate(entity)) {
			_result = entity;
			return;
		}
	}
}


template <class T>
void GridNPCTrigger::check_and_trigger(GridRefManager<T> &m)
{
	if (_source.expired())
		return;

	using namespace Horizon::Zone::Entities;
	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		std::shared_ptr<NPC> npc = iter->source()->template downcast<NPC>();
		if (npc == nullptr)
			continue;

		npc_db_data const &nd = npc->get_db_data();
		if (nd.trigger_range && _predicate(npc, nd.trigger_range)) {
			std::shared_ptr<Player> player = _source.lock()->downcast<Player>();
			_source.lock()->script_manager()->contact_npc_for_player(player, npc->guid());
		}
	}
}

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERSIMPL_HPP */
