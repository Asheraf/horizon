/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
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

#ifndef HORIZON_ZONE_CLIENTSOCKETMGR_HPP
#define HORIZON_ZONE_CLIENTSOCKETMGR_HPP
#include "Core/Networking/AcceptSocketMgr.hpp"

#include "Server/Zone/Zone.hpp"
#include "Server/Zone/Socket/ZoneSocket.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Common/Models/Configuration/GeneralServerConfiguration.hpp"

namespace Horizon
{
namespace Zone
{
/**
 * Manager of client sockets and initialization of the packet db * @brief Singleton class
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

		client_type type = ZoneServer->general_conf().get_client_type();
		uint32_t packet_version = ZoneServer->general_conf().get_packet_version();

		/**
		 * Load base packet versions before overriding them with the configured version.
		 */
		if (packet_version >= 0) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe();
			}
		}

		if (packet_version >= 20190123) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20190123();
			}
		} else if (packet_version >= 20190116) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20190116();
			}
		} else if (packet_version >= 20190109) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20190109();
			}
		} else if (packet_version >= 20181226) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181226();
			}
		} else if (packet_version >= 20181219) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181219();
			}
		} else if (packet_version >= 20181212) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181212();
			}
		} else if (packet_version >= 20181205) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181205();
			}
		} else if (packet_version >= 20181128) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181128();
			}
		} else if (packet_version >= 20181121) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181121();
			}
		} else if (packet_version >= 20181114) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181114();
			}
		} else if (packet_version >= 20181107) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181107();
			}
		} else if (packet_version >= 20181031) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181031();
			}
		} else if (packet_version >= 20181024) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181024();
			}
		} else if (packet_version >= 20181017) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181017();
			}
		} else if (packet_version >= 20181002) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181002();
			}
		} else if (packet_version >= 20180919) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180919();
			}
		} else if (packet_version >= 20180912) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180912();
			}
		} else if (packet_version >= 20180831) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180831();
			}
		} else if (packet_version >= 20180829) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180829();
			}
		} else if (packet_version >= 20180822) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180822();
			}
		} else if (packet_version >= 20180808) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180808();
			}
		} else if (packet_version >= 20180801) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180801();
			}
		} else if (packet_version >= 20180718) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180718();
			}
		} else if (packet_version >= 20180704) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180704();
			}
		} else if (packet_version >= 20180621) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180621();
			}
		} else if (packet_version >= 20180620) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180620();
			}
		} else if (packet_version >= 20180605) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180605();
			}
		} else if (packet_version >= 20180530) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180530();
			}
		} else if (packet_version >= 20180523) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180523();
			}
		} else if (packet_version >= 20180516) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180516();
			}
		} else if (packet_version >= 20180509) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180509();
			}
		} else if (packet_version >= 20180502) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180502();
			}
		} else if (packet_version >= 20180425) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180425();
			}
		} else if (packet_version >= 20180418) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180418();
			}
		} else if (packet_version >= 20180404) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180404();
			}
		} else if (packet_version >= 20180328) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180328();
			}
		} else if (packet_version >= 20180321) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180321();
			}
		} else if (packet_version >= 20180315) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180315();
			}
		} else if (packet_version >= 20180314) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180314();
			}
		} else if (packet_version >= 20180309) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180309();
			}
		} else if (packet_version >= 20180307) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180307();
			}
		} else if (packet_version >= 20180221) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180221();
			}
		} else if (packet_version >= 20180213) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180213();
			}
		} else if (packet_version >= 20180207) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180207();
			}
		} else if (packet_version >= 20180131) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180131();
			}
		} else if (packet_version >= 20180124) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180124();
			}
		} else if (packet_version >= 20180117) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180117();
			}
		} else if (packet_version >= 20180103) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180103();
			}
		} else if (packet_version >= 20171227) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171227();
			}
		} else if (packet_version >= 20171220) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171220();
			}
		} else if (packet_version >= 20171213) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171213();
			}
		} else if (packet_version >= 20171206) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171206();
			}
		}

		return true;
	}

	/* Ragexe Base Packets */
	void initialize_packet_length_db_Ragexe();
	/* 20171206 Ragexe */
	void initialize_packet_length_db_Ragexe_20171206();
	/* 20171213 Ragexe */
	void initialize_packet_length_db_Ragexe_20171213();
	/* 20171220 Ragexe */
	void initialize_packet_length_db_Ragexe_20171220();
	/* 20171227 Ragexe */
	void initialize_packet_length_db_Ragexe_20171227();
	/* 20180103 Ragexe */
	void initialize_packet_length_db_Ragexe_20180103();
	/* 20180117 Ragexe */
	void initialize_packet_length_db_Ragexe_20180117();
	/* 20180124 Ragexe */
	void initialize_packet_length_db_Ragexe_20180124();
	/* 20180131 Ragexe */
	void initialize_packet_length_db_Ragexe_20180131();
	/* 20180207 Ragexe */
	void initialize_packet_length_db_Ragexe_20180207();
	/* 20180213 Ragexe */
	void initialize_packet_length_db_Ragexe_20180213();
	/* 20180221 Ragexe */
	void initialize_packet_length_db_Ragexe_20180221();
	/* 20180307 Ragexe */
	void initialize_packet_length_db_Ragexe_20180307();
	/* 20180309 Ragexe */
	void initialize_packet_length_db_Ragexe_20180309();
	/* 20180314 Ragexe */
	void initialize_packet_length_db_Ragexe_20180314();
	/* 20180315 Ragexe */
	void initialize_packet_length_db_Ragexe_20180315();
	/* 20180321 Ragexe */
	void initialize_packet_length_db_Ragexe_20180321();
	/* 20180328 Ragexe */
	void initialize_packet_length_db_Ragexe_20180328();
	/* 20180404 Ragexe */
	void initialize_packet_length_db_Ragexe_20180404();
	/* 20180418 Ragexe */
	void initialize_packet_length_db_Ragexe_20180418();
	/* 20180425 Ragexe */
	void initialize_packet_length_db_Ragexe_20180425();
	/* 20180502 Ragexe */
	void initialize_packet_length_db_Ragexe_20180502();
	/* 20180509 Ragexe */
	void initialize_packet_length_db_Ragexe_20180509();
	/* 20180516 Ragexe */
	void initialize_packet_length_db_Ragexe_20180516();
	/* 20180523 Ragexe */
	void initialize_packet_length_db_Ragexe_20180523();
	/* 20180530 Ragexe */
	void initialize_packet_length_db_Ragexe_20180530();
	/* 20180605 Ragexe */
	void initialize_packet_length_db_Ragexe_20180605();
	/* 20180620 Ragexe */
	void initialize_packet_length_db_Ragexe_20180620();
	/* 20180621 Ragexe */
	void initialize_packet_length_db_Ragexe_20180621();
	/* 20180704 Ragexe */
	void initialize_packet_length_db_Ragexe_20180704();
	/* 20180718 Ragexe */
	void initialize_packet_length_db_Ragexe_20180718();
	/* 20180801 Ragexe */
	void initialize_packet_length_db_Ragexe_20180801();
	/* 20180808 Ragexe */
	void initialize_packet_length_db_Ragexe_20180808();
	/* 20180822 Ragexe */
	void initialize_packet_length_db_Ragexe_20180822();
	/* 20180829 Ragexe */
	void initialize_packet_length_db_Ragexe_20180829();
	/* 20180831 Ragexe */
	void initialize_packet_length_db_Ragexe_20180831();
	/* 20180912 Ragexe */
	void initialize_packet_length_db_Ragexe_20180912();
	/* 20180919 Ragexe */
	void initialize_packet_length_db_Ragexe_20180919();
	/* 20181002 Ragexe */
	void initialize_packet_length_db_Ragexe_20181002();
	/* 20181017 Ragexe */
	void initialize_packet_length_db_Ragexe_20181017();
	/* 20181024 Ragexe */
	void initialize_packet_length_db_Ragexe_20181024();
	/* 20181031 Ragexe */
	void initialize_packet_length_db_Ragexe_20181031();
	/* 20181107 Ragexe */
	void initialize_packet_length_db_Ragexe_20181107();
	/* 20181114 Ragexe */
	void initialize_packet_length_db_Ragexe_20181114();
	/* 20181121 Ragexe */
	void initialize_packet_length_db_Ragexe_20181121();
	/* 20181128 Ragexe */
	void initialize_packet_length_db_Ragexe_20181128();
	/* 20181205 Ragexe */
	void initialize_packet_length_db_Ragexe_20181205();
	/* 20181212 Ragexe */
	void initialize_packet_length_db_Ragexe_20181212();
	/* 20181219 Ragexe */
	void initialize_packet_length_db_Ragexe_20181219();
	/* 20181226 Ragexe */
	void initialize_packet_length_db_Ragexe_20181226();
	/* 20190109 Ragexe */
	void initialize_packet_length_db_Ragexe_20190109();
	/* 20190116 Ragexe */
	void initialize_packet_length_db_Ragexe_20190116();
	/* 20190123 Ragexe */
	void initialize_packet_length_db_Ragexe_20190123();

};
}
}
#define ClientSocktMgr Horizon::Zone::ClientSocketMgr::getInstance()
#define GET_ZONE_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)
#endif /* HORIZON_ZONE_CLIENTSOCKETMGR_HPP */
