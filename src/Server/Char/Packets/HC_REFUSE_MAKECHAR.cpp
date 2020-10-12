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

#include "HC_REFUSE_MAKECHAR.hpp"
#include "Server/Char/Socket/CharSocket.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_REFUSE_MAKECHAR::HC_REFUSE_MAKECHAR(std::shared_ptr<CharSocket> sock)
 : NetworkPacket<CharSocket>(ID_HC_REFUSE_MAKECHAR, sock) { }

HC_REFUSE_MAKECHAR::~HC_REFUSE_MAKECHAR() { }

void HC_REFUSE_MAKECHAR::deliver()
{
}
ByteBuffer &HC_REFUSE_MAKECHAR::serialize()
{
	return buf();
}
void HC_REFUSE_MAKECHAR::handle(ByteBuffer &&buf)
{
}
void HC_REFUSE_MAKECHAR::deserialize(ByteBuffer &buf)
{
}
