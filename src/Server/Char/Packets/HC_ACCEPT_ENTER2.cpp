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

#include "HC_ACCEPT_ENTER2.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_ACCEPT_ENTER2::HC_ACCEPT_ENTER2(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_HC_ACCEPT_ENTER2, s) { }

HC_ACCEPT_ENTER2::~HC_ACCEPT_ENTER2() { }

void HC_ACCEPT_ENTER2::deliver(uint8_t total_slots, uint8_t premium_slots)
{
	serialize(total_slots, premium_slots);
	transmit();
}

ByteBuffer &HC_ACCEPT_ENTER2::serialize(uint8_t total_slots, uint8_t premium_slots)
{
	_total_slots = total_slots;
	_premium_slots = premium_slots;
	
	buf() << _packet_id;
	buf() << _packet_length;
	buf() << _total_slots;
	buf() << _premium_slots;
	buf() << _unknown_byte;
	buf() << _char_slots_1;
	buf() << _char_slots_2;
	buf().append(_unknown_bytes, sizeof(_unknown_bytes));
	
	return buf();
}

void HC_ACCEPT_ENTER2::handle(ByteBuffer &&buf)
{
}

void HC_ACCEPT_ENTER2::deserialize(ByteBuffer &buf)
{
}

