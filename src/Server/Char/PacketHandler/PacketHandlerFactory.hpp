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

#ifndef HORIZON_PACKETHANDLERFACTORY_HPP
#define HORIZON_PACKETHANDLERFACTORY_HPP

#include "Server/Char/PacketHandler/PacketHandler.hpp"
#include "Server/Char/PacketHandler/InterPacketHandler.hpp"

#include <memory>

namespace Horizon
{
namespace Char
{
class Session;
class InterSession;
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
	static std::shared_ptr<PacketHandler> CreatePacketHandler(std::shared_ptr<Session> session, uint32_t /*packet_ver*/)
	{
		return std::make_shared<PacketHandler>(session);
	}

	/**
	 * @brief Build an InterPacketHandler instance for an inter-server connection.
	 * @param[in|out] session    shared_ptr to a InterSession instance.
	 * @return shared pointer to a new instance of Horizon::Char::InterPacketHandler.
	 */
	static std::shared_ptr<InterPacketHandler> CreateInterPacketHandler(std::shared_ptr<InterSession> session)
	{
		return std::make_shared<InterPacketHandler>(session);
	}
};
}
}
#endif //HORIZON_PACKETHANDLERFACTORY_HPP
