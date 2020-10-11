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

#include "AC_REQ_LOGIN_ACCOUNT_INFO.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"

using namespace Horizon;

AC_REQ_LOGIN_ACCOUNT_INFO::AC_REQ_LOGIN_ACCOUNT_INFO(std::shared_ptr<AuthSocket> sock)
 : Base::NetworkPacket<AuthSocket>(ID_AC_REQ_LOGIN_ACCOUNT_INFO, sock) { }

AC_REQ_LOGIN_ACCOUNT_INFO::~AC_REQ_LOGIN_ACCOUNT_INFO() { }

void AC_REQ_LOGIN_ACCOUNT_INFO::deliver()
{
}

ByteBuffer &AC_REQ_LOGIN_ACCOUNT_INFO::serialize()
{
	return buf();
}

void AC_REQ_LOGIN_ACCOUNT_INFO::handle(ByteBuffer &&buf)
{
}

void AC_REQ_LOGIN_ACCOUNT_INFO::deserialize(ByteBuffer &buf)
{
}

