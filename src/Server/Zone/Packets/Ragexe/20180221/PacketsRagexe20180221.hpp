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

#ifndef HORIZON_ZONE_RAGEXE_20180221_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20180221_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20180221
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x0917,
	CZ_ADD_FRIENDS = 0x0436,
	CZ_CHANGE_DIRECTION = 0x0838,
	CZ_COMMAND_MER = 0x0876,
	CZ_ENTER = 0x0897,
	CZ_GANGSI_RANK = 0x0891,
	CZ_ITEMLISTWIN_RES = 0x0880,
	CZ_ITEM_PICKUP = 0x094e,
	CZ_ITEM_THROW = 0x0871,
	CZ_JOIN_BATTLE_FIELD = 0x0366,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x0879,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x091e,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0802,
	CZ_PARTY_JOIN_REQ = 0x093d,
	CZ_REQNAME = 0x0957,
	CZ_REQNAME_BYGID = 0x088f,
	CZ_REQNAME_BYGID2 = 0x0369,
	CZ_REQUEST_ACT = 0x096a,
	CZ_REQUEST_MOVE = 0x087d,
	CZ_REQUEST_TIME = 0x089d,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0817,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0929,
	CZ_REQ_OPEN_BUYING_STORE = 0x086f,
	CZ_REQ_TRADE_BUYING_STORE = 0x0883,
	CZ_SEARCH_STORE_INFO = 0x0867,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0899,
	CZ_SSILIST_ITEM_CLICK = 0x0964,
	CZ_USE_SKILL = 0x094b,
	CZ_USE_SKILL_TOGROUND = 0x094d,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0202,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20180221_PACKETS_HPP */
