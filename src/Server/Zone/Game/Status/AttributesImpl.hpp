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

template <class T, class NOTIFIER_TYPE>
void Horizon::Zone::Game::Status::BasicAttributeNotifier::notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr)
{
	using namespace Horizon::Zone::Game::Entities;

	if (entity.expired())
		return;

	if (entity.lock()->get_type() == ENTITY_PLAYER)
		entity.lock()->downcast<Player>()->get_packet_handler()->Send_ZC_PAR_CHANGE(attr.get_type(), attr.total());
}

template <class T, class NOTIFIER_TYPE>
void Horizon::Zone::Game::Status::ExpAttributeNotifier::notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr)
{
	using namespace Horizon::Zone::Game::Entities;

	if (entity.expired())
		return;

	if (entity.lock()->get_type() == ENTITY_PLAYER)
		entity.lock()->downcast<Player>()->get_packet_handler()->Send_ZC_LONGPAR_CHANGE(attr.get_type(), attr.total());
}


template <class T, class NOTIFIER_TYPE>
void Horizon::Zone::Game::Status::StatusPointRequirementNotifier::notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr)
{
	using namespace Horizon::Zone::Game::Entities;

	if (entity.expired())
		return;

	if (entity.lock()->get_type() == ENTITY_PLAYER)
		entity.lock()->downcast<Player>()->get_packet_handler()->Send_ZC_STATUS_CHANGE(attr.get_type(), attr.total());
}

template <class T, class NOTIFIER_TYPE>
void Horizon::Zone::Game::Status::StatusPointNotifier::notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr)
{
	using namespace Horizon::Zone::Game::Entities;

	if (entity.expired())
		return;

	if (entity.lock()->get_type() == ENTITY_PLAYER)
		entity.lock()->downcast<Player>()->get_packet_handler()->Send_ZC_COUPLESTATUS(attr.get_type(), attr.get_base(), attr.get_equip() + attr.get_status());
}

template <class T, class NOTIFIER_TYPE>
void Horizon::Zone::Game::Status::AttackRangeNotifier::notify(std::weak_ptr<Entity> entity, Attribute<T, NOTIFIER_TYPE> const &attr)
{
	using namespace Horizon::Zone::Game::Entities;

	if (entity.expired())
		return;

	if (entity.lock()->get_type() == ENTITY_PLAYER)
		entity.lock()->downcast<Player>()->get_packet_handler()->Send_ZC_ATTACK_RANGE(attr.total());
}

#endif /* HORIZON_ZONE_GAME_STATUS_ATTRIBUTESIMPL_HPP */
