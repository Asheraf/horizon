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

#ifndef HORIZON_CHAR_CLIENTSOCKETMGR_HPP
#define HORIZON_CHAR_CLIENTSOCKETMGR_HPP
#include "Core/Networking/AcceptSocketMgr.hpp"

#include "Server/Char/Char.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"

namespace Horizon
{
namespace Char
{
/**
 * Manager of client sockets and initialization of the packet db * @brief Singleton class
 */
class ClientSocketMgr : public Horizon::Networking::AcceptSocketMgr<CharSocket>
{
	typedef Horizon::Networking::AcceptSocketMgr<CharSocket> BaseSocketMgr;
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
			
		client_types type = CharServer->general_conf().get_client_type();
		uint32_t packet_version = CharServer->general_conf().get_packet_version();

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

		if (packet_version >= 20180117) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180117();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180117();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180117();
			}
		} else if (packet_version >= 20180103) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180103();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180103();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180103();
			}
		} else if (packet_version >= 20171220) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171220();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171220();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171220();
			}
		} else if (packet_version >= 20170906) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170906();
			}
		} else if (packet_version >= 20170830) {
			if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170830();
			}
		} else if (packet_version >= 20170228) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170228();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170228();
			}
		} else if (packet_version >= 20170104) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170104();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170104();
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
	/* 20170104 Ragexe */
	void initialize_packet_length_db_Ragexe_20170104();
	/* 20170104 RE */
	void initialize_packet_length_db_RE_20170104();
	/* 20170228 Ragexe */
	void initialize_packet_length_db_Ragexe_20170228();
	/* 20170228 RE */
	void initialize_packet_length_db_RE_20170228();
	/* 20170830 RE */
	void initialize_packet_length_db_RE_20170830();
	/* 20170906 Ragexe */
	void initialize_packet_length_db_Ragexe_20170906();
	/* 20171220 Ragexe */
	void initialize_packet_length_db_Ragexe_20171220();
	/* 20171220 RE */
	void initialize_packet_length_db_RE_20171220();
	/* 20171220 Zero */
	void initialize_packet_length_db_Zero_20171220();
	/* 20180103 Ragexe */
	void initialize_packet_length_db_Ragexe_20180103();
	/* 20180103 RE */
	void initialize_packet_length_db_RE_20180103();
	/* 20180103 Zero */
	void initialize_packet_length_db_Zero_20180103();
	/* 20180117 Ragexe */
	void initialize_packet_length_db_Ragexe_20180117();
	/* 20180117 RE */
	void initialize_packet_length_db_RE_20180117();
	/* 20180117 Zero */
	void initialize_packet_length_db_Zero_20180117();

};
}
}
#define ClientSocktMgr Horizon::Char::ClientSocketMgr::getInstance()
#define GET_CHAR_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)
#endif /* HORIZON_CHAR_CLIENTSOCKETMGR_HPP */
