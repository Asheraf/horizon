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

#include "HC_CHECKBOT_RESULT.hpp"
#include "Server/Char/Socket/CharSocket.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_CHECKBOT_RESULT::HC_CHECKBOT_RESULT(std::shared_ptr<CharSocket> sock)
 : NetworkPacket<CharSocket>(ID_HC_CHECKBOT_RESULT, sock) { }

HC_CHECKBOT_RESULT::~HC_CHECKBOT_RESULT() { }

void HC_CHECKBOT_RESULT::deliver()
{
}
ByteBuffer &HC_CHECKBOT_RESULT::serialize()
{
	return buf();
}
void HC_CHECKBOT_RESULT::handle(ByteBuffer &&buf)
{
}
void HC_CHECKBOT_RESULT::deserialize(ByteBuffer &buf)
{
}

