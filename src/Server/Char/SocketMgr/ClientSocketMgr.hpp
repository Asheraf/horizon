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

#ifndef HORIZON_CHAR_CLIENTSOCKETMGR_HPP
#define HORIZON_CHAR_CLIENTSOCKETMGR_HPP

#include "Core/Networking/AcceptSocketMgr.hpp"
#include "Server/Char/Socket/CharSocket.hpp"
#include "Server/Char/PacketHandler/Packets.hpp"
#include "Server/Char/PacketHandler/Versions/PacketHandler20120307.hpp"

namespace Horizon
{
namespace Char
{
/**
 * @brief Singleton class
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

		initialize_packet_length_db();
		initialize_packet_length_db_20120307();

		return true;
	}

	void initialize_packet_length_db()
	{
#define ADD_PVL_VARIABLE(name) add_packet_length(Horizon::Char::packets::name, -1);
#define ADD_PVL_FIXED(name) add_packet_length(Horizon::Char::packets::name, sizeof(PACKET_ ## name));
		ADD_PVL_FIXED(CH_CONNECT)
		ADD_PVL_FIXED(CH_SELECT)
		ADD_PVL_FIXED(CH_CREATE)
		ADD_PVL_FIXED(CH_DELETE)
		ADD_PVL_FIXED(CH_KEEP_ALIVE)
		ADD_PVL_FIXED(CH_CREATE_2015)
		ADD_PVL_FIXED(CH_CHAR_RENAME_1)
		ADD_PVL_FIXED(CH_CHAR_RENAME_2)
		ADD_PVL_FIXED(CH_RENAME_CONFIRM)
		ADD_PVL_FIXED(CH_DELETE_2)
		ADD_PVL_FIXED(CH_DELETE_START)
		ADD_PVL_FIXED(CH_DELETE_ACCEPT)
		ADD_PVL_FIXED(CH_DELETE_CANCEL)
#undef ADD_PVL_VARIABLE
#undef ADD_PVL_FIXED
	}

	void initialize_packet_length_db_20120307()
	{
#define ADD_PVL_VARIABLE(name) add_packet_length(Horizon::Char::PacketVer20120307::packets::name, -1);
#define ADD_PVL_FIXED(name) add_packet_length(Horizon::Char::PacketVer20120307::packets::name, sizeof(PacketVer20120307::PACKET_ ## name));
		ADD_PVL_FIXED(CH_CREATE)
#undef ADD_PVL_VARIABLE
#undef ADD_PVL_FIXED
	}
};
}
}

#define ClientSocktMgr Horizon::Char::ClientSocketMgr::getInstance()
#define GET_CH_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)

#endif // HORIZON_CHAR_CLIENTSOCKETMGR_HPP
