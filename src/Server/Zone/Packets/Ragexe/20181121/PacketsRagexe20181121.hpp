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

#ifndef HORIZON_ZONE_RAGEXE_20181121_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20181121_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20181121
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x023b,
	CZ_ADD_FRIENDS = 0x0202,
	CZ_CHANGE_DIRECTION = 0x0361,
	CZ_COMMAND_MER = 0x022d,
	CZ_ENTER = 0x0436,
	CZ_GANGSI_RANK = 0x0281,
	CZ_ITEMLISTWIN_RES = 0x07e4,
	CZ_ITEM_PICKUP = 0x0362,
	CZ_ITEM_THROW = 0x0363,
	CZ_JOIN_BATTLE_FIELD = 0x07ec,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0364,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0365,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0802,
	CZ_PARTY_JOIN_REQ = 0x02c4,
	CZ_PRIVATE_AIRSHIP_REQUEST = 0x0a49,
	CZ_REFINE_ITEM_REQUEST = 0x0aa3,
	CZ_REQMAKINGITEM = 0x018e,
	CZ_REQNAME = 0x0368,
	CZ_REQNAME_BYGID = 0x0369,
	CZ_REQUEST_ACT = 0x0437,
	CZ_REQUEST_MOVE = 0x035f,
	CZ_REQUEST_TIME = 0x0360,
	CZ_REQ_APPLY_BARGAIN_SALE_ITEM = 0x09ae,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0817,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0815,
	CZ_REQ_COUNT_BARGAIN_SALE_ITEM = 0x09c3,
	CZ_REQ_ITEMREPAIR = 0x01fd,
	CZ_REQ_MAKINGARROW = 0x01ae,
	CZ_REQ_MAKINGITEM = 0x025b,
	CZ_REQ_OPEN_BUYING_STORE = 0x0811,
	CZ_REQ_REMOVE_BARGAIN_SALE_ITEM = 0x09b0,
	CZ_REQ_TRADE_BUYING_STORE = 0x0819,
	CZ_SEARCH_STORE_INFO = 0x0835,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0838,
	CZ_SIMPLE_BUY_CASH_POINT_ITEM = 0x0445,
	CZ_SSILIST_ITEM_CLICK = 0x083c,
	CZ_USE_SKILL = 0x0438,
	CZ_USE_SKILL_TOGROUND = 0x0366,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0367,
	ZC_ACK_ADD_ITEM_RODEX = 0x0a05,
	ZC_ACK_CASH_BARGAIN_SALE_ITEM_INFO = 0x09ad,
	ZC_ACK_COUNT_BARGAIN_SALE_ITEM = 0x09c4,
	ZC_ACK_GENERATE_ROULETTE = 0x0a20,
	ZC_ACK_OPEN_ROULETTE = 0x0a1a,
	ZC_ACK_REQMAKINGITEM = 0x018f,
	ZC_ACK_TOUSESKILL = 0x0110,
	ZC_ACK_WEAPONREFINE = 0x0223,
	ZC_ADD_EXCHANGE_ITEM = 0x00e9,
	ZC_ADD_EXCHANGE_ITEM2 = 0x080f,
	ZC_ADD_EXCHANGE_ITEM3 = 0x0a09,
	ZC_ADD_EXCHANGE_ITEM4 = 0x0a96,
	ZC_ADD_ITEM_TO_CART = 0x0124,
	ZC_ADD_ITEM_TO_CART2 = 0x01c5,
	ZC_ADD_ITEM_TO_CART3 = 0x0a0b,
	ZC_ADD_ITEM_TO_STORE = 0x00f4,
	ZC_ADD_ITEM_TO_STORE2 = 0x01c4,
	ZC_ADD_ITEM_TO_STORE3 = 0x0a0a,
	ZC_CASH_ITEM_DELETE = 0x0299,
	ZC_CASH_TIME_COUNTER = 0x0298,
	ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER = 0x0824,
	ZC_FEED_MER = 0x022f,
	ZC_FEED_PET = 0x01a3,
	ZC_ITEM_ENTRY = 0x009d,
	ZC_ITEM_FALL_ENTRY = 0x0add,
	ZC_ITEM_FALL_ENTRY4 = 0x084b,
	ZC_ITEM_PICKUP_ACK = 0x00a0,
	ZC_ITEM_PICKUP_ACK2 = 0x029a,
	ZC_ITEM_PICKUP_ACK3 = 0x02d4,
	ZC_ITEM_PICKUP_ACK_V5 = 0x0990,
	ZC_ITEM_PICKUP_ACK_V6 = 0x0a0c,
	ZC_ITEM_PICKUP_ACK_V7 = 0x0a37,
	ZC_ITEM_PICKUP_PARTY = 0x02b8,
	ZC_ITEM_PREVIEW = 0x0b13,
	ZC_MVP_GETTING_ITEM = 0x010a,
	ZC_NOTIFY_BARGAIN_SALE_CLOSE = 0x09b3,
	ZC_NOTIFY_BARGAIN_SALE_SELLING = 0x09b2,
	ZC_NOTIFY_MOVEENTRY2 = 0x01da,
	ZC_NOTIFY_MOVEENTRY3 = 0x022c,
	ZC_NOTIFY_MOVEENTRY4 = 0x02ec,
	ZC_NOTIFY_NEWENTRY2 = 0x01d9,
	ZC_NOTIFY_NEWENTRY3 = 0x022b,
	ZC_NOTIFY_NEWENTRY4 = 0x02ed,
	ZC_NOTIFY_OFFLINE_STORE = 0x0a89,
	ZC_NOTIFY_STANDENTRY2 = 0x01d8,
	ZC_NOTIFY_STANDENTRY3 = 0x022a,
	ZC_NOTIFY_STANDENTRY4 = 0x02ee,
	ZC_OFFLINE_STORE_VISIBLE = 0x0b05,
	ZC_PROPERTY_HOMUN = 0x022e,
	ZC_PROPERTY_HOMUN_2 = 0x09f7,
	ZC_RECV_ROULETTE_ITEM = 0x0a22,
	ZC_REFINE_STATUS = 0x0ada,
	ZC_SPRITE_CHANGE2 = 0x01d7,
	ZC_UPDATE_ITEM_FROM_BUYING_STORE = 0x081b,
	ZC_UPDATE_ITEM_FROM_BUYING_STORE2 = 0x09e6,
	ZC_USE_ITEM_ACK2 = 0x01c8,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20181121_PACKETS_HPP */
