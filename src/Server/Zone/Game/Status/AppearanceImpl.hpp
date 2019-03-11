/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
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

#ifndef HORIZON_ZONE_GAME_STATUS_APPEARANCEIMPL_HPP
#define HORIZON_ZONE_GAME_STATUS_APPEARANCEIMPL_HPP

#include "Appearance.hpp"
#include "Server/Zone/Packets/PacketHandler.hpp"
#include "Server/Common/Definitions/EntityDefinitions.hpp"
#include "Server/Zone/Game/Entities/Entity.hpp"
#include "Server/Zone/Game/Entities/Player/Player.hpp"

template <typename T>
void Horizon::Zone::Game::Status::Appearance<T>::notify_update()
{
	using namespace Horizon::Zone::Game::Entities;

//	if (get_entity() != nullptr && get_entity()->get_type() == ENTITY_PLAYER)
//		get_entity()->template downcast<Player>()->get_packet_handler()->Send_ZC_PAR_CHANGE(_type, total());
}

#endif /* HORIZON_ZONE_GAME_STATUS_APPEARANCEIMPL_HPP */
