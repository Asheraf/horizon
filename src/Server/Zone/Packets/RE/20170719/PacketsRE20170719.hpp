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

#ifndef HORIZON_ZONE_RE_20170719_PACKETS_HPP
#define HORIZON_ZONE_RE_20170719_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170719
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x089a,
	CZ_ADD_FRIENDS = 0x0946,
	CZ_CHANGE_DIRECTION = 0x0944,
	CZ_COMMAND_MER = 0x0369,
	CZ_ENTER = 0x08a8,
	CZ_GANGSI_RANK = 0x0368,
	CZ_ITEMLISTWIN_RES = 0x0885,
	CZ_ITEM_PICKUP = 0x087d,
	CZ_ITEM_THROW = 0x091b,
	CZ_JOIN_BATTLE_FIELD = 0x093e,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0966,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x08a6,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x092f,
	CZ_PARTY_JOIN_REQ = 0x086e,
	CZ_REQNAME = 0x07e4,
	CZ_REQNAME_BYGID = 0x091f,
	CZ_REQUEST_ACT = 0x022d,
	CZ_REQUEST_MOVE = 0x093d,
	CZ_REQUEST_TIME = 0x085a,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0863,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0367,
	CZ_REQ_OPEN_BUYING_STORE = 0x085e,
	CZ_REQ_TRADE_BUYING_STORE = 0x092c,
	CZ_SEARCH_STORE_INFO = 0x089d,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x092e,
	CZ_SSILIST_ITEM_CLICK = 0x0882,
	CZ_USE_SKILL = 0x0898,
	CZ_USE_SKILL_TOGROUND = 0x0891,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0881,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170719_PACKETS_HPP */
