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

#ifndef HORIZON_CHAR_PACKETHANDLERFACTORY_HPP
#define HORIZON_CHAR_PACKETHANDLERFACTORY_HPP

#include "Server/Char/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/Versions/PacketHandler20120307.hpp"
#include "Server/Char/PacketHandler/InterPacketHandler.hpp"

#include <memory>

namespace Horizon
{
namespace Char
{
class CharSocket;
class InterSocket;
class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	/**
	 * @brief Build a PacketHandler instance for a client (player) connection.
	 * @param[in|out] session    shared_ptr to a Session instance.
	 * @return shared pointer to a new instance of Horizon::Char::PacketHandler.
	 */
	static std::shared_ptr<PacketHandler> create_packet_handler(std::shared_ptr<CharSocket> socket, uint32_t packet_ver)
	{
		if (packet_ver >= 20120307)
			return std::make_shared<PacketHandler20120307>(socket);

		return std::make_shared<PacketHandler>(socket);
	}

	/**
	 * @brief Build an InterPacketHandler instance for an inter-server connection.
	 * @param[in|out] session    shared_ptr to a InterSession instance.
	 * @return shared pointer to a new instance of Horizon::Char::InterPacketHandler.
	 */
	static std::shared_ptr<InterPacketHandler> create_inter_packet_handler(std::shared_ptr<InterSocket> socket)
	{
		return std::make_shared<InterPacketHandler>(socket);
	}
};
}
}
#endif //HORIZON_CHAR_PACKETHANDLERFACTORY_HPP
