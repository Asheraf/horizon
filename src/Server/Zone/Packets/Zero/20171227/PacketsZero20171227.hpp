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

#ifndef HORIZON_ZONE_ZERO_20171227_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20171227_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20171227
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0930,
	CZ_ADD_FRIENDS = 0x0941,
	CZ_CHANGE_DIRECTION = 0x0860,
	CZ_COMMAND_MER = 0x095e,
	CZ_ENTER = 0x0874,
	CZ_GANGSI_RANK = 0x0925,
	CZ_ITEMLISTWIN_RES = 0x0968,
	CZ_ITEM_PICKUP = 0x0878,
	CZ_ITEM_THROW = 0x091c,
	CZ_JOIN_BATTLE_FIELD = 0x07ec,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x087b,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0885,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0894,
	CZ_PARTY_JOIN_REQ = 0x0945,
	CZ_REQNAME = 0x093e,
	CZ_REQNAME_BYGID = 0x0871,
	CZ_REQUEST_ACT = 0x086c,
	CZ_REQUEST_MOVE = 0x0946,
	CZ_REQUEST_TIME = 0x0939,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x089f,
	CZ_REQ_CLOSE_BUYING_STORE = 0x088b,
	CZ_REQ_OPEN_BUYING_STORE = 0x094b,
	CZ_REQ_TRADE_BUYING_STORE = 0x0920,
	CZ_SEARCH_STORE_INFO = 0x0889,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x02c4,
	CZ_SSILIST_ITEM_CLICK = 0x092d,
	CZ_USE_SKILL = 0x0967,
	CZ_USE_SKILL_TOGROUND = 0x0876,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0872,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20171227_PACKETS_HPP */
