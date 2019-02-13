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

#ifndef HORIZON_ZONE_RE_20171101_PACKETS_HPP
#define HORIZON_ZONE_RE_20171101_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20171101
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x022d,
	CZ_ADD_FRIENDS = 0x0872,
	CZ_CHANGE_DIRECTION = 0x0876,
	CZ_COMMAND_MER = 0x085b,
	CZ_ENTER = 0x0368,
	CZ_GANGSI_RANK = 0x0895,
	CZ_ITEMLISTWIN_RES = 0x08ab,
	CZ_ITEM_PICKUP = 0x0962,
	CZ_ITEM_THROW = 0x0835,
	CZ_JOIN_BATTLE_FIELD = 0x0886,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x091b,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x08a0,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x089c,
	CZ_PARTY_JOIN_REQ = 0x0899,
	CZ_REQNAME = 0x0860,
	CZ_REQNAME_BYGID = 0x094d,
	CZ_REQUEST_ACT = 0x0957,
	CZ_REQUEST_MOVE = 0x0939,
	CZ_REQUEST_TIME = 0x0438,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x088e,
	CZ_REQ_CLOSE_BUYING_STORE = 0x094a,
	CZ_REQ_OPEN_BUYING_STORE = 0x089b,
	CZ_REQ_TRADE_BUYING_STORE = 0x095a,
	CZ_SEARCH_STORE_INFO = 0x0369,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0890,
	CZ_SSILIST_ITEM_CLICK = 0x08ad,
	CZ_USE_SKILL = 0x086c,
	CZ_USE_SKILL_TOGROUND = 0x0966,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0952,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20171101_PACKETS_HPP */
