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

#include "PacketHandlerFactory.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"
#include "Server/Auth/Auth.hpp"

#include "Server/Auth/Packets/Ragexe/Packets.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketsRagexe20180704.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketHandlerRagexe20180704.hpp"

#include <memory>


using namespace Horizon::Auth;

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
 * @return shared pointer to a new instance of Horizon::Auth::PacketHandler.
 */
std::shared_ptr<PacketHandler> PacketHandlerFactory::create_packet_handler(std::shared_ptr<AuthSocket> socket, client_types client_type, uint32_t packet_ver)
{
	if (packet_ver >= 20180704) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180704>(socket);
	}

	if (packet_ver >= 20171213) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171213>(socket);
	}

	return std::make_shared<PacketHandler>(socket);
}
