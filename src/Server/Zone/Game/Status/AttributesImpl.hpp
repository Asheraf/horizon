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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_GAME_STATUS_ATTRIBUTESIMPL_HPP
#define HORIZON_ZONE_GAME_STATUS_ATTRIBUTESIMPL_HPP

#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"

template <status_point_type NOTIFIABLE_TYPE, class ... NOTIFIABLES>
template <std::size_t I, typename... Tp>
inline typename std::enable_if<(I < sizeof...(Tp)), void>::type
Horizon::Zone::Game::Status::BasicAttributeNotifier<NOTIFIABLE_TYPE, NOTIFIABLES ...>::notify(std::tuple<Tp...> &t)
{
	using namespace Horizon::Zone::Game::Entities;
	std::shared_ptr<Entity> entity = get_entity();

	if (!entity || entity->get_type() != ENTITY_PLAYER)
		return;

	entity->downcast<Player>()->get_packet_handler()->Send_ZC_PAR_CHANGE(NOTIFIABLE_TYPE, std::get<I>(t).lock()->total());
}

template <status_point_type NOTIFIABLE_TYPE, class ... NOTIFIABLES>
void Horizon::Zone::Game::Status::BasicAttributeNotifier<NOTIFIABLE_TYPE, NOTIFIABLES ...>::notify_sum()
{
	using namespace Horizon::Zone::Game::Entities;
	std::shared_ptr<Entity> entity = get_entity();

	if (!entity || entity->get_type() != ENTITY_PLAYER)
		return;

	entity->downcast<Player>()->get_packet_handler()->Send_ZC_PAR_CHANGE(NOTIFIABLE_TYPE, get_sum(_notifiables));
}

template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
void Horizon::Zone::Game::Status::ExperienceNotifier<NOTIFIABLE_TYPE, NOTIFIABLE>::notify()
{
	using namespace Horizon::Zone::Game::Entities;
	std::shared_ptr<typename NOTIFIABLE::element_type> notifiable = _notifiable.lock();
	std::shared_ptr<Entity> entity = get_entity();

	if (!entity || entity->get_type() != ENTITY_PLAYER || !notifiable)
		return;

	entity->downcast<Player>()->get_packet_handler()->Send_ZC_LONGPAR_CHANGE(NOTIFIABLE_TYPE, notifiable->get_base());
}


template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
void Horizon::Zone::Game::Status::StatusPointRequirementNotifier<NOTIFIABLE_TYPE, NOTIFIABLE>::notify()
{
	using namespace Horizon::Zone::Game::Entities;
	std::shared_ptr<typename NOTIFIABLE::element_type> notifiable = _notifiable.lock();
	std::shared_ptr<Entity> entity = get_entity();

	if (!entity || entity->get_type() != ENTITY_PLAYER || !notifiable)
		return;

	entity->downcast<Player>()->get_packet_handler()->Send_ZC_STATUS_CHANGE(NOTIFIABLE_TYPE, notifiable->get_base());
}

template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
void Horizon::Zone::Game::Status::StatusPointNotifier<NOTIFIABLE_TYPE, NOTIFIABLE>::notify()
{
	using namespace Horizon::Zone::Game::Entities;
	std::shared_ptr<typename NOTIFIABLE::element_type> notifiable = _notifiable.lock();
	std::shared_ptr<Entity> entity = get_entity();

	if (!entity || entity->get_type() != ENTITY_PLAYER || !notifiable)
		return;

	entity->downcast<Player>()->get_packet_handler()->Send_ZC_COUPLESTATUS(NOTIFIABLE_TYPE, notifiable->get_base(), notifiable->get_equip() + notifiable->get_status());
}

template <status_point_type NOTIFIABLE_TYPE, class NOTIFIABLE>
void Horizon::Zone::Game::Status::AttackRangeNotifier<NOTIFIABLE_TYPE, NOTIFIABLE>::notify()
{
	using namespace Horizon::Zone::Game::Entities;
	std::shared_ptr<typename NOTIFIABLE::element_type> notifiable = _notifiable.lock();
	std::shared_ptr<Entity> entity = get_entity();

	if (!entity || entity->get_type() != ENTITY_PLAYER || !notifiable)
		return;

	entity->downcast<Player>()->get_packet_handler()->Send_ZC_ATTACK_RANGE(notifiable->total());
}

#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTESIMPL_HPP */
