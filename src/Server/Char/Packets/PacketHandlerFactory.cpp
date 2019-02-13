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
#include "Server/Char/Char.hpp"

#include "Server/Char/Packets/Ragexe/Packets.hpp"
#include "Server/Char/Packets/RE/Packets.hpp"
#include "Server/Char/Packets/Zero/Packets.hpp"
#include "Server/Char/Packets/Ragexe/20170104/PacketsRagexe20170104.hpp"
#include "Server/Char/Packets/Ragexe/20170104/PacketHandlerRagexe20170104.hpp"
#include "Server/Char/Packets/RE/20170104/PacketsRE20170104.hpp"
#include "Server/Char/Packets/RE/20170104/PacketHandlerRE20170104.hpp"
#include "Server/Char/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Char/Packets/Ragexe/20170228/PacketHandlerRagexe20170228.hpp"
#include "Server/Char/Packets/RE/20170228/PacketsRE20170228.hpp"
#include "Server/Char/Packets/RE/20170228/PacketHandlerRE20170228.hpp"
#include "Server/Char/Packets/RE/20170830/PacketsRE20170830.hpp"
#include "Server/Char/Packets/RE/20170830/PacketHandlerRE20170830.hpp"
#include "Server/Char/Packets/Ragexe/20170906/PacketsRagexe20170906.hpp"
#include "Server/Char/Packets/Ragexe/20170906/PacketHandlerRagexe20170906.hpp"
#include "Server/Char/Packets/Ragexe/20171220/PacketsRagexe20171220.hpp"
#include "Server/Char/Packets/Ragexe/20171220/PacketHandlerRagexe20171220.hpp"
#include "Server/Char/Packets/RE/20171220/PacketsRE20171220.hpp"
#include "Server/Char/Packets/RE/20171220/PacketHandlerRE20171220.hpp"
#include "Server/Char/Packets/Zero/20171220/PacketsZero20171220.hpp"
#include "Server/Char/Packets/Zero/20171220/PacketHandlerZero20171220.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketsRagexe20180103.hpp"
#include "Server/Char/Packets/Ragexe/20180103/PacketHandlerRagexe20180103.hpp"
#include "Server/Char/Packets/RE/20180103/PacketsRE20180103.hpp"
#include "Server/Char/Packets/RE/20180103/PacketHandlerRE20180103.hpp"
#include "Server/Char/Packets/Zero/20180103/PacketsZero20180103.hpp"
#include "Server/Char/Packets/Zero/20180103/PacketHandlerZero20180103.hpp"
#include "Server/Char/Packets/Ragexe/20180117/PacketsRagexe20180117.hpp"
#include "Server/Char/Packets/Ragexe/20180117/PacketHandlerRagexe20180117.hpp"
#include "Server/Char/Packets/RE/20180117/PacketsRE20180117.hpp"
#include "Server/Char/Packets/RE/20180117/PacketHandlerRE20180117.hpp"
#include "Server/Char/Packets/Zero/20180117/PacketsZero20180117.hpp"
#include "Server/Char/Packets/Zero/20180117/PacketHandlerZero20180117.hpp"

#include <memory>


using namespace Horizon::Char;

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
 * @return shared pointer to a new instance of Horizon::Char::PacketHandler.
 */
std::shared_ptr<PacketHandler> PacketHandlerFactory::create_packet_handler(std::shared_ptr<CharSocket> socket, client_types client_type, uint32_t packet_ver)
{
	if (packet_ver >= 20180117) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180117>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180117>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180117>(socket);
	}

	if (packet_ver >= 20180103) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20180103>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180103>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180103>(socket);
	}

	if (packet_ver >= 20171220) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171220>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171220>(socket);
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171220>(socket);
	}

	if (packet_ver >= 20170906) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170906>(socket);
	}

	if (packet_ver >= 20170830) {
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170830>(socket);
	}

	if (packet_ver >= 20170228) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170228>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170228>(socket);
	}

	if (packet_ver >= 20170104) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170104>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170104>(socket);
	}

	return std::make_shared<PacketHandler>(socket);
}
