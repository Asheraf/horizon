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

#ifndef HORIZON_ZONE_RE_20180103_PACKETS_HPP
#define HORIZON_ZONE_RE_20180103_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20180103
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0946,
	CZ_ADD_FRIENDS = 0x0899,
	CZ_CHANGE_DIRECTION = 0x08a9,
	CZ_COMMAND_MER = 0x0948,
	CZ_ENTER = 0x0811,
	CZ_GANGSI_RANK = 0x0865,
	CZ_ITEMLISTWIN_RES = 0x08ac,
	CZ_ITEM_PICKUP = 0x0935,
	CZ_ITEM_THROW = 0x095f,
	CZ_JOIN_BATTLE_FIELD = 0x0926,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x02c4,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x092c,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0927,
	CZ_PARTY_JOIN_REQ = 0x0363,
	CZ_REQNAME = 0x08ab,
	CZ_REQNAME_BYGID = 0x089f,
	CZ_REQUEST_ACT = 0x091d,
	CZ_REQUEST_MOVE = 0x0941,
	CZ_REQUEST_TIME = 0x0876,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0872,
	CZ_REQ_CLOSE_BUYING_STORE = 0x088e,
	CZ_REQ_OPEN_BUYING_STORE = 0x094e,
	CZ_REQ_TRADE_BUYING_STORE = 0x0879,
	CZ_SEARCH_STORE_INFO = 0x086b,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0922,
	CZ_SSILIST_ITEM_CLICK = 0x086d,
	CZ_USE_SKILL = 0x0938,
	CZ_USE_SKILL_TOGROUND = 0x095d,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0960,
	ZC_ITEM_FALL_ENTRY = 0x009e,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20180103_PACKETS_HPP */
