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

#ifndef HORIZON_ZONE_ZERO_20180103_PACKETS_HPP
#define HORIZON_ZONE_ZERO_20180103_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Zero20180103
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x095b,
	CZ_ADD_FRIENDS = 0x086d,
	CZ_CHANGE_DIRECTION = 0x035f,
	CZ_COMMAND_MER = 0x0860,
	CZ_ENTER = 0x0958,
	CZ_GANGSI_RANK = 0x0924,
	CZ_ITEMLISTWIN_RES = 0x0866,
	CZ_ITEM_PICKUP = 0x091e,
	CZ_ITEM_THROW = 0x0890,
	CZ_JOIN_BATTLE_FIELD = 0x087b,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x089d,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0966,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x0360,
	CZ_PARTY_JOIN_REQ = 0x093b,
	CZ_REQNAME = 0x08a6,
	CZ_REQNAME_BYGID = 0x095d,
	CZ_REQUEST_ACT = 0x0888,
	CZ_REQUEST_MOVE = 0x07e4,
	CZ_REQUEST_TIME = 0x0871,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0964,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0885,
	CZ_REQ_OPEN_BUYING_STORE = 0x0872,
	CZ_REQ_TRADE_BUYING_STORE = 0x0366,
	CZ_SEARCH_STORE_INFO = 0x0956,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0874,
	CZ_SSILIST_ITEM_CLICK = 0x096a,
	CZ_USE_SKILL = 0x0896,
	CZ_USE_SKILL_TOGROUND = 0x083c,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0938,
	ZC_PARTY_RECRUIT_CANCEL_VOLUNTEER_TO_PM = 0x091c,
	ZC_PRNPC_STATE = 0x091b,
};
}
}
}
#endif /* HORIZON_ZONE_ZERO_20180103_PACKETS_HPP */
