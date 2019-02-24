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
 * Base Author - Sxyz (sagunxp@gmail.com)
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

#include "PacketHandlerRagexe20181219.hpp"

using namespace Horizon::Zone;
PacketHandlerRagexe20181219::PacketHandlerRagexe20181219(std::shared_ptr<ZoneSocket> socket)
: PacketHandlerRagexe20181212(socket)
{
	initialize_handlers();
}

PacketHandlerRagexe20181219::~PacketHandlerRagexe20181219()
{
	//
}

void PacketHandlerRagexe20181219::initialize_handlers()
{
	PacketHandler::initialize_handlers();

#define HANDLER_FUNC(packet) add_packet_handler(Ragexe20181219::packets::packet, boost::bind(&PacketHandlerRagexe20181219::Handle_ ## packet, this, boost::placeholders::_1));
#undef HANDLER_FUNC
}
