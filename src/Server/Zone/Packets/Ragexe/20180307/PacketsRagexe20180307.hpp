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

#ifndef HORIZON_ZONE_RAGEXE_20180307_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20180307_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20180307
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0939,
	CZ_ADD_FRIENDS = 0x08aa,
	CZ_CHANGE_DIRECTION = 0x08ab,
	CZ_COMMAND_MER = 0x0944,
	CZ_ENTER = 0x07e4,
	CZ_GANGSI_RANK = 0x0281,
	CZ_ITEMLISTWIN_RES = 0x0870,
	CZ_ITEM_PICKUP = 0x0954,
	CZ_ITEM_THROW = 0x0437,
	CZ_JOIN_BATTLE_FIELD = 0x0951,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0920,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x088d,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0872,
	CZ_PARTY_JOIN_REQ = 0x0948,
	CZ_REQNAME = 0x0941,
	CZ_REQNAME_BYGID = 0x0957,
	CZ_REQUEST_ACT = 0x0969,
	CZ_REQUEST_MOVE = 0x0877,
	CZ_REQUEST_TIME = 0x086c,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0862,
	CZ_REQ_CLOSE_BUYING_STORE = 0x093d,
	CZ_REQ_OPEN_BUYING_STORE = 0x035f,
	CZ_REQ_TRADE_BUYING_STORE = 0x0937,
	CZ_SEARCH_STORE_INFO = 0x0864,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x08a6,
	CZ_SSILIST_ITEM_CLICK = 0x089b,
	CZ_USE_SKILL = 0x0893,
	CZ_USE_SKILL_TOGROUND = 0x0917,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0861,
	ZC_FRIENDS_STATE = 0x0206,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20180307_PACKETS_HPP */
