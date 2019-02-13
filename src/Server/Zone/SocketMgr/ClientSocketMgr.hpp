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
			
		client_types type = ZoneServer->general_conf().get_client_type();
		uint32_t packet_version = ZoneServer->general_conf().get_packet_version();

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

		if (packet_version >= 20190130) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20190130();
			}
		} else if (packet_version >= 20190123) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20190123();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20190123();
			}
		} else if (packet_version >= 20190117) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20190117();
			}
		} else if (packet_version >= 20190116) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20190116();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20190116();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20190116();
			}
		} else if (packet_version >= 20190109) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20190109();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20190109();
			}
		} else if (packet_version >= 20181226) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181226();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181226();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181226();
			}
		} else if (packet_version >= 20181219) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181219();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181219();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181219();
			}
		} else if (packet_version >= 20181212) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181212();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181212();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181212();
			}
		} else if (packet_version >= 20181205) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181205();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181205();
			}
		} else if (packet_version >= 20181128) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181128();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181128();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181128();
			}
		} else if (packet_version >= 20181121) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181121();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181121();
			}
		} else if (packet_version >= 20181120) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181120();
			}
		} else if (packet_version >= 20181114) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181114();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181114();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181114();
			}
		} else if (packet_version >= 20181107) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181107();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181107();
			}
		} else if (packet_version >= 20181031) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181031();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181031();
			}
		} else if (packet_version >= 20181024) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181024();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181024();
			}
		} else if (packet_version >= 20181017) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181017();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181017();
			}
		} else if (packet_version >= 20181010) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20181010();
			}
		} else if (packet_version >= 20181002) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20181002();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20181002();
			}
		} else if (packet_version >= 20180928) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180928();
			}
		} else if (packet_version >= 20180919) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180919();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180919();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180919();
			}
		} else if (packet_version >= 20180912) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180912();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180912();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180912();
			}
		} else if (packet_version >= 20180905) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180905();
			}
		} else if (packet_version >= 20180831) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180831();
			}
		} else if (packet_version >= 20180829) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180829();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180829();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180829();
			}
		} else if (packet_version >= 20180822) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180822();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180822();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180822();
			}
		} else if (packet_version >= 20180808) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180808();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180808();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180808();
			}
		} else if (packet_version >= 20180801) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180801();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180801();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180801();
			}
		} else if (packet_version >= 20180725) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180725();
			}
		} else if (packet_version >= 20180718) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180718();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180718();
			}
		} else if (packet_version >= 20180711) {
			if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180711();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180711();
			}
		} else if (packet_version >= 20180704) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180704();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180704();
			}
		} else if (packet_version >= 20180703) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180703();
			}
		} else if (packet_version >= 20180627) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180627();
			}
		} else if (packet_version >= 20180621) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180621();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180621();
			}
		} else if (packet_version >= 20180620) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180620();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180620();
			}
		} else if (packet_version >= 20180612) {
			if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180612();
			}
		} else if (packet_version >= 20180605) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180605();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180605();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180605();
			}
		} else if (packet_version >= 20180530) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180530();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180530();
			}
		} else if (packet_version >= 20180523) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180523();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180523();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180523();
			}
		} else if (packet_version >= 20180516) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180516();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180516();
			}
		} else if (packet_version >= 20180511) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180511();
			}
		} else if (packet_version >= 20180509) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180509();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180509();
			}
		} else if (packet_version >= 20180502) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180502();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180502();
			}
		} else if (packet_version >= 20180425) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180425();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180425();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180425();
			}
		} else if (packet_version >= 20180418) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180418();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180418();
			}
		} else if (packet_version >= 20180411) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180411();
			}
		} else if (packet_version >= 20180404) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180404();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180404();
			}
		} else if (packet_version >= 20180328) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180328();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180328();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180328();
			}
		} else if (packet_version >= 20180321) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180321();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180321();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180321();
			}
		} else if (packet_version >= 20180315) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180315();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180315();
			}
		} else if (packet_version >= 20180314) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180314();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180314();
			}
		} else if (packet_version >= 20180309) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180309();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180309();
			}
		} else if (packet_version >= 20180307) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180307();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180307();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180307();
			}
		} else if (packet_version >= 20180228) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180228();
			}
		} else if (packet_version >= 20180221) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180221();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180221();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180221();
			}
		} else if (packet_version >= 20180213) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180213();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180213();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180213();
			}
		} else if (packet_version >= 20180207) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180207();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180207();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180207();
			}
		} else if (packet_version >= 20180131) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180131();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20180131();
			}
		} else if (packet_version >= 20180124) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20180124();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20180124();
			}
		} else if (packet_version >= 20180117) {
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
		} else if (packet_version >= 20171229) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171229();
			}
		} else if (packet_version >= 20171227) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171227();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171227();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171227();
			}
		} else if (packet_version >= 20171221) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171221();
			}
		} else if (packet_version >= 20171220) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171220();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171220();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171220();
			}
		} else if (packet_version >= 20171214) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171214();
			}
		} else if (packet_version >= 20171213) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171213();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171213();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171213();
			}
		} else if (packet_version >= 20171212) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171212();
			}
		} else if (packet_version >= 20171211) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171211();
			}
		} else if (packet_version >= 20171210) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171210();
			}
		} else if (packet_version >= 20171209) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171209();
			}
		} else if (packet_version >= 20171208) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171208();
			}
		} else if (packet_version >= 20171206) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171206();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171206();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171206();
			}
		} else if (packet_version >= 20171204) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171204();
			}
		} else if (packet_version >= 20171130) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171130();
			}
		} else if (packet_version >= 20171129) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171129();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171129();
			}
		} else if (packet_version >= 20171128) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171128();
			}
		} else if (packet_version >= 20171127) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171127();
			}
		} else if (packet_version >= 20171123) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171123();
			}
		} else if (packet_version >= 20171122) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171122();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171122();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171122();
			}
		} else if (packet_version >= 20171121) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171121();
			}
		} else if (packet_version >= 20171117) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171117();
			}
		} else if (packet_version >= 20171116) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171116();
			}
		} else if (packet_version >= 20171115) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171115();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171115();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171115();
			}
		} else if (packet_version >= 20171113) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171113();
			}
		} else if (packet_version >= 20171109) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171109();
			}
		} else if (packet_version >= 20171108) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171108();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171108();
			}
		} else if (packet_version >= 20171101) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171101();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171101();
			}
		} else if (packet_version >= 20171031) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171031();
			}
		} else if (packet_version >= 20171030) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171030();
			}
		} else if (packet_version >= 20171027) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171027();
			}
		} else if (packet_version >= 20171025) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171025();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171025();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171025();
			}
		} else if (packet_version >= 20171024) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171024();
			}
		} else if (packet_version >= 20171023) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171023();
			}
		} else if (packet_version >= 20171019) {
			if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171019();
			}
		} else if (packet_version >= 20171018) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171018();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171018();
			} else if (type == CLIENT_TYPE_ZERO) {
				initialize_packet_length_db_Zero_20171018();
			}
		} else if (packet_version >= 20171011) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171011();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171011();
			}
		} else if (packet_version >= 20171002) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20171002();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20171002();
			}
		} else if (packet_version >= 20170927) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170927();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170927();
			}
		} else if (packet_version >= 20170920) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170920();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170920();
			}
		} else if (packet_version >= 20170913) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170913();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170913();
			}
		} else if (packet_version >= 20170906) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170906();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170906();
			}
		} else if (packet_version >= 20170830) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170830();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170830();
			}
		} else if (packet_version >= 20170823) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170823();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170823();
			}
		} else if (packet_version >= 20170816) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170816();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170816();
			}
		} else if (packet_version >= 20170809) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170809();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170809();
			}
		} else if (packet_version >= 20170801) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170801();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170801();
			}
		} else if (packet_version >= 20170726) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170726();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170726();
			}
		} else if (packet_version >= 20170719) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170719();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170719();
			}
		} else if (packet_version >= 20170712) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170712();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170712();
			}
		} else if (packet_version >= 20170705) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170705();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170705();
			}
		} else if (packet_version >= 20170628) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170628();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170628();
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
		} else if (packet_version >= 20170607) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170607();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170607();
			}
		} else if (packet_version >= 20170531) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170531();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170531();
			}
		} else if (packet_version >= 20170524) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170524();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170524();
			}
		} else if (packet_version >= 20170517) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170517();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170517();
			}
		} else if (packet_version >= 20170502) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170502();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170502();
			}
		} else if (packet_version >= 20170426) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170426();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170426();
			}
		} else if (packet_version >= 20170419) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170419();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170419();
			}
		} else if (packet_version >= 20170412) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170412();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170412();
			}
		} else if (packet_version >= 20170405) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170405();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170405();
			}
		} else if (packet_version >= 20170329) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170329();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170329();
			}
		} else if (packet_version >= 20170322) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170322();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170322();
			}
		} else if (packet_version >= 20170315) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170315();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170315();
			}
		} else if (packet_version >= 20170308) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170308();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170308();
			}
		} else if (packet_version >= 20170228) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170228();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170228();
			}
		} else if (packet_version >= 20170222) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170222();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170222();
			}
		} else if (packet_version >= 20170215) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170215();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170215();
			}
		} else if (packet_version >= 20170208) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170208();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170208();
			}
		} else if (packet_version >= 20170201) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170201();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170201();
			}
		} else if (packet_version >= 20170125) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170125();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170125();
			}
		} else if (packet_version >= 20170118) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170118();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170118();
			}
		} else if (packet_version >= 20170111) {
			if (type == CLIENT_TYPE_RAGEXE) {
				initialize_packet_length_db_Ragexe_20170111();
			} else if (type == CLIENT_TYPE_RAGEXE_RE) {
				initialize_packet_length_db_RE_20170111();
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
	/* 20170111 Ragexe */
	void initialize_packet_length_db_Ragexe_20170111();
	/* 20170111 RE */
	void initialize_packet_length_db_RE_20170111();
	/* 20170118 Ragexe */
	void initialize_packet_length_db_Ragexe_20170118();
	/* 20170118 RE */
	void initialize_packet_length_db_RE_20170118();
	/* 20170125 Ragexe */
	void initialize_packet_length_db_Ragexe_20170125();
	/* 20170125 RE */
	void initialize_packet_length_db_RE_20170125();
	/* 20170201 Ragexe */
	void initialize_packet_length_db_Ragexe_20170201();
	/* 20170201 RE */
	void initialize_packet_length_db_RE_20170201();
	/* 20170208 Ragexe */
	void initialize_packet_length_db_Ragexe_20170208();
	/* 20170208 RE */
	void initialize_packet_length_db_RE_20170208();
	/* 20170215 Ragexe */
	void initialize_packet_length_db_Ragexe_20170215();
	/* 20170215 RE */
	void initialize_packet_length_db_RE_20170215();
	/* 20170222 Ragexe */
	void initialize_packet_length_db_Ragexe_20170222();
	/* 20170222 RE */
	void initialize_packet_length_db_RE_20170222();
	/* 20170228 Ragexe */
	void initialize_packet_length_db_Ragexe_20170228();
	/* 20170228 RE */
	void initialize_packet_length_db_RE_20170228();
	/* 20170308 Ragexe */
	void initialize_packet_length_db_Ragexe_20170308();
	/* 20170308 RE */
	void initialize_packet_length_db_RE_20170308();
	/* 20170315 Ragexe */
	void initialize_packet_length_db_Ragexe_20170315();
	/* 20170315 RE */
	void initialize_packet_length_db_RE_20170315();
	/* 20170322 Ragexe */
	void initialize_packet_length_db_Ragexe_20170322();
	/* 20170322 RE */
	void initialize_packet_length_db_RE_20170322();
	/* 20170329 Ragexe */
	void initialize_packet_length_db_Ragexe_20170329();
	/* 20170329 RE */
	void initialize_packet_length_db_RE_20170329();
	/* 20170405 Ragexe */
	void initialize_packet_length_db_Ragexe_20170405();
	/* 20170405 RE */
	void initialize_packet_length_db_RE_20170405();
	/* 20170412 Ragexe */
	void initialize_packet_length_db_Ragexe_20170412();
	/* 20170412 RE */
	void initialize_packet_length_db_RE_20170412();
	/* 20170419 Ragexe */
	void initialize_packet_length_db_Ragexe_20170419();
	/* 20170419 RE */
	void initialize_packet_length_db_RE_20170419();
	/* 20170426 Ragexe */
	void initialize_packet_length_db_Ragexe_20170426();
	/* 20170426 RE */
	void initialize_packet_length_db_RE_20170426();
	/* 20170502 Ragexe */
	void initialize_packet_length_db_Ragexe_20170502();
	/* 20170502 RE */
	void initialize_packet_length_db_RE_20170502();
	/* 20170517 Ragexe */
	void initialize_packet_length_db_Ragexe_20170517();
	/* 20170517 RE */
	void initialize_packet_length_db_RE_20170517();
	/* 20170524 Ragexe */
	void initialize_packet_length_db_Ragexe_20170524();
	/* 20170524 RE */
	void initialize_packet_length_db_RE_20170524();
	/* 20170531 Ragexe */
	void initialize_packet_length_db_Ragexe_20170531();
	/* 20170531 RE */
	void initialize_packet_length_db_RE_20170531();
	/* 20170607 Ragexe */
	void initialize_packet_length_db_Ragexe_20170607();
	/* 20170607 RE */
	void initialize_packet_length_db_RE_20170607();
	/* 20170614 Ragexe */
	void initialize_packet_length_db_Ragexe_20170614();
	/* 20170614 RE */
	void initialize_packet_length_db_RE_20170614();
	/* 20170621 Ragexe */
	void initialize_packet_length_db_Ragexe_20170621();
	/* 20170621 RE */
	void initialize_packet_length_db_RE_20170621();
	/* 20170628 Ragexe */
	void initialize_packet_length_db_Ragexe_20170628();
	/* 20170628 RE */
	void initialize_packet_length_db_RE_20170628();
	/* 20170705 Ragexe */
	void initialize_packet_length_db_Ragexe_20170705();
	/* 20170705 RE */
	void initialize_packet_length_db_RE_20170705();
	/* 20170712 Ragexe */
	void initialize_packet_length_db_Ragexe_20170712();
	/* 20170712 RE */
	void initialize_packet_length_db_RE_20170712();
	/* 20170719 Ragexe */
	void initialize_packet_length_db_Ragexe_20170719();
	/* 20170719 RE */
	void initialize_packet_length_db_RE_20170719();
	/* 20170726 Ragexe */
	void initialize_packet_length_db_Ragexe_20170726();
	/* 20170726 RE */
	void initialize_packet_length_db_RE_20170726();
	/* 20170801 Ragexe */
	void initialize_packet_length_db_Ragexe_20170801();
	/* 20170801 RE */
	void initialize_packet_length_db_RE_20170801();
	/* 20170809 Ragexe */
	void initialize_packet_length_db_Ragexe_20170809();
	/* 20170809 RE */
	void initialize_packet_length_db_RE_20170809();
	/* 20170816 Ragexe */
	void initialize_packet_length_db_Ragexe_20170816();
	/* 20170816 RE */
	void initialize_packet_length_db_RE_20170816();
	/* 20170823 Ragexe */
	void initialize_packet_length_db_Ragexe_20170823();
	/* 20170823 RE */
	void initialize_packet_length_db_RE_20170823();
	/* 20170830 Ragexe */
	void initialize_packet_length_db_Ragexe_20170830();
	/* 20170830 RE */
	void initialize_packet_length_db_RE_20170830();
	/* 20170906 Ragexe */
	void initialize_packet_length_db_Ragexe_20170906();
	/* 20170906 RE */
	void initialize_packet_length_db_RE_20170906();
	/* 20170913 Ragexe */
	void initialize_packet_length_db_Ragexe_20170913();
	/* 20170913 RE */
	void initialize_packet_length_db_RE_20170913();
	/* 20170920 Ragexe */
	void initialize_packet_length_db_Ragexe_20170920();
	/* 20170920 RE */
	void initialize_packet_length_db_RE_20170920();
	/* 20170927 Ragexe */
	void initialize_packet_length_db_Ragexe_20170927();
	/* 20170927 RE */
	void initialize_packet_length_db_RE_20170927();
	/* 20171002 Ragexe */
	void initialize_packet_length_db_Ragexe_20171002();
	/* 20171002 RE */
	void initialize_packet_length_db_RE_20171002();
	/* 20171011 Ragexe */
	void initialize_packet_length_db_Ragexe_20171011();
	/* 20171011 RE */
	void initialize_packet_length_db_RE_20171011();
	/* 20171018 Ragexe */
	void initialize_packet_length_db_Ragexe_20171018();
	/* 20171018 RE */
	void initialize_packet_length_db_RE_20171018();
	/* 20171018 Zero */
	void initialize_packet_length_db_Zero_20171018();
	/* 20171019 Zero */
	void initialize_packet_length_db_Zero_20171019();
	/* 20171023 Zero */
	void initialize_packet_length_db_Zero_20171023();
	/* 20171024 Zero */
	void initialize_packet_length_db_Zero_20171024();
	/* 20171025 Ragexe */
	void initialize_packet_length_db_Ragexe_20171025();
	/* 20171025 RE */
	void initialize_packet_length_db_RE_20171025();
	/* 20171025 Zero */
	void initialize_packet_length_db_Zero_20171025();
	/* 20171027 Zero */
	void initialize_packet_length_db_Zero_20171027();
	/* 20171030 Zero */
	void initialize_packet_length_db_Zero_20171030();
	/* 20171031 Zero */
	void initialize_packet_length_db_Zero_20171031();
	/* 20171101 Ragexe */
	void initialize_packet_length_db_Ragexe_20171101();
	/* 20171101 RE */
	void initialize_packet_length_db_RE_20171101();
	/* 20171108 Ragexe */
	void initialize_packet_length_db_Ragexe_20171108();
	/* 20171108 RE */
	void initialize_packet_length_db_RE_20171108();
	/* 20171109 Zero */
	void initialize_packet_length_db_Zero_20171109();
	/* 20171113 Zero */
	void initialize_packet_length_db_Zero_20171113();
	/* 20171115 Ragexe */
	void initialize_packet_length_db_Ragexe_20171115();
	/* 20171115 RE */
	void initialize_packet_length_db_RE_20171115();
	/* 20171115 Zero */
	void initialize_packet_length_db_Zero_20171115();
	/* 20171116 Zero */
	void initialize_packet_length_db_Zero_20171116();
	/* 20171117 Zero */
	void initialize_packet_length_db_Zero_20171117();
	/* 20171121 Zero */
	void initialize_packet_length_db_Zero_20171121();
	/* 20171122 Ragexe */
	void initialize_packet_length_db_Ragexe_20171122();
	/* 20171122 RE */
	void initialize_packet_length_db_RE_20171122();
	/* 20171122 Zero */
	void initialize_packet_length_db_Zero_20171122();
	/* 20171123 Zero */
	void initialize_packet_length_db_Zero_20171123();
	/* 20171127 Zero */
	void initialize_packet_length_db_Zero_20171127();
	/* 20171128 Zero */
	void initialize_packet_length_db_Zero_20171128();
	/* 20171129 Ragexe */
	void initialize_packet_length_db_Ragexe_20171129();
	/* 20171129 RE */
	void initialize_packet_length_db_RE_20171129();
	/* 20171130 Zero */
	void initialize_packet_length_db_Zero_20171130();
	/* 20171204 Zero */
	void initialize_packet_length_db_Zero_20171204();
	/* 20171206 Ragexe */
	void initialize_packet_length_db_Ragexe_20171206();
	/* 20171206 RE */
	void initialize_packet_length_db_RE_20171206();
	/* 20171206 Zero */
	void initialize_packet_length_db_Zero_20171206();
	/* 20171208 Zero */
	void initialize_packet_length_db_Zero_20171208();
	/* 20171209 Zero */
	void initialize_packet_length_db_Zero_20171209();
	/* 20171210 Zero */
	void initialize_packet_length_db_Zero_20171210();
	/* 20171211 Zero */
	void initialize_packet_length_db_Zero_20171211();
	/* 20171212 Zero */
	void initialize_packet_length_db_Zero_20171212();
	/* 20171213 Ragexe */
	void initialize_packet_length_db_Ragexe_20171213();
	/* 20171213 RE */
	void initialize_packet_length_db_RE_20171213();
	/* 20171213 Zero */
	void initialize_packet_length_db_Zero_20171213();
	/* 20171214 Zero */
	void initialize_packet_length_db_Zero_20171214();
	/* 20171220 Ragexe */
	void initialize_packet_length_db_Ragexe_20171220();
	/* 20171220 RE */
	void initialize_packet_length_db_RE_20171220();
	/* 20171220 Zero */
	void initialize_packet_length_db_Zero_20171220();
	/* 20171221 Zero */
	void initialize_packet_length_db_Zero_20171221();
	/* 20171227 Ragexe */
	void initialize_packet_length_db_Ragexe_20171227();
	/* 20171227 RE */
	void initialize_packet_length_db_RE_20171227();
	/* 20171227 Zero */
	void initialize_packet_length_db_Zero_20171227();
	/* 20171229 Zero */
	void initialize_packet_length_db_Zero_20171229();
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
	/* 20180124 Ragexe */
	void initialize_packet_length_db_Ragexe_20180124();
	/* 20180124 RE */
	void initialize_packet_length_db_RE_20180124();
	/* 20180131 Ragexe */
	void initialize_packet_length_db_Ragexe_20180131();
	/* 20180131 Zero */
	void initialize_packet_length_db_Zero_20180131();
	/* 20180207 Ragexe */
	void initialize_packet_length_db_Ragexe_20180207();
	/* 20180207 RE */
	void initialize_packet_length_db_RE_20180207();
	/* 20180207 Zero */
	void initialize_packet_length_db_Zero_20180207();
	/* 20180213 Ragexe */
	void initialize_packet_length_db_Ragexe_20180213();
	/* 20180213 RE */
	void initialize_packet_length_db_RE_20180213();
	/* 20180213 Zero */
	void initialize_packet_length_db_Zero_20180213();
	/* 20180221 Ragexe */
	void initialize_packet_length_db_Ragexe_20180221();
	/* 20180221 RE */
	void initialize_packet_length_db_RE_20180221();
	/* 20180221 Zero */
	void initialize_packet_length_db_Zero_20180221();
	/* 20180228 Zero */
	void initialize_packet_length_db_Zero_20180228();
	/* 20180307 Ragexe */
	void initialize_packet_length_db_Ragexe_20180307();
	/* 20180307 RE */
	void initialize_packet_length_db_RE_20180307();
	/* 20180307 Zero */
	void initialize_packet_length_db_Zero_20180307();
	/* 20180309 Ragexe */
	void initialize_packet_length_db_Ragexe_20180309();
	/* 20180309 Zero */
	void initialize_packet_length_db_Zero_20180309();
	/* 20180314 Ragexe */
	void initialize_packet_length_db_Ragexe_20180314();
	/* 20180314 Zero */
	void initialize_packet_length_db_Zero_20180314();
	/* 20180315 Ragexe */
	void initialize_packet_length_db_Ragexe_20180315();
	/* 20180315 Zero */
	void initialize_packet_length_db_Zero_20180315();
	/* 20180321 Ragexe */
	void initialize_packet_length_db_Ragexe_20180321();
	/* 20180321 RE */
	void initialize_packet_length_db_RE_20180321();
	/* 20180321 Zero */
	void initialize_packet_length_db_Zero_20180321();
	/* 20180328 Ragexe */
	void initialize_packet_length_db_Ragexe_20180328();
	/* 20180328 RE */
	void initialize_packet_length_db_RE_20180328();
	/* 20180328 Zero */
	void initialize_packet_length_db_Zero_20180328();
	/* 20180404 Ragexe */
	void initialize_packet_length_db_Ragexe_20180404();
	/* 20180404 RE */
	void initialize_packet_length_db_RE_20180404();
	/* 20180411 Zero */
	void initialize_packet_length_db_Zero_20180411();
	/* 20180418 Ragexe */
	void initialize_packet_length_db_Ragexe_20180418();
	/* 20180418 RE */
	void initialize_packet_length_db_RE_20180418();
	/* 20180425 Ragexe */
	void initialize_packet_length_db_Ragexe_20180425();
	/* 20180425 RE */
	void initialize_packet_length_db_RE_20180425();
	/* 20180425 Zero */
	void initialize_packet_length_db_Zero_20180425();
	/* 20180502 Ragexe */
	void initialize_packet_length_db_Ragexe_20180502();
	/* 20180502 RE */
	void initialize_packet_length_db_RE_20180502();
	/* 20180509 Ragexe */
	void initialize_packet_length_db_Ragexe_20180509();
	/* 20180509 Zero */
	void initialize_packet_length_db_Zero_20180509();
	/* 20180511 Zero */
	void initialize_packet_length_db_Zero_20180511();
	/* 20180516 Ragexe */
	void initialize_packet_length_db_Ragexe_20180516();
	/* 20180516 RE */
	void initialize_packet_length_db_RE_20180516();
	/* 20180523 Ragexe */
	void initialize_packet_length_db_Ragexe_20180523();
	/* 20180523 RE */
	void initialize_packet_length_db_RE_20180523();
	/* 20180523 Zero */
	void initialize_packet_length_db_Zero_20180523();
	/* 20180530 Ragexe */
	void initialize_packet_length_db_Ragexe_20180530();
	/* 20180530 RE */
	void initialize_packet_length_db_RE_20180530();
	/* 20180605 Ragexe */
	void initialize_packet_length_db_Ragexe_20180605();
	/* 20180605 RE */
	void initialize_packet_length_db_RE_20180605();
	/* 20180605 Zero */
	void initialize_packet_length_db_Zero_20180605();
	/* 20180612 RE */
	void initialize_packet_length_db_RE_20180612();
	/* 20180620 Ragexe */
	void initialize_packet_length_db_Ragexe_20180620();
	/* 20180620 RE */
	void initialize_packet_length_db_RE_20180620();
	/* 20180621 Ragexe */
	void initialize_packet_length_db_Ragexe_20180621();
	/* 20180621 RE */
	void initialize_packet_length_db_RE_20180621();
	/* 20180627 Zero */
	void initialize_packet_length_db_Zero_20180627();
	/* 20180703 Zero */
	void initialize_packet_length_db_Zero_20180703();
	/* 20180704 Ragexe */
	void initialize_packet_length_db_Ragexe_20180704();
	/* 20180704 RE */
	void initialize_packet_length_db_RE_20180704();
	/* 20180711 RE */
	void initialize_packet_length_db_RE_20180711();
	/* 20180711 Zero */
	void initialize_packet_length_db_Zero_20180711();
	/* 20180718 Ragexe */
	void initialize_packet_length_db_Ragexe_20180718();
	/* 20180718 RE */
	void initialize_packet_length_db_RE_20180718();
	/* 20180725 Zero */
	void initialize_packet_length_db_Zero_20180725();
	/* 20180801 Ragexe */
	void initialize_packet_length_db_Ragexe_20180801();
	/* 20180801 RE */
	void initialize_packet_length_db_RE_20180801();
	/* 20180801 Zero */
	void initialize_packet_length_db_Zero_20180801();
	/* 20180808 Ragexe */
	void initialize_packet_length_db_Ragexe_20180808();
	/* 20180808 RE */
	void initialize_packet_length_db_RE_20180808();
	/* 20180808 Zero */
	void initialize_packet_length_db_Zero_20180808();
	/* 20180822 Ragexe */
	void initialize_packet_length_db_Ragexe_20180822();
	/* 20180822 RE */
	void initialize_packet_length_db_RE_20180822();
	/* 20180822 Zero */
	void initialize_packet_length_db_Zero_20180822();
	/* 20180829 Ragexe */
	void initialize_packet_length_db_Ragexe_20180829();
	/* 20180829 RE */
	void initialize_packet_length_db_RE_20180829();
	/* 20180829 Zero */
	void initialize_packet_length_db_Zero_20180829();
	/* 20180831 Ragexe */
	void initialize_packet_length_db_Ragexe_20180831();
	/* 20180905 Zero */
	void initialize_packet_length_db_Zero_20180905();
	/* 20180912 Ragexe */
	void initialize_packet_length_db_Ragexe_20180912();
	/* 20180912 RE */
	void initialize_packet_length_db_RE_20180912();
	/* 20180912 Zero */
	void initialize_packet_length_db_Zero_20180912();
	/* 20180919 Ragexe */
	void initialize_packet_length_db_Ragexe_20180919();
	/* 20180919 RE */
	void initialize_packet_length_db_RE_20180919();
	/* 20180919 Zero */
	void initialize_packet_length_db_Zero_20180919();
	/* 20180928 Zero */
	void initialize_packet_length_db_Zero_20180928();
	/* 20181002 Ragexe */
	void initialize_packet_length_db_Ragexe_20181002();
	/* 20181002 RE */
	void initialize_packet_length_db_RE_20181002();
	/* 20181010 Zero */
	void initialize_packet_length_db_Zero_20181010();
	/* 20181017 Ragexe */
	void initialize_packet_length_db_Ragexe_20181017();
	/* 20181017 RE */
	void initialize_packet_length_db_RE_20181017();
	/* 20181024 Ragexe */
	void initialize_packet_length_db_Ragexe_20181024();
	/* 20181024 Zero */
	void initialize_packet_length_db_Zero_20181024();
	/* 20181031 Ragexe */
	void initialize_packet_length_db_Ragexe_20181031();
	/* 20181031 RE */
	void initialize_packet_length_db_RE_20181031();
	/* 20181107 Ragexe */
	void initialize_packet_length_db_Ragexe_20181107();
	/* 20181107 RE */
	void initialize_packet_length_db_RE_20181107();
	/* 20181114 Ragexe */
	void initialize_packet_length_db_Ragexe_20181114();
	/* 20181114 RE */
	void initialize_packet_length_db_RE_20181114();
	/* 20181114 Zero */
	void initialize_packet_length_db_Zero_20181114();
	/* 20181120 Zero */
	void initialize_packet_length_db_Zero_20181120();
	/* 20181121 Ragexe */
	void initialize_packet_length_db_Ragexe_20181121();
	/* 20181121 RE */
	void initialize_packet_length_db_RE_20181121();
	/* 20181128 Ragexe */
	void initialize_packet_length_db_Ragexe_20181128();
	/* 20181128 RE */
	void initialize_packet_length_db_RE_20181128();
	/* 20181128 Zero */
	void initialize_packet_length_db_Zero_20181128();
	/* 20181205 Ragexe */
	void initialize_packet_length_db_Ragexe_20181205();
	/* 20181205 RE */
	void initialize_packet_length_db_RE_20181205();
	/* 20181212 Ragexe */
	void initialize_packet_length_db_Ragexe_20181212();
	/* 20181212 RE */
	void initialize_packet_length_db_RE_20181212();
	/* 20181212 Zero */
	void initialize_packet_length_db_Zero_20181212();
	/* 20181219 Ragexe */
	void initialize_packet_length_db_Ragexe_20181219();
	/* 20181219 RE */
	void initialize_packet_length_db_RE_20181219();
	/* 20181219 Zero */
	void initialize_packet_length_db_Zero_20181219();
	/* 20181226 Ragexe */
	void initialize_packet_length_db_Ragexe_20181226();
	/* 20181226 RE */
	void initialize_packet_length_db_RE_20181226();
	/* 20181226 Zero */
	void initialize_packet_length_db_Zero_20181226();
	/* 20190109 Ragexe */
	void initialize_packet_length_db_Ragexe_20190109();
	/* 20190109 RE */
	void initialize_packet_length_db_RE_20190109();
	/* 20190116 Ragexe */
	void initialize_packet_length_db_Ragexe_20190116();
	/* 20190116 RE */
	void initialize_packet_length_db_RE_20190116();
	/* 20190116 Zero */
	void initialize_packet_length_db_Zero_20190116();
	/* 20190117 Zero */
	void initialize_packet_length_db_Zero_20190117();
	/* 20190123 Ragexe */
	void initialize_packet_length_db_Ragexe_20190123();
	/* 20190123 RE */
	void initialize_packet_length_db_RE_20190123();
	/* 20190130 Zero */
	void initialize_packet_length_db_Zero_20190130();

};
}
}
#define ClientSocktMgr Horizon::Zone::ClientSocketMgr::getInstance()
#define GET_ZONE_PACKETLEN(id) ClientSocktMgr->get_packet_length(id)
#endif /* HORIZON_ZONE_CLIENTSOCKETMGR_HPP */
