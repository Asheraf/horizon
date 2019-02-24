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

#include <boost/smart_ptr.hpp>

template <class T>
void GridViewPortUpdater::update(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Game::Entities;
	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		boost::shared_ptr<Player> pl = boost::dynamic_pointer_cast<Player>(_entity.lock());

		if (iter->source()->get_guid() == pl->get_guid())
			continue;

		pl->add_entity_to_viewport(iter->source()->weak_from_this());
	}
}


template <class T>
void GridEntityExistenceNotifier::notify(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Game::Entities;

	boost::shared_ptr<Horizon::Zone::Game::Entity> src_entity = _entity.lock();

	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		boost::shared_ptr<Player> tpl = boost::dynamic_pointer_cast<Player>(iter->source()->shared_from_this());

		if (src_entity == nullptr || src_entity->get_guid() == tpl->get_guid())
			continue;

		bool is_in_range = tpl->is_in_range_of(src_entity);

		if (_notif_type <= EVP_NOTIFY_IN_SIGHT && is_in_range) {
			boost::shared_ptr<Unit> unit = boost::dynamic_pointer_cast<Unit>(src_entity);
			if (unit->is_walking()) {
				tpl->realize_entity_movement(src_entity);
			} else {
				tpl->add_entity_to_viewport(src_entity);
			}
		} else if (_notif_type > EVP_NOTIFY_OUT_OF_SIGHT || (_notif_type == EVP_NOTIFY_OUT_OF_SIGHT && !is_in_range)) {
			if (src_entity->get_type() == ENTITY_PLAYER) {
				boost::shared_ptr<Player> pl = boost::dynamic_pointer_cast<Player>(src_entity);
				pl->remove_entity_from_viewport(tpl, _notif_type);
			}

			tpl->remove_entity_from_viewport(src_entity, _notif_type);
		}
	}
}

template <class T>
void GridEntitySearcher::search(GridRefManager<T> &m)
{
	if (!_result.expired())
		return;

	using namespace Horizon::Zone::Game;
	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		boost::weak_ptr<Entity> entity = iter->source()->weak_from_this();
		if (!entity.expired() && _predicate(entity)) {
			_result = entity;
			return;
		}
	}
}

template <typename ZC_PACKET_T> template <typename T>
void GridPlayerNotifier<ZC_PACKET_T>::notify(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Game::Entities;

	boost::shared_ptr<Player> pl = boost::dynamic_pointer_cast<Player>(_player.lock());

	if (pl == nullptr)
		return;

	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		switch (_type)
		{
			case GRID_NOTIFY_AREA_WOS:
				if (iter->source()->get_guid() == pl->get_guid())
					continue;
			default:
				break;
		}
		iter->source()->get_packet_handler()->send_packet(_pkt);
	}
}

#endif /* HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERSIMPL_HPP */
