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

#ifndef HORIZON_AUTH_CLIENTSOCKETMGR_HPP
#define HORIZON_AUTH_CLIENTSOCKETMGR_HPP
#include "Core/Networking/AcceptSocketMgr.hpp"

#include "Server/Auth/Auth.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"

namespace Horizon
{
namespace Auth
{
/**
 * Manager of client sockets and initialization of the packet db * @brief Singleton class
 */
class ClientSocketMgr : public Horizon::Networking::AcceptSocketMgr<AuthSocket>
{
	typedef Horizon::Networking::AcceptSocketMgr<AuthSocket> BaseSocketMgr;
public:
	static ClientSocketMgr *getInstance()
	{
		static ClientSocketMgr instance;
		return &instance;
	}

	bool start(boost::asio::io_service &io_service, std::string const &listen_ip, uint16_t port, uint32_t threads = 1)
	{
		if (!BaseSocketMgr::start(io_service, listen_ip, port, threads))
			return false;

		client_type type = AuthServer->general_conf().get_client_type();
		uint32_t packet_version = AuthServer->general_conf().get_packet_version();

		/**
		 * Load base packet versions before overriding them with the configured version.
		 */
		if (packet_version >= 0) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe();
			}
		}

		if (packet_version >= 20180704) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180704();
			}
		} else if (packet_version >= 20171213) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171213();
			}
		}

		return true;
	}

	/* Ragexe Base Packets */
	void initialize_packet_length_db_Ragexe();
	/* 20171213 Ragexe */
	void initialize_packet_length_db_Ragexe_20171213();
	/* 20180704 Ragexe */
	void initialize_packet_length_db_Ragexe_20180704();

};
}
}
#define ClientSocktMgr Horizon::Auth::ClientSocketMgr::getInstance()
#define GET_AUTH_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)
#endif /* HORIZON_AUTH_CLIENTSOCKETMGR_HPP */
