/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#include "ClientSocketMgr.hpp"

#include "Server/Char/Packets/Ragexe/Packets.hpp"

#include "Server/Char/Packets/PacketHandler.hpp"
#include "Server/Char/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Char/Packets/Ragexe/20171220/PacketHandlerRagexe20171220.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketHandlerRagexe20180103.hpp"
#include "Server/Char/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Char/Packets/Ragexe/20180117/PacketHandlerRagexe20180117.hpp"

using namespace Horizon::Char;

void ClientSocketMgr::initialize_packet_length_db_Ragexe()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe::packets::name, len);
	ADD_PVL_DEF(CH_ACK_CHANGE_CHARACTERNAME, 6)
	ADD_PVL_DEF(CH_AVAILABLE_SECOND_PASSWD, 6)
	ADD_PVL_DEF(CH_CHARLIST_REQ, 2)
	ADD_PVL_DEF(CH_CHECKBOT, 32)
	ADD_PVL_DEF(CH_DELETE_CHAR, 46)
	ADD_PVL_DEF(CH_DELETE_CHAR2, 56)
	ADD_PVL_DEF(CH_DELETE_CHAR3, 12)
	ADD_PVL_DEF(CH_DELETE_CHAR3_CANCEL, 6)
	ADD_PVL_DEF(CH_DELETE_CHAR3_EXT, -1)
	ADD_PVL_DEF(CH_DELETE_CHAR3_RESERVED, 6)
	ADD_PVL_DEF(CH_DELETE_SECOND_PASSWD, 10)
	ADD_PVL_DEF(CH_EDIT_SECOND_PASSWD, 14)
	ADD_PVL_DEF(CH_ENTER, 17)
	ADD_PVL_DEF(CH_ENTER2, 37)
	ADD_PVL_DEF(CH_ENTER_CHECKBOT, 4)
	ADD_PVL_DEF(CH_MAKE_CHAR, 36)
	ADD_PVL_DEF(CH_MAKE_CHAR_NOT_STATS, 31)
	ADD_PVL_DEF(CH_MAKE_SECOND_PASSWD, 10)
	ADD_PVL_DEF(CH_NOT_AVAILABLE_SECOND_PASSWD, 10)
	ADD_PVL_DEF(CH_REQ_CHANGE_CHARACTERNAME, 30)
	ADD_PVL_DEF(CH_REQ_CHANGE_CHARACTER_SLOT, 8)
	ADD_PVL_DEF(CH_REQ_CHANGE_CHARNAME, 6)
	ADD_PVL_DEF(CH_REQ_CHARINFO_PER_PAGE, 6)
	ADD_PVL_DEF(CH_REQ_IS_VALID_CHARNAME, 34)
	ADD_PVL_DEF(CH_SECOND_PASSWD_ACK, 10)
	ADD_PVL_DEF(CH_SELECT_ACCESSIBLE_MAPNAME, 4)
	ADD_PVL_DEF(CH_SELECT_CHAR, 3)
	ADD_PVL_DEF(CH_SELECT_CHAR_GOINGTOBEUSED, 46)
	ADD_PVL_DEF(CH_UNKNOWN_PING, 6)
	ADD_PVL_DEF(CH_WAITING_LOGIN, 17)
	ADD_PVL_DEF(HC_ACCEPT_DELETECHAR, 2)
	ADD_PVL_DEF(HC_ACCEPT_ENTER, -1)
	ADD_PVL_DEF(HC_ACCEPT_ENTER2, -1)
	ADD_PVL_DEF(HC_ACCEPT_MAKECHAR, 108)
	ADD_PVL_DEF(HC_ACK_CHANGE_CHARACTER_SLOT, -1)
	ADD_PVL_DEF(HC_ACK_CHANGE_CHARNAME, 4)
	ADD_PVL_DEF(HC_ACK_CHARINFO_PER_PAGE, -1)
	ADD_PVL_DEF(HC_ACK_IS_VALID_CHARNAME, 4)
	ADD_PVL_DEF(HC_AVAILABLE_SECOND_PASSWD, 4)
	ADD_PVL_DEF(HC_BLOCK_CHARACTER, -1)
	ADD_PVL_DEF(HC_CHARACTER_LIST, -1)
	ADD_PVL_DEF(HC_CHARLIST_NOTIFY, 6)
	ADD_PVL_DEF(HC_CHARNOTBEENSELECTED, -1)
	ADD_PVL_DEF(HC_CHECKBOT, -1)
	ADD_PVL_DEF(HC_CHECKBOT_RESULT, 5)
	ADD_PVL_DEF(HC_DELETE_CHAR3, 10)
	ADD_PVL_DEF(HC_DELETE_CHAR3_CANCEL, 10)
	ADD_PVL_DEF(HC_DELETE_CHAR3_RESERVED, 14)
	ADD_PVL_DEF(HC_DELETE_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_EDIT_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_MAKE_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_NOTIFY_ACCESSIBLE_MAPNAME, -1)
	ADD_PVL_DEF(HC_NOTIFY_ZONESVR, 156)
	ADD_PVL_DEF(HC_NOT_AVAILABLE_SECOND_PASSWD, 8)
	ADD_PVL_DEF(HC_QUEUE_ORDER, 12)
	ADD_PVL_DEF(HC_REFUSE_DELETECHAR, 3)
	ADD_PVL_DEF(HC_REFUSE_ENTER, 3)
	ADD_PVL_DEF(HC_REFUSE_MAKECHAR, 3)
	ADD_PVL_DEF(HC_REFUSE_SELECTCHAR, 3)
	ADD_PVL_DEF(HC_REQUEST_CHARACTER_PASSWORD, 8)
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 13)
	ADD_PVL_DEF(HC_SECRETSCAN_DATA, -1)
	ADD_PVL_DEF(HC_UPDATE_CHARINFO, 157)
	ADD_PVL_DEF(HC_WAITING_LOGIN, 10)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20171220()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20171220::packets::name, len);
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 64)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20180103()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20180103::packets::name, len);
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 64)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20180117()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Char::Ragexe20180117::packets::name, len);
	ADD_PVL_DEF(HC_SECOND_PASSWD_LOGIN, 13)
#undef ADD_PVL_DEF
}

