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

#ifndef HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERSIMPL_HPP
#define HORIZON_ZONE_GAME_MAP_GRIDNOTIFIERSIMPL_HPP

template <class T>
void GridViewPortUpdater::update(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Game::Entities;
	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		std::shared_ptr<Player> pl = std::dynamic_pointer_cast<Player>(_entity.lock());

		if (iter->source()->get_guid() == pl->get_guid())
			continue;

		pl->add_entity_to_viewport(iter->source()->weak_from_this());
	}
}


template <class T>
void GridMovementNotifier::notify(GridRefManager<T> &m)
{
	using namespace Horizon::Zone::Game::Entities;
	for (typename GridRefManager<T>::iterator iter = m.begin(); iter != typename GridRefManager<T>::iterator(nullptr); ++iter) {
		std::shared_ptr<Player> pl = std::dynamic_pointer_cast<Player>(iter->source()->shared_from_this());
		std::shared_ptr<Player> tpl = std::dynamic_pointer_cast<Player>(_entity.lock());

		if (tpl->get_guid() == pl->get_guid())
			continue;

		if (tpl->is_walking()) {
			pl->realize_entity_movement(_entity);
		} else {
			pl->add_entity_to_viewport(_entity);
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
		std::weak_ptr<Entity> entity = iter->source()->weak_from_this();
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

	std::shared_ptr<Player> pl = std::dynamic_pointer_cast<Player>(_player.lock());

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
