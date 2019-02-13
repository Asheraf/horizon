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

#ifndef HORIZON_ZONE_RE_20170315_PACKETS_HPP
#define HORIZON_ZONE_RE_20170315_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170315
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0952,
	CZ_ADD_FRIENDS = 0x0872,
	CZ_CHANGE_DIRECTION = 0x0360,
	CZ_COMMAND_MER = 0x0863,
	CZ_ENTER = 0x094e,
	CZ_GANGSI_RANK = 0x085c,
	CZ_ITEMLISTWIN_RES = 0x0922,
	CZ_ITEM_PICKUP = 0x0366,
	CZ_ITEM_THROW = 0x091a,
	CZ_JOIN_BATTLE_FIELD = 0x088d,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x08aa,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x086a,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x088b,
	CZ_PARTY_JOIN_REQ = 0x087b,
	CZ_REQNAME = 0x0944,
	CZ_REQNAME_BYGID = 0x0920,
	CZ_REQUEST_ACT = 0x0884,
	CZ_REQUEST_MOVE = 0x088f,
	CZ_REQUEST_TIME = 0x07ec,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x094a,
	CZ_REQ_CLOSE_BUYING_STORE = 0x089c,
	CZ_REQ_OPEN_BUYING_STORE = 0x091b,
	CZ_REQ_TRADE_BUYING_STORE = 0x0436,
	CZ_SEARCH_STORE_INFO = 0x035f,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0950,
	CZ_SSILIST_ITEM_CLICK = 0x091d,
	CZ_USE_SKILL = 0x0892,
	CZ_USE_SKILL_TOGROUND = 0x02c4,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0367,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170315_PACKETS_HPP */
