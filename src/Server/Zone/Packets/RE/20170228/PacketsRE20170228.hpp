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

#ifndef HORIZON_ZONE_RE_20170228_PACKETS_HPP
#define HORIZON_ZONE_RE_20170228_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170228
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x08a2,
	CZ_ADD_FRIENDS = 0x08a0,
	CZ_CHANGE_DIRECTION = 0x0889,
	CZ_COMMAND_MER = 0x0362,
	CZ_ENTER = 0x086b,
	CZ_GANGSI_RANK = 0x093e,
	CZ_ITEMLISTWIN_RES = 0x0873,
	CZ_ITEM_PICKUP = 0x092a,
	CZ_ITEM_THROW = 0x022d,
	CZ_JOIN_BATTLE_FIELD = 0x08a6,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x089e,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0944,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0955,
	CZ_PARTY_JOIN_REQ = 0x0948,
	CZ_REQNAME = 0x0893,
	CZ_REQNAME_BYGID = 0x0947,
	CZ_REQUEST_ACT = 0x0360,
	CZ_REQUEST_MOVE = 0x0884,
	CZ_REQUEST_TIME = 0x0937,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x08a7,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0876,
	CZ_REQ_OPEN_BUYING_STORE = 0x0874,
	CZ_REQ_TRADE_BUYING_STORE = 0x092e,
	CZ_SEARCH_STORE_INFO = 0x0863,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0883,
	CZ_SSILIST_ITEM_CLICK = 0x0819,
	CZ_USE_SKILL = 0x091f,
	CZ_USE_SKILL_TOGROUND = 0x0952,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x085e,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170228_PACKETS_HPP */
