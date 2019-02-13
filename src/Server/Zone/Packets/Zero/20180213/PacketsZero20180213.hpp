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

#ifndef HORIZON_ZONE_ZERO_20180213_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20180213_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20180213
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x023b,
	CZ_ADD_FRIENDS = 0x0202,
	CZ_CHANGE_DIRECTION = 0x022d,
	CZ_COMMAND_MER = 0x085d,
	CZ_ENTER = 0x0941,
	CZ_ENTER2 = 0x0436,
	CZ_GANGSI_RANK = 0x088a,
	CZ_ITEMLISTWIN_RES = 0x0887,
	CZ_ITEM_PICKUP = 0x0947,
	CZ_ITEM_THROW = 0x035f,
	CZ_JOIN_BATTLE_FIELD = 0x0930,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x02c4,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0942,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0868,
	CZ_PARTY_JOIN_REQ = 0x0958,
	CZ_REQNAME = 0x087b,
	CZ_REQNAME_BYGID = 0x0888,
	CZ_REQUEST_ACT = 0x0917,
	CZ_REQUEST_MOVE = 0x091d,
	CZ_REQUEST_TIME = 0x0802,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x088e,
	CZ_REQ_CLOSE_BUYING_STORE = 0x095b,
	CZ_REQ_OPEN_BUYING_STORE = 0x0922,
	CZ_REQ_TRADE_BUYING_STORE = 0x095c,
	CZ_SEARCH_STORE_INFO = 0x085a,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0838,
	CZ_SSILIST_ITEM_CLICK = 0x0882,
	CZ_USE_SKILL = 0x0815,
	CZ_USE_SKILL_TOGROUND = 0x094d,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0361,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20180213_PACKETS_HPP */
