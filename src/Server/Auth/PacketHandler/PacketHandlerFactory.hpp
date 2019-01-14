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

#ifndef HORIZON_AUTH_PACKETHANDLERFACTORY_HPP
#define HORIZON_AUTH_PACKETHANDLERFACTORY_HPP

#include "Server/Auth/PacketHandler/PacketHandler.hpp"
#include "Server/Auth/PacketHandler/InterPacketHandler.hpp"
#include "Server/Auth/PacketHandler/Versions/PacketHandler20170315.hpp"
#include "Server/Auth/PacketHandler/Versions/PacketHandler20171113.hpp"

namespace Horizon
{
namespace Auth
{
class AuthSocket;
class InterSocket;
class PacketHandlerFactory
{
public:
	PacketHandlerFactory() { };
	~PacketHandlerFactory() { };

	/**
	 * @brief Creates a packet handler object for a client connected to the auth-server,
	 *        based on the connected client's packet version.
	 * @param[in] session    constant reference to the session in question.
	 * @param[in] packet_ver version of the client of the connected session.
	 * @return shared pointer to a new packet handler object for the client version or default.
	 */
	static std::shared_ptr<PacketHandler> create_auth_packet_handler(std::shared_ptr<AuthSocket> socket, int packet_ver)
	{
		if (packet_ver >= 20171113)
			return std::make_shared<PacketHandler20171113>(socket);
		else if (packet_ver >= 20170315)
			return std::make_shared<PacketHandler20170315>(socket);

		return std::make_shared<PacketHandler>(socket);
	}

	/**
	 * @brief Creates a packet handler object for a server connected to the auth-server.
	 * @param[in] session    constant reference to the session in question.
	 * @return shared pointer to a new packet handler object.
	 */
	static std::shared_ptr<InterPacketHandler> create_inter_packet_handler(std::shared_ptr<InterSocket> socket)
	{
		return std::make_shared<InterPacketHandler>(socket);
	}
};
}
}

#endif //HORIZON_AUTH_PACKETHANDLERFACTORY_HPP
