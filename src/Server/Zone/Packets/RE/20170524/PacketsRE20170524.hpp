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

#ifndef HORIZON_ZONE_RE_20170524_PACKETS_HPP
#define HORIZON_ZONE_RE_20170524_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170524
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0368,
	CZ_ADD_FRIENDS = 0x0967,
	CZ_CHANGE_DIRECTION = 0x0934,
	CZ_COMMAND_MER = 0x086d,
	CZ_ENTER = 0x0873,
	CZ_GANGSI_RANK = 0x0958,
	CZ_ITEMLISTWIN_RES = 0x0923,
	CZ_ITEM_PICKUP = 0x0864,
	CZ_ITEM_THROW = 0x0802,
	CZ_JOIN_BATTLE_FIELD = 0x091e,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0868,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0894,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x095b,
	CZ_PARTY_JOIN_REQ = 0x0364,
	CZ_REQNAME = 0x095a,
	CZ_REQNAME_BYGID = 0x0968,
	CZ_REQUEST_ACT = 0x085e,
	CZ_REQUEST_MOVE = 0x089c,
	CZ_REQUEST_TIME = 0x0860,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x085f,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0964,
	CZ_REQ_OPEN_BUYING_STORE = 0x087d,
	CZ_REQ_TRADE_BUYING_STORE = 0x0882,
	CZ_SEARCH_STORE_INFO = 0x0866,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0874,
	CZ_SSILIST_ITEM_CLICK = 0x08a1,
	CZ_USE_SKILL = 0x088d,
	CZ_USE_SKILL_TOGROUND = 0x0946,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0925,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170524_PACKETS_HPP */
