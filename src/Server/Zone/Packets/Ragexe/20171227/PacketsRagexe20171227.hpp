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
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_ZONE_RAGEXE_20171227_PACKETS_HPP
#define HORIZON_ZONE_RAGEXE_20171227_PACKETS_HPP

namespace Horizon
{
namespace Zone
{
namespace Ragexe20171227
{
enum packets
{
	CZ_ACK_STORE_PASSWORD = 0x087d,
	CZ_ADD_FRIENDS = 0x0946,
	CZ_CHANGE_DIRECTION = 0x0369,
	CZ_COMMAND_MER = 0x08a5,
	CZ_ENTER = 0x092c,
	CZ_GANGSI_RANK = 0x0281,
	CZ_ITEMLISTWIN_RES = 0x0945,
	CZ_ITEM_PICKUP = 0x088d,
	CZ_ITEM_THROW = 0x0969,
	CZ_JOIN_BATTLE_FIELD = 0x088a,
	CZ_MOVE_ITEM_FROM_BODY_TO_STORE = 0x08a0,
	CZ_MOVE_ITEM_FROM_STORE_TO_BODY = 0x0888,
	CZ_PARTY_BOOKING_REQ_REGISTER = 0x096a,
	CZ_PARTY_JOIN_REQ = 0x0938,
	CZ_REQNAME = 0x0802,
	CZ_REQNAME_BYGID = 0x0368,
	CZ_REQUEST_ACT = 0x0361,
	CZ_REQUEST_MOVE = 0x0437,
	CZ_REQUEST_TIME = 0x035f,
	CZ_REQ_CLICK_TO_BUYING_STORE = 0x0360,
	CZ_REQ_CLOSE_BUYING_STORE = 0x0817,
	CZ_REQ_OPEN_BUYING_STORE = 0x0815,
	CZ_REQ_TRADE_BUYING_STORE = 0x0811,
	CZ_SEARCH_STORE_INFO = 0x0819,
	CZ_SEARCH_STORE_INFO_NEXT_PAGE = 0x0835,
	CZ_SSILIST_ITEM_CLICK = 0x0838,
	CZ_USE_SKILL = 0x083c,
	CZ_USE_SKILL_TOGROUND = 0x0438,
	CZ_USE_SKILL_TOGROUND_WITHTALKBOX = 0x0366,
	ZC_PRNPC_STATE = 0x091b,
};
}
}
}
#endif /* HORIZON_ZONE_RAGEXE_20171227_PACKETS_HPP */
