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

#include "HC_DELETE_CHAR3_CANCEL.hpp"
#include "Server/Char/Session/CharSession.hpp"

using namespace Horizon::Char;
using namespace Horizon::Base;

HC_DELETE_CHAR3_CANCEL::HC_DELETE_CHAR3_CANCEL(std::shared_ptr<CharSession> s)
 : NetworkPacket<CharSession>(ID_HC_DELETE_CHAR3_CANCEL, s) { }

HC_DELETE_CHAR3_CANCEL::~HC_DELETE_CHAR3_CANCEL() { }

void HC_DELETE_CHAR3_CANCEL::deliver(uint32_t char_id, hc_delete_cancel_result result)
{
	_character_id = char_id;
	_result = result;
	
	serialize();
	transmit();
}

ByteBuffer &HC_DELETE_CHAR3_CANCEL::serialize()
{
	buf() << _packet_id;
	buf() << _character_id;
	buf() << (int) _result;
	return buf();
}

void HC_DELETE_CHAR3_CANCEL::handle(ByteBuffer &&buf)
{
}

void HC_DELETE_CHAR3_CANCEL::deserialize(ByteBuffer &buf)
{
}

