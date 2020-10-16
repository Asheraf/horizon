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

#include "HC_ACCEPT_MAKECHAR.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_ACCEPT_MAKECHAR::HC_ACCEPT_MAKECHAR(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_HC_ACCEPT_MAKECHAR, s) { }

HC_ACCEPT_MAKECHAR::~HC_ACCEPT_MAKECHAR() { }

void HC_ACCEPT_MAKECHAR::deliver(uint32_t char_id, uint32_t start_zeny, std::string map_name, std::string name, uint8_t slot, uint32_t hair_color, uint32_t hair_style, uint32_t job_class, uint8_t gender)
{
	_c._character_id = char_id;
	_c._zeny = start_zeny;
	_c._status_points = 48;
	_c._hp = 40;
	_c._maximum_hp = 40;
	_c._sp = 40;
	_c._maximum_sp = 40;
	_c._walk_speed = DEFAULT_MOVEMENT_SPEED;
	_c._job_id = job_class;
	_c._hair_view_id = hair_style;
	strncpy(_c._name, name.c_str(), MAX_UNIT_NAME_LENGTH);
	_c._char_slot = slot;
#if (PACKET_VERSION >= 20100720 && PACKET_VERSION <= 20100727) || PACKET_VERSION >= 20100803
	strncpy(_c._map_name, map_name.c_str(), MAP_NAME_LENGTH_EXT);///< len: 16
#endif
#if PACKET_VERSION >= 20141016
	_c._gender = gender;                   ///< 146 0: Female, 1: Male, 99: Account-based.
#endif
	
	serialize();
	transmit();
}

ByteBuffer &HC_ACCEPT_MAKECHAR::serialize()
{
	buf() << _packet_id;
	buf().append((uint8_t *) &_c, sizeof(s_hc_character_list_data));
	return buf();
}

void HC_ACCEPT_MAKECHAR::handle(ByteBuffer &&buf)
{
}

void HC_ACCEPT_MAKECHAR::deserialize(ByteBuffer &buf)
{
}

