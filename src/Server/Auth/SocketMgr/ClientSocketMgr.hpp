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

#ifndef HORIZON_AUTH_CLIENTSOCKETMGR_HPP
#define HORIZON_AUTH_CLIENTSOCKETMGR_HPP

#include "Core/Networking/AcceptSocketMgr.hpp"
#include "Server/Auth/Socket/AuthSocket.hpp"
#include "Server/Auth/Session/AuthSession.hpp"
#include "Server/Auth/PacketHandler/Packets.hpp"

namespace Horizon
{
namespace Auth
{
/**
 * Auth Accept Socket Manager for clients.
 * @brief Singleton class
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

		initialize_packet_version_length_db();
		
		return true;
	}

	void initialize_packet_version_length_db()
	{
#define ADD_PVL_VARIABLE(name) add_packet_length(Horizon::Auth::packets::name, -1);
#define ADD_PVL_FIXED(name) add_packet_length(Horizon::Auth::packets::name, sizeof(PACKET_ ## name));
		ADD_PVL_FIXED(CA_LOGIN)
		ADD_PVL_FIXED(CA_REQ_HASH)
		ADD_PVL_FIXED(CA_LOGIN2)
		ADD_PVL_FIXED(CA_LOGIN3)
		ADD_PVL_FIXED(CA_CONNECT_INFO_CHANGED)
		ADD_PVL_FIXED(CA_EXE_HASHCHECK)
		ADD_PVL_FIXED(CA_LOGIN_PCBANG)
		ADD_PVL_FIXED(CA_LOGIN4)
		ADD_PVL_FIXED(CA_LOGIN_HAN)
		ADD_PVL_VARIABLE(CA_SSO_LOGIN_REQ)
		ADD_PVL_FIXED(CA_LOGIN_OTP)
#undef ADD_PVL_VARIABLE
#undef ADD_PVL_FIXED
	}
};
}
}

#define ClientSocktMgr Horizon::Auth::ClientSocketMgr::getInstance()
#define GET_CA_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)

#endif // HORIZON_AUTH_CLIENTSOCKETMGR_HPP
