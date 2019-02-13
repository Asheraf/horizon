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

#include "ClientSocketMgr.hpp"

#include "Server/Auth/Packets/Ragexe/Packets.hpp"
#include "Server/Auth/Packets/RE/Packets.hpp"
#include "Server/Auth/Packets/Zero/Packets.hpp"

#include "Server/Auth/Packets/PacketHandler.hpp"
#include "Server/Auth/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Auth/Packets/Ragexe/20170228/PacketHandlerRagexe20170228.hpp"
#include "Server/Auth/Packets/RE/20170228/PacketsRE20170228.hpp"
#include "Server/Auth/Packets/RE/20170228/PacketHandlerRE20170228.hpp"
#include "Server/Auth/Packets/Ragexe/20170614/PacketsRagexe20170614.hpp"
#include "Server/Auth/Packets/Ragexe/20170614/PacketHandlerRagexe20170614.hpp"
#include "Server/Auth/Packets/RE/20170614/PacketsRE20170614.hpp"
#include "Server/Auth/Packets/RE/20170614/PacketHandlerRE20170614.hpp"
#include "Server/Auth/Packets/Ragexe/20170621/PacketsRagexe20170621.hpp"
#include "Server/Auth/Packets/Ragexe/20170621/PacketHandlerRagexe20170621.hpp"
#include "Server/Auth/Packets/RE/20170621/PacketsRE20170621.hpp"
#include "Server/Auth/Packets/RE/20170621/PacketHandlerRE20170621.hpp"
#include "Server/Auth/Packets/Ragexe/20170705/PacketsRagexe20170705.hpp"
#include "Server/Auth/Packets/Ragexe/20170705/PacketHandlerRagexe20170705.hpp"
#include "Server/Auth/Packets/RE/20170705/PacketsRE20170705.hpp"
#include "Server/Auth/Packets/RE/20170705/PacketHandlerRE20170705.hpp"
#include "Server/Auth/Packets/Zero/20171018/PacketsZero20171018.hpp"
#include "Server/Auth/Packets/Zero/20171018/PacketHandlerZero20171018.hpp"
#include "Server/Auth/Packets/Zero/20171113/PacketsZero20171113.hpp"
#include "Server/Auth/Packets/Zero/20171113/PacketHandlerZero20171113.hpp"
#include "Server/Auth/Packets/Ragexe/20171115/PacketsRagexe20171115.hpp"
#include "Server/Auth/Packets/Ragexe/20171115/PacketHandlerRagexe20171115.hpp"
#include "Server/Auth/Packets/RE/20171115/PacketsRE20171115.hpp"
#include "Server/Auth/Packets/RE/20171115/PacketHandlerRE20171115.hpp"
#include "Server/Auth/Packets/Zero/20171123/PacketsZero20171123.hpp"
#include "Server/Auth/Packets/Zero/20171123/PacketHandlerZero20171123.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"
#include "Server/Auth/Packets/RE/20171213/PacketsRE20171213.hpp"
#include "Server/Auth/Packets/RE/20171213/PacketHandlerRE20171213.hpp"
#include "Server/Auth/Packets/Zero/20180627/PacketsZero20180627.hpp"
#include "Server/Auth/Packets/Zero/20180627/PacketHandlerZero20180627.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketsRagexe20180704.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketHandlerRagexe20180704.hpp"
#include "Server/Auth/Packets/RE/20180704/PacketsRE20180704.hpp"
#include "Server/Auth/Packets/RE/20180704/PacketHandlerRE20180704.hpp"

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

void ClientSocketMgr::initialize_packet_length_db_RE()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, -1)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Zero::packets::name, len);
	ADD_PVL_DEF(AC_ACCEPT_LOGIN, -1)
	ADD_PVL_DEF(CA_OTP_CODE, 11)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170228()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20170228::packets::name, len);
	ADD_PVL_DEF(AC_ACCEPT_LOGIN, -1)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170228()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20170228::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170614()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20170614::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, 52)
	ADD_PVL_DEF(CA_OTP_CODE, 11)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170614()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20170614::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170621()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20170621::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, 57)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170621()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20170621::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20170705()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20170705::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, 64)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20170705()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20170705::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20171018()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Zero20171018::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, 64)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20171113()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Zero20171113::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, 68)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20171115()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20171115::packets::name, len);
	ADD_PVL_DEF(CA_LOGIN_OTP, 68)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20171115()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20171115::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20171123()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Zero20171123::packets::name, len);
	ADD_PVL_DEF(AC_LOGIN_OTP, -1)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20171213()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20171213::packets::name, len);
	ADD_PVL_DEF(AC_LOGIN_OTP, -1)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20171213()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20171213::packets::name, len);
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Zero_20180627()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Zero20180627::packets::name, len);
	ADD_PVL_DEF(AC_REFUSE_LOGIN4, 26)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_Ragexe_20180704()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::Ragexe20180704::packets::name, len);
	ADD_PVL_DEF(AC_REFUSE_LOGIN4, 26)
#undef ADD_PVL_DEF
}

void ClientSocketMgr::initialize_packet_length_db_RE_20180704()
{
#define ADD_PVL_DEF(name, len) add_packet_length(Horizon::Auth::RE20180704::packets::name, len);
#undef ADD_PVL_DEF
}

