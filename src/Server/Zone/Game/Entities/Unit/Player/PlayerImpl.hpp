//
//  PlayerImpl.hpp
//  zone
//
//  Created by SagunKho on 05/02/2019.
//

#ifndef HORIZON_ZONE_GAME_ENTITIES_PLAYERIMPL_HPP
#define HORIZON_ZONE_GAME_ENTITIES_PLAYERIMPL_HPP

#include "Server/Zone/Game/Map/Grid/Notifiers/GridNotifiers.hpp"
#include "Server/Zone/Game/Map/Grid/Container/GridReferenceContainer.hpp"

template <typename ZC_PACKET_T>
struct GridPlayerNotifier;

template<typename ZC_PACKET_T>
void Horizon::Zone::Game::Entities::Player::notify_in_area(ZC_PACKET_T &pkt, player_notifier_types type, uint16_t range)
{
	GridPlayerNotifier<ZC_PACKET_T> notifier(pkt, static_cast<Entity *>(this)->weak_from_this(), type);
	GridReferenceContainerVisitor<GridPlayerNotifier<ZC_PACKET_T>, GridReferenceContainer<AllEntityTypes>> container(notifier);

	get_map()->visit_in_range(get_map_coords(), range, container);
}

#endif /* HORIZON_ZONE_GAME_ENTITIES_PLAYERIMPL_HPP */
