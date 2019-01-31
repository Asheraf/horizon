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

#ifndef HORIZON_ZONE_ZONESOCKETMGR_HPP
#define HORIZON_ZONE_ZONESOCKETMGR_HPP

#include "Core/Networking/AcceptSocketMgr.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/PacketHandler/Packets.hpp"
#include "Server/Zone/PacketHandler/Versions/PacketHandler20141022.hpp"

namespace Horizon
{
namespace Zone
{
/**
 * @brief Singleton class
 */
class ClientSocketMgr : public Horizon::Networking::AcceptSocketMgr<ZoneSocket>
{
	typedef Horizon::Networking::AcceptSocketMgr<ZoneSocket> BaseSocketMgr;
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
		initialize_packet_length_db_20141022();
		return true;
	}
	
	void initialize_packet_length_db()
	{
#define ADD_PVL_VARIABLE(name) add_packet_length(Horizon::Zone::packets::name, -1);
#define ADD_PVL_FIXED(name) add_packet_length(Horizon::Zone::packets::name, sizeof(PACKET_ ## name));
		ADD_PVL_FIXED(CZ_NOTIFY_ACTORINIT)
		ADD_PVL_FIXED(CZ_RESTART)
		ADD_PVL_FIXED(CZ_CHOOSE_MENU)
		ADD_PVL_FIXED(CZ_REQ_NEXT_SCRIPT)
		ADD_PVL_FIXED(CZ_INPUT_EDITDLG)
		ADD_PVL_FIXED(CZ_CLOSE_DIALOG)
		ADD_PVL_FIXED(CZ_REQ_GUILD_MENUINTERFACE)
		ADD_PVL_FIXED(CZ_REQ_GUILD_MENU)
		ADD_PVL_FIXED(CZ_REQ_DISCONNECT)
		ADD_PVL_VARIABLE(CZ_INPUT_EDITDLGSTR)
		ADD_PVL_FIXED(CZ_LOGIN_TIMESTAMP)
		ADD_PVL_FIXED(CZ_REQ_SCHEDULER_CASHITEM)
#undef ADD_PVL_VARIABLE
#undef ADD_PVL_FIXED
	}

	void initialize_packet_length_db_20141022()
	{
#define ADD_PVL_VARIABLE(name) add_packet_length(Horizon::Zone::PacketVer20141022::packets::name, -1);
#define ADD_PVL_FIXED(name) add_packet_length(Horizon::Zone::PacketVer20141022::packets::name, sizeof(PACKET_ ## name));
		ADD_PVL_FIXED(CZ_ENTER)
		ADD_PVL_FIXED(CZ_REQUEST_TIME)
		ADD_PVL_FIXED(CZ_REQNAME)
		ADD_PVL_FIXED(CZ_REQUEST_MOVE)
		/* ADD_PVL_FIXED(CZ_ACK_STORE_PASSWORD) */
		ADD_PVL_FIXED(CZ_REQUEST_ACT)
#undef ADD_PVL_VARIABLE
#undef ADD_PVL_FIXED
	}
};
}
}

#define ClientSocktMgr Horizon::Zone::ClientSocketMgr::getInstance()
#define GET_CZ_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)

#endif //HORIZON_ZONE_ZONESOCKETMGR_HPP
