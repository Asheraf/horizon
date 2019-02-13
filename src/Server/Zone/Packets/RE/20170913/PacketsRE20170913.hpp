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

#ifndef HORIZON_ZONE_RE_20170913_PACKETS_HPP
#define HORIZON_ZONE_RE_20170913_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170913
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0892,
	CZ_ADD_FRIENDS = 0x035f,
	CZ_CHANGE_DIRECTION = 0x08ac,
	CZ_COMMAND_MER = 0x088c,
	CZ_ENTER = 0x0835,
	CZ_GANGSI_RANK = 0x08a7,
	CZ_ITEMLISTWIN_RES = 0x08ad,
	CZ_ITEM_PICKUP = 0x0860,
	CZ_ITEM_THROW = 0x091d,
	CZ_JOIN_BATTLE_FIELD = 0x091e,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0891,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x07e4,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x08ab,
	CZ_PARTY_JOIN_REQ = 0x0865,
	CZ_REQNAME = 0x0281,
	CZ_REQNAME_BYGID = 0x095c,
	CZ_REQUEST_ACT = 0x0817,
	CZ_REQUEST_MOVE = 0x0923,
	CZ_REQUEST_TIME = 0x091b,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x08a6,
	CZ_REQ_CLOSE_BUYING_STORE = 0x085a,
	CZ_REQ_OPEN_BUYING_STORE = 0x0866,
	CZ_REQ_TRADE_BUYING_STORE = 0x0927,
	CZ_SEARCH_STORE_INFO = 0x0437,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0920,
	CZ_SSILIST_ITEM_CLICK = 0x0925,
	CZ_USE_SKILL = 0x08aa,
	CZ_USE_SKILL_TOGROUND = 0x095a,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0890,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170913_PACKETS_HPP */
