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

#include "CH_MAKE_CHAR.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

CH_MAKE_CHAR::CH_MAKE_CHAR(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_CH_MAKE_CHAR, s) { }

CH_MAKE_CHAR::~CH_MAKE_CHAR() { }

void CH_MAKE_CHAR::deliver()
{

}

ByteBuffer &CH_MAKE_CHAR::serialize()
{
	return buf();
}

void CH_MAKE_CHAR::handle(ByteBuffer &&buf)
{
	deserialize(buf);
	
#if PACKET_VERSION >= 20151001
	get_session()->clif()->make_new_character(_name, _slot, _hair_color, _hair_style, _job_id, _gender);
#elif PACKET_VERSION >= 20120307
	get_session()->clif()->make_new_character(_name, _slot, _hair_color, _hair_style);
#endif
}

void CH_MAKE_CHAR::deserialize(ByteBuffer &buf)
{
	buf >> _packet_id;
	buf.read(_name, MAX_UNIT_NAME_LENGTH);
	buf >> _slot;
	buf >> _hair_color;
	buf >> _hair_style;
#if PACKET_VERSION >= 20151001
	buf >> _job_id;
	buf.read(_unknown_bytes, sizeof(short));
	buf >> _gender;
#endif
}

