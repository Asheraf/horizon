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

#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYERIMPL_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYERIMPL_HPP

#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"

template <typename ZC_PACKET_T>
struct GridPlayerNotifier;

template<typename ZC_PACKET_T>
void Horizon::Zone::Entities::Player::notify_in_area(ZC_PACKET_T &pkt, player_notifier_type type, uint16_t range)
{
	GridPlayerNotifier<ZC_PACKET_T> notifier(pkt, static_cast<Entity *>(this)->shared_from_this(), type);
	GridReferenceContainerVisitor<GridPlayerNotifier<ZC_PACKET_T>, GridReferenceContainer<AllEntityTypes>> container(notifier);

	map()->visit_in_range(map_coords(), container, range);
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYERIMPL_HPP */
