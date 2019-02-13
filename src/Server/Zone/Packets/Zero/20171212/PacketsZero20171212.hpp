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

#ifndef HORIZON_ZONE_ZERO_20171212_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20171212_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20171212
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0959,
	CZ_ADD_FRIENDS = 0x0893,
	CZ_CHANGE_DIRECTION = 0x0862,
	CZ_COMMAND_MER = 0x0897,
	CZ_ENTER = 0x0920,
	CZ_GANGSI_RANK = 0x0860,
	CZ_ITEMLISTWIN_RES = 0x093a,
	CZ_ITEM_PICKUP = 0x0835,
	CZ_ITEM_THROW = 0x0366,
	CZ_JOIN_BATTLE_FIELD = 0x083c,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0870,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0936,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x087a,
	CZ_PARTY_JOIN_REQ = 0x088d,
	CZ_REQNAME = 0x0941,
	CZ_REQNAME_BYGID = 0x0885,
	CZ_REQUEST_ACT = 0x08ac,
	CZ_REQUEST_MOVE = 0x0864,
	CZ_REQUEST_TIME = 0x095f,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0436,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0934,
	CZ_REQ_OPEN_BUYING_STORE = 0x08a4,
	CZ_REQ_TRADE_BUYING_STORE = 0x087b,
	CZ_SEARCH_STORE_INFO = 0x095c,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x095b,
	CZ_SSILIST_ITEM_CLICK = 0x089e,
	CZ_USE_SKILL = 0x0281,
	CZ_USE_SKILL_TOGROUND = 0x0878,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0940,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20171212_PACKETS_HPP */
