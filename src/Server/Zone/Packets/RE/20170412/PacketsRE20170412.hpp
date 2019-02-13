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

#ifndef HORIZON_ZONE_RE_20170412_PACKETS_HPP
#define HORIZON_ZONE_RE_20170412_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170412
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x095d,
	CZ_ADD_FRIENDS = 0x0942,
	CZ_CHANGE_DIRECTION = 0x091a,
	CZ_COMMAND_MER = 0x089a,
	CZ_ENTER = 0x091e,
	CZ_GANGSI_RANK = 0x0879,
	CZ_ITEMLISTWIN_RES = 0x0890,
	CZ_ITEM_PICKUP = 0x0959,
	CZ_ITEM_THROW = 0x089c,
	CZ_JOIN_BATTLE_FIELD = 0x092e,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0945,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x086d,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0869,
	CZ_PARTY_JOIN_REQ = 0x094f,
	CZ_REQNAME = 0x095b,
	CZ_REQNAME_BYGID = 0x0898,
	CZ_REQUEST_ACT = 0x08a1,
	CZ_REQUEST_MOVE = 0x0878,
	CZ_REQUEST_TIME = 0x0929,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0365,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0952,
	CZ_REQ_OPEN_BUYING_STORE = 0x0893,
	CZ_REQ_TRADE_BUYING_STORE = 0x0863,
	CZ_SEARCH_STORE_INFO = 0x088b,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0949,
	CZ_SSILIST_ITEM_CLICK = 0x095c,
	CZ_USE_SKILL = 0x087b,
	CZ_USE_SKILL_TOGROUND = 0x023b,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0938,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170412_PACKETS_HPP */
