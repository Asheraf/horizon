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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKETHANDLER_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKETHANDLER_HPP

#include "Server/Common/PacketBuffer.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ACK_STORE_PASSWORD.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ADD_FRIENDS.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_CHANGE_DIRECTION.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_COMMAND_MER.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ENTER.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_GANGSI_RANK.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ITEMLISTWIN_RES.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ITEM_PICKUP.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_ITEM_THROW.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_JOIN_BATTLE_FIELD.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_MOVE_ITEM_FROM_BODY_TO_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_MOVE_ITEM_FROM_STORE_TO_BODY.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_PARTY_BOOKING_REQ_REGISTER.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_PARTY_JOIN_REQ.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_PRIVATE_AIRSHIP_REQUEST.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REFINE_ITEM_REQUEST.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQMAKINGITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQNAME.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQNAME_BYGID.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQUEST_ACT.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQUEST_MOVE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQUEST_TIME.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_APPLY_BARGAIN_SALE_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_CLICK_TO_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_CLOSE_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_COUNT_BARGAIN_SALE_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_ITEMREPAIR.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_MAKINGARROW.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_MAKINGITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_OPEN_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_REMOVE_BARGAIN_SALE_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_REQ_TRADE_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_SEARCH_STORE_INFO.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_SEARCH_STORE_INFO_NEXT_PAGE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_SIMPLE_BUY_CASH_POINT_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_SSILIST_ITEM_CLICK.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_USE_SKILL.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_USE_SKILL_TOGROUND.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_CZ_USE_SKILL_TOGROUND_WITHTALKBOX.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_ADD_ITEM_RODEX.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_COUNT_BARGAIN_SALE_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_GENERATE_ROULETTE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_OPEN_ROULETTE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_REQMAKINGITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_TOUSESKILL.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ACK_WEAPONREFINE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_EXCHANGE_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_EXCHANGE_ITEM2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_EXCHANGE_ITEM3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_EXCHANGE_ITEM4.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_ITEM_TO_CART.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_ITEM_TO_CART2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_ITEM_TO_CART3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_ITEM_TO_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_ITEM_TO_STORE2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ADD_ITEM_TO_STORE3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_CASH_ITEM_DELETE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_CASH_TIME_COUNTER.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_FEED_MER.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_FEED_PET.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_ENTRY.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_FALL_ENTRY.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_FALL_ENTRY4.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_ACK.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_ACK2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_ACK3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_ACK_V5.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_ACK_V6.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_ACK_V7.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PICKUP_PARTY.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_ITEM_PREVIEW.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_MVP_GETTING_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_BARGAIN_SALE_CLOSE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_BARGAIN_SALE_SELLING.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_MOVEENTRY2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_MOVEENTRY3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_MOVEENTRY4.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_NEWENTRY2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_NEWENTRY3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_NEWENTRY4.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_OFFLINE_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_STANDENTRY2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_STANDENTRY3.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_NOTIFY_STANDENTRY4.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_OFFLINE_STORE_VISIBLE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_PROPERTY_HOMUN.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_PROPERTY_HOMUN_2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_RECV_ROULETTE_ITEM.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_REFINE_STATUS.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_SPRITE_CHANGE2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_UPDATE_ITEM_FROM_BUYING_STORE.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_UPDATE_ITEM_FROM_BUYING_STORE2.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/Structs/PACKET_ZC_USE_ITEM_ACK2.hpp"
#include "Server/Zone/Packets/Ragexe/20181114/PacketHandlerRagexe20181114.hpp"

namespace Horizon
{
namespace Zone
{

class ZoneSocket;

class PacketHandlerRagexe20181121 : public PacketHandlerRagexe20181114
{
public:
	PacketHandlerRagexe20181121(std::shared_ptr<ZoneSocket> socket);
	~PacketHandlerRagexe20181121();

	virtual void initialize_handlers() override;

};
}
}

#endif /* HORIZON_ZONE_Ragexe_20181121_PACKETHANDLER_HPP */
