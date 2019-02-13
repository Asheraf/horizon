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

#ifndef HORIZON_ZONE_RAGEXE_20170419_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20170419_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20170419
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x023b,
	CZ_ADD_FRIENDS = 0x093a,
	CZ_CHANGE_DIRECTION = 0x0811,
	CZ_COMMAND_MER = 0x088f,
	CZ_ENTER = 0x0922,
	CZ_GANGSI_RANK = 0x0963,
	CZ_ITEMLISTWIN_RES = 0x088d,
	CZ_ITEM_PICKUP = 0x095c,
	CZ_ITEM_THROW = 0x0897,
	CZ_JOIN_BATTLE_FIELD = 0x0872,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x08aa,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0930,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY2 = 0x0365,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x086a,
	CZ_PARTY_JOIN_REQ = 0x0862,
	CZ_REQNAME = 0x0838,
	CZ_REQNAME_BYGID = 0x091b,
	CZ_REQUEST_ACT = 0x085a,
	CZ_REQUEST_MOVE = 0x085e,
	CZ_REQUEST_TIME = 0x0898,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0965,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0931,
	CZ_REQ_OPEN_BUYING_STORE = 0x089d,
	CZ_REQ_TRADE_BUYING_STORE = 0x095d,
	CZ_SEARCH_STORE_INFO = 0x0868,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0942,
	CZ_SSILIST_ITEM_CLICK = 0x0819,
	CZ_USE_SKILL = 0x0920,
	CZ_USE_SKILL_TOGROUND = 0x093f,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0935,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20170419_PACKETS_HPP */
