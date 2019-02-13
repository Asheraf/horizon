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

#ifndef HORIZON_ZONE_RE_20170927_PACKETS_HPP
#define HORIZON_ZONE_RE_20170927_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170927
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x089a,
	CZ_ADD_FRIENDS = 0x094b,
	CZ_CHANGE_DIRECTION = 0x087e,
	CZ_COMMAND_MER = 0x02c4,
	CZ_ENTER = 0x0366,
	CZ_GANGSI_RANK = 0x0361,
	CZ_ITEMLISTWIN_RES = 0x08a5,
	CZ_ITEM_PICKUP = 0x094d,
	CZ_ITEM_THROW = 0x0923,
	CZ_JOIN_BATTLE_FIELD = 0x08a6,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0959,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x089b,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0942,
	CZ_PARTY_JOIN_REQ = 0x0922,
	CZ_REQNAME = 0x035f,
	CZ_REQNAME_BYGID = 0x0873,
	CZ_REQUEST_ACT = 0x0899,
	CZ_REQUEST_MOVE = 0x0927,
	CZ_REQUEST_TIME = 0x0945,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x091e,
	CZ_REQ_CLOSE_BUYING_STORE = 0x08a3,
	CZ_REQ_OPEN_BUYING_STORE = 0x0362,
	CZ_REQ_TRADE_BUYING_STORE = 0x087d,
	CZ_SEARCH_STORE_INFO = 0x08ad,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x088b,
	CZ_SSILIST_ITEM_CLICK = 0x0875,
	CZ_USE_SKILL = 0x085c,
	CZ_USE_SKILL_TOGROUND = 0x095a,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x093b,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170927_PACKETS_HPP */
