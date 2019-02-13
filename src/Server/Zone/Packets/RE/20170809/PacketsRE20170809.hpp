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

#ifndef HORIZON_ZONE_RE_20170809_PACKETS_HPP
#define HORIZON_ZONE_RE_20170809_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170809
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0890,
	CZ_ADD_FRIENDS = 0x0366,
	CZ_CHANGE_DIRECTION = 0x086e,
	CZ_COMMAND_MER = 0x086f,
	CZ_ENTER = 0x08a6,
	CZ_GANGSI_RANK = 0x022d,
	CZ_ITEMLISTWIN_RES = 0x0802,
	CZ_ITEM_PICKUP = 0x0918,
	CZ_ITEM_THROW = 0x0835,
	CZ_JOIN_BATTLE_FIELD = 0x0899,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0921,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0281,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0940,
	CZ_PARTY_JOIN_REQ = 0x0364,
	CZ_REQNAME = 0x092a,
	CZ_REQNAME_BYGID = 0x0931,
	CZ_REQUEST_ACT = 0x0868,
	CZ_REQUEST_MOVE = 0x0895,
	CZ_REQUEST_TIME = 0x092b,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0939,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0367,
	CZ_REQ_OPEN_BUYING_STORE = 0x093b,
	CZ_REQ_TRADE_BUYING_STORE = 0x08a3,
	CZ_SEARCH_STORE_INFO = 0x0880,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x07e4,
	CZ_SSILIST_ITEM_CLICK = 0x087d,
	CZ_USE_SKILL = 0x088c,
	CZ_USE_SKILL_TOGROUND = 0x0876,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0892,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170809_PACKETS_HPP */
