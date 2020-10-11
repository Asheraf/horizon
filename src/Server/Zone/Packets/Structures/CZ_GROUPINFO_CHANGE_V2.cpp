/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Horizon Dev Team.
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

#include "CZ_GROUPINFO_CHANGE_V2.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"

using namespace Horizon::Zone::Packet;

CZ_GROUPINFO_CHANGE_V2::CZ_GROUPINFO_CHANGE_V2(std::shared_ptr<ZoneSocket> sock)
: NetworkPacket(ID_CZ_GROUPINFO_CHANGE_V2, sock) { }

CZ_GROUPINFO_CHANGE_V2::~CZ_GROUPINFO_CHANGE_V2() { }

void CZ_GROUPINFO_CHANGE_V2::handle(ByteBuffer &buf)
{
}

void CZ_GROUPINFO_CHANGE_V2::deserialize(ByteBuffer &buf)
{
}

