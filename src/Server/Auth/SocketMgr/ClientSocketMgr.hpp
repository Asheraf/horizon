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
			
		client_types type = AuthServer->general_conf().get_client_type();
		uint32_t packet_version = AuthServer->general_conf().get_packet_version();

		/**
		 * Load base packet versions before overriding them with the configured version.
		 */
		if (packet_version >= 0) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero();
			}
		}

		if (packet_version >= 20180704) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180704();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180704();
			}
		} else if (packet_version >= 20180627) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180627();
			}
		} else if (packet_version >= 20171213) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171213();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171213();
			}
		} else if (packet_version >= 20171123) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171123();
			}
		} else if (packet_version >= 20171115) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171115();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171115();
			}
		} else if (packet_version >= 20171113) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171113();
			}
		} else if (packet_version >= 20171018) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171018();
			}
		} else if (packet_version >= 20170705) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170705();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170705();
			}
		} else if (packet_version >= 20170621) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170621();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170621();
			}
		} else if (packet_version >= 20170614) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170614();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170614();
			}
		} else if (packet_version >= 20170228) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170228();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170228();
			}
		}
		
		return true;
	}

	/* Ragexe Base Packets */
	void initialize_packet_length_db_Ragexe();
	/* RE Base Packets */
	void initialize_packet_length_db_RE();
	/* Zero Base Packets */
	void initialize_packet_length_db_Zero();
	/* 20170228 Ragexe */
	void initialize_packet_length_db_Ragexe_20170228();
	/* 20170228 RE */
	void initialize_packet_length_db_RE_20170228();
	/* 20170614 Ragexe */
	void initialize_packet_length_db_Ragexe_20170614();
	/* 20170614 RE */
	void initialize_packet_length_db_RE_20170614();
	/* 20170621 Ragexe */
	void initialize_packet_length_db_Ragexe_20170621();
	/* 20170621 RE */
	void initialize_packet_length_db_RE_20170621();
	/* 20170705 Ragexe */
	void initialize_packet_length_db_Ragexe_20170705();
	/* 20170705 RE */
	void initialize_packet_length_db_RE_20170705();
	/* 20171018 Zero */
	void initialize_packet_length_db_Zero_20171018();
	/* 20171113 Zero */
	void initialize_packet_length_db_Zero_20171113();
	/* 20171115 Ragexe */
	void initialize_packet_length_db_Ragexe_20171115();
	/* 20171115 RE */
	void initialize_packet_length_db_RE_20171115();
	/* 20171123 Zero */
	void initialize_packet_length_db_Zero_20171123();
	/* 20171213 Ragexe */
	void initialize_packet_length_db_Ragexe_20171213();
	/* 20171213 RE */
	void initialize_packet_length_db_RE_20171213();
	/* 20180627 Zero */
	void initialize_packet_length_db_Zero_20180627();
	/* 20180704 Ragexe */
	void initialize_packet_length_db_Ragexe_20180704();
	/* 20180704 RE */
	void initialize_packet_length_db_RE_20180704();

};
}
}
#define ClientSocktMgr Horizon::Auth::ClientSocketMgr::getInstance()
#define GET_AUTH_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)
#endif /* HORIZON_AUTH_CLIENTSOCKETMGR_HPP */
