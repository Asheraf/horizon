/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2020- Horizon Dev Team.
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


#include "HandledPackets.hpp"
#include "Server/Auth/Interface/AuthClientInterface.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/Auth.hpp"

using namespace Horizon::Auth;

/**
 * CA_CONNECT_INFO_CHANGED
 */
void CA_CONNECT_INFO_CHANGED::handle(ByteBuffer &&buf) { }

void CA_CONNECT_INFO_CHANGED::deserialize(ByteBuffer &buf) { }

/**
 * CA_ACK_LOGIN_ACCOUNT_INFO
 */
void CA_ACK_LOGIN_ACCOUNT_INFO::handle(ByteBuffer &&buf) { }

void CA_ACK_LOGIN_ACCOUNT_INFO::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN_PCBANG
 */
void CA_LOGIN_PCBANG::handle(ByteBuffer &&buf) { }

void CA_LOGIN_PCBANG::deserialize(ByteBuffer &buf) { }

/**
 * CA_OTP_AUTH_REQ
 */
void CA_OTP_AUTH_REQ::handle(ByteBuffer &&buf) { }

void CA_OTP_AUTH_REQ::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN3
 */
void CA_LOGIN3::handle(ByteBuffer &&buf) { }

void CA_LOGIN3::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN2
 */
void CA_LOGIN2::handle(ByteBuffer &&buf) { }

void CA_LOGIN2::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN6
 */
void CA_LOGIN6::handle(ByteBuffer &&buf) { }

void CA_LOGIN6::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN5
 */
void CA_LOGIN5::handle(ByteBuffer &&buf) { }

void CA_LOGIN5::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN4
 */
void CA_LOGIN4::handle(ByteBuffer &&buf) { }

void CA_LOGIN4::deserialize(ByteBuffer &buf) { }

/**
 * CA_REPLY_PNGAMEROOM
 */
void CA_REPLY_PNGAMEROOM::handle(ByteBuffer &&buf) { }

void CA_REPLY_PNGAMEROOM::deserialize(ByteBuffer &buf) { }

/**
 * CA_SSO_LOGIN_REQ
 */
void CA_SSO_LOGIN_REQ::handle(ByteBuffer &&buf) { }

void CA_SSO_LOGIN_REQ::deserialize(ByteBuffer &buf) { }

/**
 * CA_ACK_LOGIN_NEWEKEY
 */
void CA_ACK_LOGIN_NEWEKEY::handle(ByteBuffer &&buf) { }

void CA_ACK_LOGIN_NEWEKEY::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN_HAN
 */
void CA_LOGIN_HAN::handle(ByteBuffer &&buf) { }

void CA_LOGIN_HAN::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN
 */
void CA_LOGIN::handle(ByteBuffer &&buf)
{
    deserialize(buf);
	
	get_session()->clif()->process_login(_username, _password, _version, _client_type);
}

void CA_LOGIN::deserialize(ByteBuffer &buf) 
{
    buf >> _packet_id;
    buf >> _version;
    buf.read(_username, sizeof(_username));
    buf.read(_password, sizeof(_password));
    buf >> _client_type;
}

/**
 * CA_EXE_HASHCHECK
 */
void CA_EXE_HASHCHECK::handle(ByteBuffer &&buf) { }

void CA_EXE_HASHCHECK::deserialize(ByteBuffer &buf) { }

/**
 * CA_OTP_CODE
 */
void CA_OTP_CODE::handle(ByteBuffer &&buf) { }

void CA_OTP_CODE::deserialize(ByteBuffer &buf) { }

/**
 * CA_CLIENT_TYPE
 */
void CA_CLIENT_TYPE::handle(ByteBuffer &&buf) { }

void CA_CLIENT_TYPE::deserialize(ByteBuffer &buf) { }

/**
 * CA_ACK_NEW_USER
 */
void CA_ACK_NEW_USER::handle(ByteBuffer &&buf) { }

void CA_ACK_NEW_USER::deserialize(ByteBuffer &buf) { }

/**
 * CA_ACK_LOGIN_OLDEKEY
 */
void CA_ACK_LOGIN_OLDEKEY::handle(ByteBuffer &&buf) { }

void CA_ACK_LOGIN_OLDEKEY::deserialize(ByteBuffer &buf) { }

/**
 * CA_REQ_HASH
 */
void CA_REQ_HASH::handle(ByteBuffer &&buf) { }

void CA_REQ_HASH::deserialize(ByteBuffer &buf) { }

/**
 * CA_LOGIN_OTP
 */
void CA_LOGIN_OTP::handle(ByteBuffer &&buf) { }

void CA_LOGIN_OTP::deserialize(ByteBuffer &buf) { }

/**
 * CA_ACK_MOBILE_OTP
 */
void CA_ACK_MOBILE_OTP::handle(ByteBuffer &&buf) { }

void CA_ACK_MOBILE_OTP::deserialize(ByteBuffer &buf) { }

/**
 * CA_REQ_GAME_GUARD_CHECK
 */
void CA_REQ_GAME_GUARD_CHECK::handle(ByteBuffer &&buf) { }

void CA_REQ_GAME_GUARD_CHECK::deserialize(ByteBuffer &buf) { }

/**
 * CA_ACK_LOGIN_CARDPASS
 */
void CA_ACK_LOGIN_CARDPASS::handle(ByteBuffer &&buf) { }

void CA_ACK_LOGIN_CARDPASS::deserialize(ByteBuffer &buf) { }

