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

#ifndef HORIZON_ZONE_ZERO_20180117_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20180117_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20180117
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x07e4,
	CZ_ADD_FRIENDS = 0x0946,
	CZ_CHANGE_DIRECTION = 0x089e,
	CZ_COMMAND_MER = 0x0963,
	CZ_ENTER = 0x087d,
	CZ_GANGSI_RANK = 0x092d,
	CZ_ITEMLISTWIN_RES = 0x089d,
	CZ_ITEM_PICKUP = 0x0886,
	CZ_ITEM_THROW = 0x083c,
	CZ_JOIN_BATTLE_FIELD = 0x0438,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0890,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x091c,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0929,
	CZ_PARTY_JOIN_REQ = 0x0361,
	CZ_REQNAME = 0x0891,
	CZ_REQNAME_BYGID = 0x0364,
	CZ_REQUEST_ACT = 0x0893,
	CZ_REQUEST_MOVE = 0x0921,
	CZ_REQUEST_TIME = 0x0919,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x086f,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0928,
	CZ_REQ_OPEN_BUYING_STORE = 0x0866,
	CZ_REQ_TRADE_BUYING_STORE = 0x095e,
	CZ_SEARCH_STORE_INFO = 0x0899,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0884,
	CZ_SSILIST_ITEM_CLICK = 0x0933,
	CZ_USE_SKILL = 0x0881,
	CZ_USE_SKILL_TOGROUND = 0x086e,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x091f,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20180117_PACKETS_HPP */
