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

#include "AC_ASK_PNGAMEROOM.hpp"
#include "Server/Auth/Session/AuthSession.hpp"

using namespace Horizon::Auth;
using namespace Horizon::Base;

AC_ASK_PNGAMEROOM::AC_ASK_PNGAMEROOM(std::shared_ptr<AuthSession> s)
 : NetworkPacket<AuthSession>(ID_AC_ASK_PNGAMEROOM, s) { }

AC_ASK_PNGAMEROOM::~AC_ASK_PNGAMEROOM() { }

void AC_ASK_PNGAMEROOM::deliver()
{
}
ByteBuffer &AC_ASK_PNGAMEROOM::serialize()
{
	return buf();
}
void AC_ASK_PNGAMEROOM::handle(ByteBuffer &&buf)
{
}
void AC_ASK_PNGAMEROOM::deserialize(ByteBuffer &buf)
{
}

