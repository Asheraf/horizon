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

#include "CH_DELETE_CHAR.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

CH_DELETE_CHAR::CH_DELETE_CHAR(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_CH_DELETE_CHAR, s) { }

CH_DELETE_CHAR::~CH_DELETE_CHAR() { }

void CH_DELETE_CHAR::deliver()
{
}

ByteBuffer &CH_DELETE_CHAR::serialize()
{
	return buf();
}

void CH_DELETE_CHAR::handle(ByteBuffer &&buf)
{
	deserialize(buf);
	get_session()->clif()->character_delete_email(_character_id, _email);
}

void CH_DELETE_CHAR::deserialize(ByteBuffer &buf)
{
	buf >> _packet_id;
	buf >> _character_id;
	buf.read(_email, MAX_EMAIL_LENGTH);
}

