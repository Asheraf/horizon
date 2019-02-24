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

/* This is an auto-generated file, please do not edit manually. */

#include "PacketHandlerFactory.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"
#include "Server/Zone/Zone.hpp"

#include "Server/Zone/Packets/Ragexe/Packets.hpp"
#include "Server/Zone/Packets/Ragexe/20171206/PacketsRagexe20171206.hpp"
#include "Server/Zone/Packets/Ragexe/20171206/PacketHandlerRagexe20171206.hpp"
#include "Server/Zone/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Zone/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"
#include "Server/Zone/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Zone/Packets/Ragexe/20171220/PacketHandlerRagexe20171220.hpp"
#include "Server/Zone/Packets/Ragexe/20171227/PacketsRagexe20171227.hpp"
#include "Server/Zone/Packets/Ragexe/20171227/PacketHandlerRagexe20171227.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/20180103/PacketHandlerRagexe20180103.hpp"
#include "Server/Zone/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Zone/Packets/Ragexe/20180117/PacketHandlerRagexe20180117.hpp"
#include "Server/Zone/Packets/Ragexe/20180124/PacketsRagexe20180124.hpp"
#include "Server/Zone/Packets/Ragexe/20180124/PacketHandlerRagexe20180124.hpp"
#include "Server/Zone/Packets/Ragexe/20180131/PacketsRagexe20180131.hpp"
#include "Server/Zone/Packets/Ragexe/20180131/PacketHandlerRagexe20180131.hpp"
#include "Server/Zone/Packets/Ragexe/20180207/PacketsRagexe20180207.hpp"
#include "Server/Zone/Packets/Ragexe/20180207/PacketHandlerRagexe20180207.hpp"
#include "Server/Zone/Packets/Ragexe/20180213/PacketsRagexe20180213.hpp"
#include "Server/Zone/Packets/Ragexe/20180213/PacketHandlerRagexe20180213.hpp"
#include "Server/Zone/Packets/Ragexe/20180221/PacketsRagexe20180221.hpp"
#include "Server/Zone/Packets/Ragexe/20180221/PacketHandlerRagexe20180221.hpp"
#include "Server/Zone/Packets/Ragexe/20180307/PacketsRagexe20180307.hpp"
#include "Server/Zone/Packets/Ragexe/20180307/PacketHandlerRagexe20180307.hpp"
#include "Server/Zone/Packets/Ragexe/20180309/PacketsRagexe20180309.hpp"
#include "Server/Zone/Packets/Ragexe/20180309/PacketHandlerRagexe20180309.hpp"
#include "Server/Zone/Packets/Ragexe/20180314/PacketsRagexe20180314.hpp"
#include "Server/Zone/Packets/Ragexe/20180314/PacketHandlerRagexe20180314.hpp"
#include "Server/Zone/Packets/Ragexe/20180315/PacketsRagexe20180315.hpp"
#include "Server/Zone/Packets/Ragexe/20180315/PacketHandlerRagexe20180315.hpp"
#include "Server/Zone/Packets/Ragexe/20180321/PacketsRagexe20180321.hpp"
#include "Server/Zone/Packets/Ragexe/20180321/PacketHandlerRagexe20180321.hpp"
#include "Server/Zone/Packets/Ragexe/20180328/PacketsRagexe20180328.hpp"
#include "Server/Zone/Packets/Ragexe/20180328/PacketHandlerRagexe20180328.hpp"
#include "Server/Zone/Packets/Ragexe/20180404/PacketsRagexe20180404.hpp"
#include "Server/Zone/Packets/Ragexe/20180404/PacketHandlerRagexe20180404.hpp"
#include "Server/Zone/Packets/Ragexe/20180418/PacketsRagexe20180418.hpp"
#include "Server/Zone/Packets/Ragexe/20180418/PacketHandlerRagexe20180418.hpp"
#include "Server/Zone/Packets/Ragexe/20180425/PacketsRagexe20180425.hpp"
#include "Server/Zone/Packets/Ragexe/20180425/PacketHandlerRagexe20180425.hpp"
#include "Server/Zone/Packets/Ragexe/20180502/PacketsRagexe20180502.hpp"
#include "Server/Zone/Packets/Ragexe/20180502/PacketHandlerRagexe20180502.hpp"
#include "Server/Zone/Packets/Ragexe/20180509/PacketsRagexe20180509.hpp"
#include "Server/Zone/Packets/Ragexe/20180509/PacketHandlerRagexe20180509.hpp"
#include "Server/Zone/Packets/Ragexe/20180516/PacketsRagexe20180516.hpp"
#include "Server/Zone/Packets/Ragexe/20180516/PacketHandlerRagexe20180516.hpp"
#include "Server/Zone/Packets/Ragexe/20180523/PacketsRagexe20180523.hpp"
#include "Server/Zone/Packets/Ragexe/20180523/PacketHandlerRagexe20180523.hpp"
#include "Server/Zone/Packets/Ragexe/20180530/PacketsRagexe20180530.hpp"
#include "Server/Zone/Packets/Ragexe/20180530/PacketHandlerRagexe20180530.hpp"
#include "Server/Zone/Packets/Ragexe/20180605/PacketsRagexe20180605.hpp"
#include "Server/Zone/Packets/Ragexe/20180605/PacketHandlerRagexe20180605.hpp"
#include "Server/Zone/Packets/Ragexe/20180620/PacketsRagexe20180620.hpp"
#include "Server/Zone/Packets/Ragexe/20180620/PacketHandlerRagexe20180620.hpp"
#include "Server/Zone/Packets/Ragexe/20180621/PacketsRagexe20180621.hpp"
#include "Server/Zone/Packets/Ragexe/20180621/PacketHandlerRagexe20180621.hpp"
#include "Server/Zone/Packets/Ragexe/20180704/PacketsRagexe20180704.hpp"
#include "Server/Zone/Packets/Ragexe/20180704/PacketHandlerRagexe20180704.hpp"
#include "Server/Zone/Packets/Ragexe/20180718/PacketsRagexe20180718.hpp"
#include "Server/Zone/Packets/Ragexe/20180718/PacketHandlerRagexe20180718.hpp"
#include "Server/Zone/Packets/Ragexe/20180801/PacketsRagexe20180801.hpp"
#include "Server/Zone/Packets/Ragexe/20180801/PacketHandlerRagexe20180801.hpp"
#include "Server/Zone/Packets/Ragexe/20180808/PacketsRagexe20180808.hpp"
#include "Server/Zone/Packets/Ragexe/20180808/PacketHandlerRagexe20180808.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/PacketsRagexe20180822.hpp"
#include "Server/Zone/Packets/Ragexe/20180822/PacketHandlerRagexe20180822.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/PacketsRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/20180829/PacketHandlerRagexe20180829.hpp"
#include "Server/Zone/Packets/Ragexe/20180831/PacketsRagexe20180831.hpp"
#include "Server/Zone/Packets/Ragexe/20180831/PacketHandlerRagexe20180831.hpp"
#include "Server/Zone/Packets/Ragexe/20180912/PacketsRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/20180912/PacketHandlerRagexe20180912.hpp"
#include "Server/Zone/Packets/Ragexe/20180919/PacketsRagexe20180919.hpp"
#include "Server/Zone/Packets/Ragexe/20180919/PacketHandlerRagexe20180919.hpp"
#include "Server/Zone/Packets/Ragexe/20181002/PacketsRagexe20181002.hpp"
#include "Server/Zone/Packets/Ragexe/20181002/PacketHandlerRagexe20181002.hpp"
#include "Server/Zone/Packets/Ragexe/20181017/PacketsRagexe20181017.hpp"
#include "Server/Zone/Packets/Ragexe/20181017/PacketHandlerRagexe20181017.hpp"
#include "Server/Zone/Packets/Ragexe/20181024/PacketsRagexe20181024.hpp"
#include "Server/Zone/Packets/Ragexe/20181024/PacketHandlerRagexe20181024.hpp"
#include "Server/Zone/Packets/Ragexe/20181031/PacketsRagexe20181031.hpp"
#include "Server/Zone/Packets/Ragexe/20181031/PacketHandlerRagexe20181031.hpp"
#include "Server/Zone/Packets/Ragexe/20181107/PacketsRagexe20181107.hpp"
#include "Server/Zone/Packets/Ragexe/20181107/PacketHandlerRagexe20181107.hpp"
#include "Server/Zone/Packets/Ragexe/20181114/PacketsRagexe20181114.hpp"
#include "Server/Zone/Packets/Ragexe/20181114/PacketHandlerRagexe20181114.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/PacketsRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20181121/PacketHandlerRagexe20181121.hpp"
#include "Server/Zone/Packets/Ragexe/20181128/PacketsRagexe20181128.hpp"
#include "Server/Zone/Packets/Ragexe/20181128/PacketHandlerRagexe20181128.hpp"
#include "Server/Zone/Packets/Ragexe/20181205/PacketsRagexe20181205.hpp"
#include "Server/Zone/Packets/Ragexe/20181205/PacketHandlerRagexe20181205.hpp"
#include "Server/Zone/Packets/Ragexe/20181212/PacketsRagexe20181212.hpp"
#include "Server/Zone/Packets/Ragexe/20181212/PacketHandlerRagexe20181212.hpp"
#include "Server/Zone/Packets/Ragexe/20181219/PacketsRagexe20181219.hpp"
#include "Server/Zone/Packets/Ragexe/20181219/PacketHandlerRagexe20181219.hpp"
#include "Server/Zone/Packets/Ragexe/20181226/PacketsRagexe20181226.hpp"
#include "Server/Zone/Packets/Ragexe/20181226/PacketHandlerRagexe20181226.hpp"
#include "Server/Zone/Packets/Ragexe/20190109/PacketsRagexe20190109.hpp"
#include "Server/Zone/Packets/Ragexe/20190109/PacketHandlerRagexe20190109.hpp"
#include "Server/Zone/Packets/Ragexe/20190116/PacketsRagexe20190116.hpp"
#include "Server/Zone/Packets/Ragexe/20190116/PacketHandlerRagexe20190116.hpp"
#include "Server/Zone/Packets/Ragexe/20190123/PacketsRagexe20190123.hpp"
#include "Server/Zone/Packets/Ragexe/20190123/PacketHandlerRagexe20190123.hpp"

#include <memory>


using namespace Horizon::Zone;

PacketHandlerFactory::PacketHandlerFactory()
{
//
}

PacketHandlerFactory::~PacketHandlerFactory()
{
//
}

/**
 * @brief Build a PacketHandler instance for a client (player) connection.
 * @param[in|out] session    shared_ptr to a Session instance.
 * @return shared pointer to a new instance of Horizon::Zone::PacketHandler.
 */
std::shared_ptr<PacketHandler> PacketHandlerFactory::create_packet_handler(std::shared_ptr<ZoneSocket> socket, client_types client_type, uint32_t packet_ver)
{
	if (packet_ver >= 20190123) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20190123>(socket);
	}

	if (packet_ver >= 20190116) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20190116>(socket);
	}

	if (packet_ver >= 20190109) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20190109>(socket);
	}

	if (packet_ver >= 20181226) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181226>(socket);
	}

	if (packet_ver >= 20181219) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181219>(socket);
	}

	if (packet_ver >= 20181212) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181212>(socket);
	}

	if (packet_ver >= 20181205) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181205>(socket);
	}

	if (packet_ver >= 20181128) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181128>(socket);
	}

	if (packet_ver >= 20181121) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181121>(socket);
	}

	if (packet_ver >= 20181114) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181114>(socket);
	}

	if (packet_ver >= 20181107) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181107>(socket);
	}

	if (packet_ver >= 20181031) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181031>(socket);
	}

	if (packet_ver >= 20181024) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181024>(socket);
	}

	if (packet_ver >= 20181017) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181017>(socket);
	}

	if (packet_ver >= 20181002) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20181002>(socket);
	}

	if (packet_ver >= 20180919) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180919>(socket);
	}

	if (packet_ver >= 20180912) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180912>(socket);
	}

	if (packet_ver >= 20180831) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180831>(socket);
	}

	if (packet_ver >= 20180829) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180829>(socket);
	}

	if (packet_ver >= 20180822) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180822>(socket);
	}

	if (packet_ver >= 20180808) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180808>(socket);
	}

	if (packet_ver >= 20180801) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180801>(socket);
	}

	if (packet_ver >= 20180718) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180718>(socket);
	}

	if (packet_ver >= 20180704) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180704>(socket);
	}

	if (packet_ver >= 20180621) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180621>(socket);
	}

	if (packet_ver >= 20180620) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180620>(socket);
	}

	if (packet_ver >= 20180605) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180605>(socket);
	}

	if (packet_ver >= 20180530) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180530>(socket);
	}

	if (packet_ver >= 20180523) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180523>(socket);
	}

	if (packet_ver >= 20180516) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180516>(socket);
	}

	if (packet_ver >= 20180509) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180509>(socket);
	}

	if (packet_ver >= 20180502) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180502>(socket);
	}

	if (packet_ver >= 20180425) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180425>(socket);
	}

	if (packet_ver >= 20180418) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180418>(socket);
	}

	if (packet_ver >= 20180404) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180404>(socket);
	}

	if (packet_ver >= 20180328) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180328>(socket);
	}

	if (packet_ver >= 20180321) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180321>(socket);
	}

	if (packet_ver >= 20180315) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180315>(socket);
	}

	if (packet_ver >= 20180314) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180314>(socket);
	}

	if (packet_ver >= 20180309) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180309>(socket);
	}

	if (packet_ver >= 20180307) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180307>(socket);
	}

	if (packet_ver >= 20180221) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180221>(socket);
	}

	if (packet_ver >= 20180213) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180213>(socket);
	}

	if (packet_ver >= 20180207) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180207>(socket);
	}

	if (packet_ver >= 20180131) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180131>(socket);
	}

	if (packet_ver >= 20180124) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180124>(socket);
	}

	if (packet_ver >= 20180117) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180117>(socket);
	}

	if (packet_ver >= 20180103) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180103>(socket);
	}

	if (packet_ver >= 20171227) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171227>(socket);
	}

	if (packet_ver >= 20171220) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171220>(socket);
	}

	if (packet_ver >= 20171213) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171213>(socket);
	}

	if (packet_ver >= 20171206) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171206>(socket);
	}

	return std::make_shared<PacketHandler>(socket);
}
