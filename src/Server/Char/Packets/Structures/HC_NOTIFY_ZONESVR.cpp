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

#include "HC_NOTIFY_ZONESVR.hpp"
#include "Server/Char/Socket/CharSocket.hpp"

using namespace Horizon::Char::Packet;

HC_NOTIFY_ZONESVR::HC_NOTIFY_ZONESVR(std::shared_ptr<CharSocket> sock)
: NetworkPacket(ID_HC_NOTIFY_ZONESVR, sock) { }

HC_NOTIFY_ZONESVR::~HC_NOTIFY_ZONESVR() { }

void HC_NOTIFY_ZONESVR::deliver()
{
}

ByteBuffer HC_NOTIFY_ZONESVR::serialize()
{
}

