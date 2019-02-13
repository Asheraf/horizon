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

#ifndef HORIZON_ZONE_RE_20180213_PACKETS_HPP
#define HORIZON_ZONE_RE_20180213_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20180213
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0369,
	CZ_ADD_FRIENDS = 0x0917,
	CZ_CHANGE_DIRECTION = 0x0878,
	CZ_COMMAND_MER = 0x0962,
	CZ_ENTER = 0x08a3,
	CZ_GANGSI_RANK = 0x089c,
	CZ_ITEMLISTWIN_RES = 0x095a,
	CZ_ITEM_PICKUP = 0x0892,
	CZ_ITEM_THROW = 0x0802,
	CZ_JOIN_BATTLE_FIELD = 0x0926,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0955,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0875,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0943,
	CZ_PARTY_JOIN_REQ = 0x086f,
	CZ_REQNAME = 0x093c,
	CZ_REQNAME_BYGID = 0x08ad,
	CZ_REQUEST_ACT = 0x0933,
	CZ_REQUEST_MOVE = 0x0922,
	CZ_REQUEST_TIME = 0x0874,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x087b,
	CZ_REQ_CLOSE_BUYING_STORE = 0x08a9,
	CZ_REQ_OPEN_BUYING_STORE = 0x08a5,
	CZ_REQ_TRADE_BUYING_STORE = 0x0898,
	CZ_SEARCH_STORE_INFO = 0x088c,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0936,
	CZ_SSILIST_ITEM_CLICK = 0x085a,
	CZ_USE_SKILL = 0x0882,
	CZ_USE_SKILL_TOGROUND = 0x0924,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0817,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20180213_PACKETS_HPP */
