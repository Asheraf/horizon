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

#ifndef HORIZON_CHAR_RAGEXE_PACKETSTRUCTS_HPP
#define HORIZON_CHAR_RAGEXE_PACKETSTRUCTS_HPP

#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_ACK_CHANGE_CHARACTERNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_AVAILABLE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_CHARLIST_REQ.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_CHECKBOT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_CHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_CHAR2.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_CHAR3.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_CHAR3_CANCEL.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_CHAR3_EXT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_CHAR3_RESERVED.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_DELETE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_EDIT_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_ENTER.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_ENTER2.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_ENTER_CHECKBOT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_MAKE_CHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_MAKE_CHAR_NOT_STATS.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_MAKE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_NOT_AVAILABLE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_REQ_CHANGE_CHARACTERNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_REQ_CHANGE_CHARACTER_SLOT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_REQ_CHANGE_CHARNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_REQ_CHARINFO_PER_PAGE.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_REQ_IS_VALID_CHARNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_SECOND_PASSWD_ACK.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_SELECT_ACCESSIBLE_MAPNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_SELECT_CHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_SELECT_CHAR_GOINGTOBEUSED.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_UNKNOWN_PING.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_CH_WAITING_LOGIN.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_DELETECHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_ENTER.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_ENTER2.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCEPT_MAKECHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACCOUNT_ID.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACK_CHANGE_CHARACTER_SLOT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACK_CHANGE_CHARNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACK_CHARINFO_PER_PAGE.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_ACK_IS_VALID_CHARNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_AVAILABLE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_BLOCK_CHARACTER.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_CHARACTER_LIST.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_CHARLIST_NOTIFY.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_CHARNOTBEENSELECTED.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_CHECKBOT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_CHECKBOT_RESULT.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_DELETE_CHAR3.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_DELETE_CHAR3_CANCEL.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_DELETE_CHAR3_RESERVED.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_DELETE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_EDIT_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_MAKE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_NOTIFY_ACCESSIBLE_MAPNAME.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_NOTIFY_ZONESVR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_NOT_AVAILABLE_SECOND_PASSWD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_QUEUE_ORDER.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_REFUSE_DELETECHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_REFUSE_ENTER.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_REFUSE_MAKECHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_REFUSE_SELECTCHAR.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_REQUEST_CHARACTER_PASSWORD.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_SECOND_PASSWD_LOGIN.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_SECRETSCAN_DATA.hpp"
#include "Server/Char/Packets/Ragexe/Structs/PACKET_HC_WAITING_LOGIN.hpp"

#endif /* HORIZON_CHAR_RAGEXE_PACKETSTRUCTS_HPP */
