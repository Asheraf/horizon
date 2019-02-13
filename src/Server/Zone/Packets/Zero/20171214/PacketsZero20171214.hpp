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

#ifndef HORIZON_ZONE_ZERO_20171214_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20171214_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20171214
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x085b,
	CZ_ADD_FRIENDS = 0x08a3,
	CZ_CHANGE_DIRECTION = 0x094a,
	CZ_COMMAND_MER = 0x094d,
	CZ_ENTER = 0x0871,
	CZ_ENTER2 = 0x0436,
	CZ_GANGSI_RANK = 0x0281,
	CZ_ITEMLISTWIN_RES = 0x0873,
	CZ_ITEM_PICKUP = 0x0894,
	CZ_ITEM_THROW = 0x02c4,
	CZ_JOIN_BATTLE_FIELD = 0x0864,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x088c,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x095a,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x085e,
	CZ_PARTY_JOIN_REQ = 0x0951,
	CZ_REQNAME = 0x0438,
	CZ_REQNAME_BYGID = 0x0862,
	CZ_REQUEST_ACT = 0x0933,
	CZ_REQUEST_MOVE = 0x086a,
	CZ_REQUEST_TIME = 0x0960,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0886,
	CZ_REQ_CLOSE_BUYING_STORE = 0x08ac,
	CZ_REQ_OPEN_BUYING_STORE = 0x0969,
	CZ_REQ_TRADE_BUYING_STORE = 0x0897,
	CZ_SEARCH_STORE_INFO = 0x0835,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x023b,
	CZ_SSILIST_ITEM_CLICK = 0x083c,
	CZ_USE_SKILL = 0x0892,
	CZ_USE_SKILL_TOGROUND = 0x096a,
	CZ_USE_SKILL_TOGROUND2 = 0x0366,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x08a5,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20171214_PACKETS_HPP */
