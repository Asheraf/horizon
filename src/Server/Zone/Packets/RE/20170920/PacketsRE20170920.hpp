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

#ifndef HORIZON_ZONE_RE_20170920_PACKETS_HPP
#define HORIZON_ZONE_RE_20170920_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170920
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0864,
	CZ_ADD_FRIENDS = 0x0861,
	CZ_CHANGE_DIRECTION = 0x0939,
	CZ_COMMAND_MER = 0x095d,
	CZ_ENTER = 0x0923,
	CZ_GANGSI_RANK = 0x0875,
	CZ_ITEMLISTWIN_RES = 0x0436,
	CZ_ITEM_PICKUP = 0x0369,
	CZ_ITEM_THROW = 0x086c,
	CZ_JOIN_BATTLE_FIELD = 0x091e,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0926,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x07ec,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0945,
	CZ_PARTY_JOIN_REQ = 0x086a,
	CZ_REQNAME = 0x0889,
	CZ_REQNAME_BYGID = 0x0921,
	CZ_REQUEST_ACT = 0x089b,
	CZ_REQUEST_MOVE = 0x085a,
	CZ_REQUEST_TIME = 0x088e,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0961,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0874,
	CZ_REQ_OPEN_BUYING_STORE = 0x0865,
	CZ_REQ_TRADE_BUYING_STORE = 0x092e,
	CZ_SEARCH_STORE_INFO = 0x094c,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x096a,
	CZ_SSILIST_ITEM_CLICK = 0x0937,
	CZ_USE_SKILL = 0x0862,
	CZ_USE_SKILL_TOGROUND = 0x0919,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0966,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170920_PACKETS_HPP */
