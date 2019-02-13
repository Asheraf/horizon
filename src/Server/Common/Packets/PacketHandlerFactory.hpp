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
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 **************************************************/

/* This is an auto-generated file, please do not edit manually. */

#ifndef HORIZON_COMMON_PACKETS_PACKETHANDLERFACTORY_HPP
#define HORIZON_COMMON_PACKETS_PACKETHANDLERFACTORY_HPP

#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"
#include <stdint.h>

namespace Horizon
{
namespace Common
{
class CommonSocket;
class PacketHandler;
class PacketHandlerFactory
{
public:
	PacketHandlerFactory();
	~PacketHandlerFactory();
	/**
	 * @brief Build a PacketHandler instance for a client (player) connection.
	 * @param[in|out] session    shared_ptr to a Session instance.
	 * @return shared pointer to a new instance of Horizon::Common::PacketHandler.
	 */
	static std::shared_ptr<PacketHandler> create_packet_handler(std::shared_ptr<CommonSocket> socket, client_types client_type, uint32_t packet_ver);
};
}
}
#endif /* HORIZON_COMMON_PACKETS_PACKETHANDLERFACTORY_HPP*/
