/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

#ifndef HORIZON_ZONE_PACKETHANDLERFACTORY_HPP
#define HORIZON_ZONE_PACKETHANDLERFACTORY_HPP

#include "Server/Zone/PacketHandler/PacketHandler.hpp"
#include "Server/Zone/PacketHandler/Versions/PacketHandler20141022.hpp"

#include <memory>

namespace Horizon
{
namespace Zone
{
class ZoneSocket;
class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	/**
	 * @brief Build a PacketHandler instance for a client (player) connection.
	 * @param[in|out] session    shared_ptr to a Session instance.
	 * @return shared pointer to a new instance of Horizon::Zone::PacketHandler.
	 */
	static std::shared_ptr<PacketHandler> create_packet_handler(std::shared_ptr<ZoneSocket> socket, uint32_t packet_ver)
	{
		if (packet_ver >= 20141022)
			return std::make_shared<PacketHandler20141022>(socket);

		return std::make_shared<PacketHandler>(socket);
	}
};
}
}
#endif //HORIZON_ZONE_PACKETHANDLERFACTORY_HPP

