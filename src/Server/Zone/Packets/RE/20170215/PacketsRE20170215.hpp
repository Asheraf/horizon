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

#ifndef HORIZON_ZONE_RE_20170215_PACKETS_HPP
#define HORIZON_ZONE_RE_20170215_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170215
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x02c4,
	CZ_ADD_FRIENDS = 0x0876,
	CZ_CHANGE_DIRECTION = 0x087d,
	CZ_COMMAND_MER = 0x0962,
	CZ_ENTER = 0x0811,
	CZ_GANGSI_RANK = 0x0896,
	CZ_ITEMLISTWIN_RES = 0x087c,
	CZ_ITEM_PICKUP = 0x0942,
	CZ_ITEM_THROW = 0x085c,
	CZ_JOIN_BATTLE_FIELD = 0x0884,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x089b,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0925,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x08a8,
	CZ_PARTY_JOIN_REQ = 0x088b,
	CZ_REQNAME = 0x094e,
	CZ_REQNAME_BYGID = 0x0883,
	CZ_REQUEST_ACT = 0x083c,
	CZ_REQUEST_MOVE = 0x0969,
	CZ_REQUEST_TIME = 0x0360,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x095f,
	CZ_REQ_CLOSE_BUYING_STORE = 0x091c,
	CZ_REQ_OPEN_BUYING_STORE = 0x088c,
	CZ_REQ_TRADE_BUYING_STORE = 0x035f,
	CZ_SEARCH_STORE_INFO = 0x092b,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x092d,
	CZ_SSILIST_ITEM_CLICK = 0x08a2,
	CZ_USE_SKILL = 0x087e,
	CZ_USE_SKILL_TOGROUND = 0x0890,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x088a,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170215_PACKETS_HPP */
