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

#ifndef HORIZON_ZONE_RAGEXE_20170405_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20170405_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20170405
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x094c,
	CZ_ADD_FRIENDS = 0x086f,
	CZ_CHANGE_DIRECTION = 0x0865,
	CZ_COMMAND_MER = 0x0835,
	CZ_ENTER = 0x08a5,
	CZ_GANGSI_RANK = 0x0363,
	CZ_ITEMLISTWIN_RES = 0x0860,
	CZ_ITEM_PICKUP = 0x0369,
	CZ_ITEM_THROW = 0x0964,
	CZ_JOIN_BATTLE_FIELD = 0x094f,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x085f,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0893,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0281,
	CZ_PARTY_JOIN_REQ = 0x0864,
	CZ_REQNAME = 0x096a,
	CZ_REQNAME_BYGID = 0x0368,
	CZ_REQUEST_ACT = 0x0362,
	CZ_REQUEST_MOVE = 0x0437,
	CZ_REQUEST_TIME = 0x035f,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0360,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0817,
	CZ_REQ_OPEN_BUYING_STORE = 0x0815,
	CZ_REQ_TRADE_BUYING_STORE = 0x0811,
	CZ_SEARCH_STORE_INFO = 0x0819,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x022d,
	CZ_SSILIST_ITEM_CLICK = 0x0838,
	CZ_USE_SKILL = 0x083c,
	CZ_USE_SKILL_TOGROUND = 0x0438,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0366,
	ZC_NOTIFY_EXP = 0x0acc,
	ZC_PAR_CHANGE = 0x0acb,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20170405_PACKETS_HPP */
