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

#ifndef HORIZON_AUTH_RAGEXE_PACKETSTRUCTS_HPP
#define HORIZON_AUTH_RAGEXE_PACKETSTRUCTS_HPP

#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACCEPT_LOGIN.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACCEPT_LOGIN2.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_AUTHREFUSE.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_INPUTEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_NEEDCARDPASS.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_NOTEXIST.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_NOTICE.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_NOTUSEDEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_EKEY_FAIL_NOTUSESEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_FIRST_LOGIN.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_GAME_GUARD.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_HASH.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ACK_PT_ID_INFO.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_ASK_PNGAMEROOM.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_EVENT_RESULT.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_NOTIFY_ERROR.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_OTP_AUTH_ACK.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_OTP_USER.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REALNAME_AUTH.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REFUSE_LOGIN.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REFUSE_LOGIN2.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REFUSE_LOGIN3.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REFUSE_LOGIN4.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQUEST_SECOND_PASSWORD.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQ_LOGIN_ACCOUNT_INFO.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQ_LOGIN_CARDPASS.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQ_LOGIN_NEWEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQ_LOGIN_OLDEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQ_MOBILE_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_REQ_NEW_USER.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_SHUTDOWN_INFO.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_AC_SHUTDOWN_NOTIFY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_ACK_LOGIN_ACCOUNT_INFO.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_ACK_LOGIN_CARDPASS.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_ACK_LOGIN_NEWEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_ACK_LOGIN_OLDEKEY.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_ACK_MOBILE_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_ACK_NEW_USER.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_CLIENT_TYPE.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_CONNECT_INFO_CHANGED.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_EXE_HASHCHECK.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN2.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN3.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN4.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN5.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN6.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN_HAN.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN_OTP.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_LOGIN_PCBANG.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_OTP_AUTH_REQ.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_REPLY_PNGAMEROOM.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_REQ_GAME_GUARD_CHECK.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_REQ_HASH.hpp"
#include "Server/Auth/Packets/Ragexe/Structs/PACKET_CA_SSO_LOGIN_REQ.hpp"

#endif /* HORIZON_AUTH_RAGEXE_PACKETSTRUCTS_HPP */
