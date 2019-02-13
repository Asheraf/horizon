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

#ifndef HORIZON_ZONE_RE_20170614_PACKETS_HPP
#define HORIZON_ZONE_RE_20170614_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170614
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0437,
	CZ_ADD_FRIENDS = 0x0867,
	CZ_CHANGE_DIRECTION = 0x087e,
	CZ_COMMAND_MER = 0x0364,
	CZ_ENTER = 0x0944,
	CZ_GANGSI_RANK = 0x0865,
	CZ_ITEMLISTWIN_RES = 0x089d,
	CZ_ITEM_PICKUP = 0x08ad,
	CZ_ITEM_THROW = 0x0367,
	CZ_JOIN_BATTLE_FIELD = 0x0957,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0879,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x023b,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0877,
	CZ_PARTY_JOIN_REQ = 0x0899,
	CZ_REQNAME = 0x0936,
	CZ_REQNAME_BYGID = 0x087d,
	CZ_REQUEST_ACT = 0x083c,
	CZ_REQUEST_MOVE = 0x0361,
	CZ_REQUEST_TIME = 0x0866,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0860,
	CZ_REQ_CLOSE_BUYING_STORE = 0x086b,
	CZ_REQ_OPEN_BUYING_STORE = 0x08a2,
	CZ_REQ_TRADE_BUYING_STORE = 0x092f,
	CZ_SEARCH_STORE_INFO = 0x086c,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0928,
	CZ_SSILIST_ITEM_CLICK = 0x0963,
	CZ_USE_SKILL = 0x091b,
	CZ_USE_SKILL_TOGROUND = 0x0838,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0889,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170614_PACKETS_HPP */
