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

#ifndef HORIZON_ZONE_ZERO_20171122_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20171122_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20171122
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0202,
	CZ_ADD_FRIENDS = 0x0928,
	CZ_CHANGE_DIRECTION = 0x089e,
	CZ_COMMAND_MER = 0x0811,
	CZ_ENTER = 0x091f,
	CZ_GANGSI_RANK = 0x0950,
	CZ_ITEMLISTWIN_RES = 0x0363,
	CZ_ITEM_PICKUP = 0x0918,
	CZ_ITEM_THROW = 0x0362,
	CZ_JOIN_BATTLE_FIELD = 0x0943,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0866,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0889,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0892,
	CZ_PARTY_JOIN_REQ = 0x08ad,
	CZ_REQNAME = 0x096a,
	CZ_REQNAME_BYGID = 0x0368,
	CZ_REQUEST_ACT = 0x0369,
	CZ_REQUEST_MOVE = 0x0437,
	CZ_REQUEST_TIME = 0x035f,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0360,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0817,
	CZ_REQ_OPEN_BUYING_STORE = 0x0815,
	CZ_REQ_TRADE_BUYING_STORE = 0x022d,
	CZ_SEARCH_STORE_INFO = 0x0819,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0835,
	CZ_SSILIST_ITEM_CLICK = 0x0838,
	CZ_USE_SKILL = 0x083c,
	CZ_USE_SKILL_TOGROUND = 0x0438,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0366,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20171122_PACKETS_HPP */
