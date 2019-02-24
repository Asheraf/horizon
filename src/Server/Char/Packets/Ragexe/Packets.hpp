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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#ifndef HORIZON_CHAR_RAGEXE_PACKETS_HPP
#define HORIZON_CHAR_RAGEXE_PACKETS_HPP

namespace Horizon
{
namespace Char
{
namespace Ragexe
{
enum packets
{
	CH_ACK_CHANGE_CHARACTERNAME = 0x08fd,
	CH_AVAILABLE_SECOND_PASSWD = 0x08c5,
	CH_CHARLIST_REQ = 0x09a1,
	CH_CHECKBOT = 0x07e7,
	CH_DELETE_CHAR = 0x0068,
	CH_DELETE_CHAR2 = 0x01fb,
	CH_DELETE_CHAR3 = 0x0829,
	CH_DELETE_CHAR3_CANCEL = 0x082b,
	CH_DELETE_CHAR3_EXT = 0x098f,
	CH_DELETE_CHAR3_RESERVED = 0x0827,
	CH_DELETE_SECOND_PASSWD = 0x08bc,
	CH_EDIT_SECOND_PASSWD = 0x08be,
	CH_ENTER = 0x0065,
	CH_ENTER2 = 0x0275,
	CH_ENTER_CHECKBOT = 0x07e5,
	CH_MAKE_CHAR = 0x0a39,
	CH_MAKE_CHAR_NOT_STATS = 0x0970,
	CH_MAKE_SECOND_PASSWD = 0x08ba,
	CH_NOT_AVAILABLE_SECOND_PASSWD = 0x08c3,
	CH_REQ_CHANGE_CHARACTERNAME = 0x08fc,
	CH_REQ_CHANGE_CHARACTER_SLOT = 0x08d4,
	CH_REQ_CHANGE_CHARNAME = 0x028f,
	CH_REQ_CHARINFO_PER_PAGE = 0x099c,
	CH_REQ_IS_VALID_CHARNAME = 0x028d,
	CH_SECOND_PASSWD_ACK = 0x08b8,
	CH_SELECT_ACCESSIBLE_MAPNAME = 0x0841,
	CH_SELECT_CHAR = 0x0066,
	CH_SELECT_CHAR_GOINGTOBEUSED = 0x028c,
	CH_UNKNOWN_PING = 0x0187,
	CH_WAITING_LOGIN = 0x08b0,
	HC_ACCEPT_DELETECHAR = 0x006f,
	HC_ACCEPT_ENTER = 0x006b,
	HC_ACCEPT_ENTER2 = 0x082d,
	HC_ACCEPT_MAKECHAR = 0x006d,
	HC_ACK_CHANGE_CHARACTER_SLOT = 0x08d5,
	HC_ACK_CHANGE_CHARNAME = 0x0290,
	HC_ACK_CHARINFO_PER_PAGE = 0x099d,
	HC_UPDATE_CHARINFO = 0x08e3,
	HC_ACK_IS_VALID_CHARNAME = 0x028e,
	HC_AVAILABLE_SECOND_PASSWD = 0x08c6,
	HC_BLOCK_CHARACTER = 0x020d,
	HC_CHARACTER_LIST = 0x0448,
	HC_CHARLIST_NOTIFY = 0x09a0,
	HC_CHARNOTBEENSELECTED = 0x028b,
	HC_CHECKBOT = 0x07e8,
	HC_CHECKBOT_RESULT = 0x07e9,
	HC_DELETE_CHAR3 = 0x082a,
	HC_DELETE_CHAR3_CANCEL = 0x082c,
	HC_DELETE_CHAR3_RESERVED = 0x0828,
	HC_DELETE_SECOND_PASSWD = 0x08bd,
	HC_EDIT_SECOND_PASSWD = 0x08bf,
	HC_MAKE_SECOND_PASSWD = 0x08bb,
	HC_NOTIFY_ACCESSIBLE_MAPNAME = 0x0840,
	HC_NOTIFY_ZONESVR = 0x0071,
	HC_NOT_AVAILABLE_SECOND_PASSWD = 0x08c4,
	HC_QUEUE_ORDER = 0x099e,
	HC_REFUSE_DELETECHAR = 0x0070,
	HC_REFUSE_ENTER = 0x006c,
	HC_REFUSE_MAKECHAR = 0x006e,
	HC_REFUSE_SELECTCHAR = 0x02ca,
	HC_REQUEST_CHARACTER_PASSWORD = 0x023e,
	HC_SECOND_PASSWD_LOGIN = 0x08b9,
	HC_SECRETSCAN_DATA = 0x09c2,
	HC_WAITING_LOGIN = 0x08af,
};
}
}
}
#endif /* HORIZON_CHAR_RAGEXE_PACKETS_HPP */
