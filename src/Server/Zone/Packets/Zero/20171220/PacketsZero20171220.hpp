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

#ifndef HORIZON_ZONE_ZERO_20171220_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20171220_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20171220
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x095b,
	CZ_ADD_FRIENDS = 0x092e,
	CZ_CHANGE_DIRECTION = 0x096a,
	CZ_COMMAND_MER = 0x0921,
	CZ_ENTER = 0x08ad,
	CZ_GANGSI_RANK = 0x087e,
	CZ_ITEMLISTWIN_RES = 0x08a3,
	CZ_ITEM_PICKUP = 0x086c,
	CZ_ITEM_THROW = 0x08a5,
	CZ_JOIN_BATTLE_FIELD = 0x089b,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0934,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0872,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x092d,
	CZ_PARTY_JOIN_REQ = 0x02c4,
	CZ_REQNAME = 0x0438,
	CZ_REQNAME_BYGID = 0x0867,
	CZ_REQUEST_ACT = 0x0937,
	CZ_REQUEST_MOVE = 0x0899,
	CZ_REQUEST_TIME = 0x0838,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x07ec,
	CZ_REQ_CLOSE_BUYING_STORE = 0x089c,
	CZ_REQ_OPEN_BUYING_STORE = 0x091f,
	CZ_REQ_TRADE_BUYING_STORE = 0x085f,
	CZ_SEARCH_STORE_INFO = 0x0835,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x022d,
	CZ_SSILIST_ITEM_CLICK = 0x087a,
	CZ_USE_SKILL = 0x094d,
	CZ_USE_SKILL_TOGROUND = 0x0281,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0819,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20171220_PACKETS_HPP */
