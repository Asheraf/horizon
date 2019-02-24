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

#include "ClientSocketMgr.hpp"

#include "Server/Auth/Packets/Ragexe/Packets.hpp"

#include "Server/Auth/Packets/PacketHandler.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketsRagexe20180704.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketHandlerRagexe20180704.hpp"

using namespace Horizon::Auth;

void ClientSocketMgr::initialize_packet_length_db_Ragexe()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe::packets::name, len);
	ADD_PVL_DEF(AC_ACCEPT_LOGIN, -1)
	ADD_PVL_DEF(AC_ACCEPT_LOGIN2, -1)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_AUTHREFUSE, 4)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_INPUTEKEY, 4)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_NEEDCARDPASS, 4)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_NOTEXIST, 4)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_NOTICE, 4)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_NOTUSEDEKEY, 4)
	ADD_PVL_DEF(AC_ACK_EKEY_FAIL_NOTUSESEKEY, 4)
	ADD_PVL_DEF(AC_ACK_FIRST_LOGIN, 2)
	ADD_PVL_DEF(AC_ACK_GAME_GUARD, 3)
	ADD_PVL_DEF(AC_ACK_HASH, -1)
	ADD_PVL_DEF(AC_ACK_PT_ID_INFO, 44)
	ADD_PVL_DEF(AC_ASK_PNGAMEROOM, 2)
	ADD_PVL_DEF(AC_EVENT_RESULT, 6)
	ADD_PVL_DEF(AC_LOGIN_OTP, -1)
	ADD_PVL_DEF(AC_NOTIFY_ERROR, -1)
	ADD_PVL_DEF(AC_OTP_AUTH_ACK, -1)
	ADD_PVL_DEF(AC_OTP_USER, 2)
	ADD_PVL_DEF(AC_REALNAME_AUTH, -1)
	ADD_PVL_DEF(AC_REFUSE_LOGIN, 23)
	ADD_PVL_DEF(AC_REFUSE_LOGIN2, 26)
	ADD_PVL_DEF(AC_REFUSE_LOGIN3, 7)
	ADD_PVL_DEF(AC_REFUSE_LOGIN4, 26)
	ADD_PVL_DEF(AC_REQUEST_SECOND_PASSWORD, 8)
	ADD_PVL_DEF(AC_REQ_LOGIN_ACCOUNT_INFO, 2)
	ADD_PVL_DEF(AC_REQ_LOGIN_CARDPASS, 11)
	ADD_PVL_DEF(AC_REQ_LOGIN_NEWEKEY, 11)
	ADD_PVL_DEF(AC_REQ_LOGIN_OLDEKEY, 11)
	ADD_PVL_DEF(AC_REQ_MOBILE_OTP, 6)
	ADD_PVL_DEF(AC_REQ_NEW_USER, 2)
	ADD_PVL_DEF(AC_SHUTDOWN_INFO, 6)
	ADD_PVL_DEF(AC_SHUTDOWN_NOTIFY, 10)
	ADD_PVL_DEF(CA_ACK_LOGIN_ACCOUNT_INFO, 40)
	ADD_PVL_DEF(CA_ACK_LOGIN_CARDPASS, 30)
	ADD_PVL_DEF(CA_ACK_LOGIN_NEWEKEY, 20)
	ADD_PVL_DEF(CA_ACK_LOGIN_OLDEKEY, 20)
	ADD_PVL_DEF(CA_ACK_MOBILE_OTP, -1)
	ADD_PVL_DEF(CA_ACK_NEW_USER, 4)
	ADD_PVL_DEF(CA_CLIENT_TYPE, 8)
	ADD_PVL_DEF(CA_CONNECT_INFO_CHANGED, 26)
	ADD_PVL_DEF(CA_EXE_HASHCHECK, 18)
	ADD_PVL_DEF(CA_LOGIN, 55)
	ADD_PVL_DEF(CA_LOGIN2, 47)
	ADD_PVL_DEF(CA_LOGIN3, 48)
	ADD_PVL_DEF(CA_LOGIN4, 60)
	ADD_PVL_DEF(CA_LOGIN5, 109)
	ADD_PVL_DEF(CA_LOGIN6, -1)
	ADD_PVL_DEF(CA_LOGIN_HAN, 85)
	ADD_PVL_DEF(CA_LOGIN_OTP, 68)
	ADD_PVL_DEF(CA_LOGIN_PCBANG, 84)
	ADD_PVL_DEF(CA_OTP_AUTH_REQ, 9)
	ADD_PVL_DEF(CA_REPLY_PNGAMEROOM, 3)
	ADD_PVL_DEF(CA_REQ_GAME_GUARD_CHECK, 2)
	ADD_PVL_DEF(CA_REQ_HASH, 2)
	ADD_PVL_DEF(CA_SSO_LOGIN_REQ, -1)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20171213()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20171213::packets::name, len);
	ADD_PVL_DEF(AC_LOGIN_OTP, -1)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20180704()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20180704::packets::name, len);
	ADD_PVL_DEF(AC_REFUSE_LOGIN4, 26)
#undef ADD_PVL_DEF
}

