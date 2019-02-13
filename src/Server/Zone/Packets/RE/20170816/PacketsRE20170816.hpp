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

#ifndef HORIZON_ZONE_RE_20170816_PACKETS_HPP
#define HORIZON_ZONE_RE_20170816_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170816
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0882,
	CZ_ADD_FRIENDS = 0x08a3,
	CZ_CHANGE_DIRECTION = 0x0950,
	CZ_COMMAND_MER = 0x08ac,
	CZ_ENTER = 0x093d,
	CZ_GANGSI_RANK = 0x08a7,
	CZ_ITEMLISTWIN_RES = 0x0361,
	CZ_ITEM_PICKUP = 0x087e,
	CZ_ITEM_THROW = 0x0941,
	CZ_JOIN_BATTLE_FIELD = 0x0884,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0959,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0925,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0888,
	CZ_PARTY_JOIN_REQ = 0x093a,
	CZ_REQNAME = 0x022d,
	CZ_REQNAME_BYGID = 0x085a,
	CZ_REQUEST_ACT = 0x0438,
	CZ_REQUEST_MOVE = 0x08a9,
	CZ_REQUEST_TIME = 0x0889,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0921,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0864,
	CZ_REQ_OPEN_BUYING_STORE = 0x092c,
	CZ_REQ_TRADE_BUYING_STORE = 0x0881,
	CZ_SEARCH_STORE_INFO = 0x0960,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x035f,
	CZ_SSILIST_ITEM_CLICK = 0x091c,
	CZ_USE_SKILL = 0x0940,
	CZ_USE_SKILL_TOGROUND = 0x0862,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0362,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170816_PACKETS_HPP */
