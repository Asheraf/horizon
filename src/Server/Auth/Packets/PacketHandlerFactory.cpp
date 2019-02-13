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
#include "Server/Auth/Packets/RE/Packets.hpp"
#include "Server/Auth/Packets/Zero/Packets.hpp"
#include "Server/Auth/Packets/Ragexe/20170228/PacketsRagexe20170228.hpp"
#include "Server/Auth/Packets/Ragexe/20170228/PacketHandlerRagexe20170228.hpp"
#include "Server/Auth/Packets/RE/20170228/PacketsRE20170228.hpp"
#include "Server/Auth/Packets/RE/20170228/PacketHandlerRE20170228.hpp"
#include "Server/Auth/Packets/Ragexe/20170614/PacketsRagexe20170614.hpp"
#include "Server/Auth/Packets/Ragexe/20170614/PacketHandlerRagexe20170614.hpp"
#include "Server/Auth/Packets/RE/20170614/PacketsRE20170614.hpp"
#include "Server/Auth/Packets/RE/20170614/PacketHandlerRE20170614.hpp"
#include "Server/Auth/Packets/Ragexe/20170621/PacketsRagexe20170621.hpp"
#include "Server/Auth/Packets/Ragexe/20170621/PacketHandlerRagexe20170621.hpp"
#include "Server/Auth/Packets/RE/20170621/PacketsRE20170621.hpp"
#include "Server/Auth/Packets/RE/20170621/PacketHandlerRE20170621.hpp"
#include "Server/Auth/Packets/Ragexe/20170705/PacketsRagexe20170705.hpp"
#include "Server/Auth/Packets/Ragexe/20170705/PacketHandlerRagexe20170705.hpp"
#include "Server/Auth/Packets/RE/20170705/PacketsRE20170705.hpp"
#include "Server/Auth/Packets/RE/20170705/PacketHandlerRE20170705.hpp"
#include "Server/Auth/Packets/Zero/20171018/PacketsZero20171018.hpp"
#include "Server/Auth/Packets/Zero/20171018/PacketHandlerZero20171018.hpp"
#include "Server/Auth/Packets/Zero/20171113/PacketsZero20171113.hpp"
#include "Server/Auth/Packets/Zero/20171113/PacketHandlerZero20171113.hpp"
#include "Server/Auth/Packets/Ragexe/20171115/PacketsRagexe20171115.hpp"
#include "Server/Auth/Packets/Ragexe/20171115/PacketHandlerRagexe20171115.hpp"
#include "Server/Auth/Packets/RE/20171115/PacketsRE20171115.hpp"
#include "Server/Auth/Packets/RE/20171115/PacketHandlerRE20171115.hpp"
#include "Server/Auth/Packets/Zero/20171123/PacketsZero20171123.hpp"
#include "Server/Auth/Packets/Zero/20171123/PacketHandlerZero20171123.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketsRagexe20171213.hpp"
#include "Server/Auth/Packets/Ragexe/20171213/PacketHandlerRagexe20171213.hpp"
#include "Server/Auth/Packets/RE/20171213/PacketsRE20171213.hpp"
#include "Server/Auth/Packets/RE/20171213/PacketHandlerRE20171213.hpp"
#include "Server/Auth/Packets/Zero/20180627/PacketsZero20180627.hpp"
#include "Server/Auth/Packets/Zero/20180627/PacketHandlerZero20180627.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketsRagexe20180704.hpp"
#include "Server/Auth/Packets/Ragexe/20180704/PacketHandlerRagexe20180704.hpp"
#include "Server/Auth/Packets/RE/20180704/PacketsRE20180704.hpp"
#include "Server/Auth/Packets/RE/20180704/PacketHandlerRE20180704.hpp"

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
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20180704>(socket);
	}

	if (packet_ver >= 20180627) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20180627>(socket);
	}

	if (packet_ver >= 20171213) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171213>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171213>(socket);
	}

	if (packet_ver >= 20171123) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171123>(socket);
	}

	if (packet_ver >= 20171115) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20171115>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20171115>(socket);
	}

	if (packet_ver >= 20171113) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171113>(socket);
	}

	if (packet_ver >= 20171018) {
		if (client_type == CLIENT_TYPE_ZERO)
			return std::make_shared<PacketHandlerZero20171018>(socket);
	}

	if (packet_ver >= 20170705) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170705>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170705>(socket);
	}

	if (packet_ver >= 20170621) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170621>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170621>(socket);
	}

	if (packet_ver >= 20170614) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170614>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170614>(socket);
	}

	if (packet_ver >= 20170228) {
		if (client_type == CLIENT_TYPE_RAGEXE)
			return std::make_shared<PacketHandlerRagexe20170228>(socket);
		if (client_type == CLIENT_TYPE_RAGEXE_RE)
			return std::make_shared<PacketHandlerRE20170228>(socket);
	}

	return std::make_shared<PacketHandler>(socket);
}
