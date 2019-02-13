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

#ifndef HORIZON_ZONE_RE_20170607_PACKETS_HPP
#define HORIZON_ZONE_RE_20170607_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace RE20170607
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0364,
	CZ_ADD_FRIENDS = 0x0885,
	CZ_CHANGE_DIRECTION = 0x085a,
	CZ_COMMAND_MER = 0x0942,
	CZ_ENTER = 0x0871,
	CZ_GANGSI_RANK = 0x0931,
	CZ_ITEMLISTWIN_RES = 0x0361,
	CZ_ITEM_PICKUP = 0x0897,
	CZ_ITEM_THROW = 0x0864,
	CZ_JOIN_BATTLE_FIELD = 0x0873,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x089d,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x088a,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0918,
	CZ_PARTY_JOIN_REQ = 0x0925,
	CZ_REQNAME = 0x0862,
	CZ_REQNAME_BYGID = 0x0944,
	CZ_REQUEST_ACT = 0x0938,
	CZ_REQUEST_MOVE = 0x0934,
	CZ_REQUEST_TIME = 0x07e4,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0863,
	CZ_REQ_CLOSE_BUYING_STORE = 0x093d,
	CZ_REQ_OPEN_BUYING_STORE = 0x0949,
	CZ_REQ_TRADE_BUYING_STORE = 0x0919,
	CZ_SEARCH_STORE_INFO = 0x085e,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0917,
	CZ_SSILIST_ITEM_CLICK = 0x0875,
	CZ_USE_SKILL = 0x08a9,
	CZ_USE_SKILL_TOGROUND = 0x0927,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x08ab,
};
}
}
}
#endif /* HORIZON_ZONE_RE_20170607_PACKETS_HPP */
