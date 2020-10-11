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

#include "Zone.hpp"

#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Session/ZoneSession.hpp" // required by clientmgr for update()
#include "Server/Zone/Game/Entities/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"

#include <iostream>
#include <boost/make_shared.hpp>
#include <chrono>
#include <signal.h>

#if (((defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))) || defined(_MSC_VER)) \
	&& !defined(SOL_EXCEPTIONS_SAFE_PROPAGATION))
#define SOL_EXCEPTIONS_SAFE_PROPAGATION
#endif

#include <sol.hpp>

using namespace std;
using namespace Horizon::Zone::Game;

/**
 * Zone Main server constructor.
 */
Horizon::Zone::ZoneMain::ZoneMain() : Server("Zone", "config/", "zone-server.lua")
{
}

/**
 * Zone Main server destructor.
 */
Horizon::Zone::ZoneMain::~ZoneMain()
{
}

#define zone_config_error(setting_name, default) \
	CoreLog(error) <<"No setting for '{}' in configuration file, defaulting to '{}'.", setting_name, default);

/**
 * Read /config/zone-server.yaml
 * @return false on failure, true on success.
 */
bool Horizon::Zone::ZoneMain::ReadConfig()
{
	using namespace std::chrono;

	sol::state lua;
	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
	} catch(const std::exception &e) {
		CoreLog(error) <<"ZoneMain::ReadConfig: {}.", e.what());
		return false;
	}

	sol::table tbl = lua["server_config"];

	get_zone_config().set_database_path(tbl.get_or("static_db_path", std::string("db/")));
	CoreLog(info) <<"[Config] Static database path set to '{}'", get_zone_config().get_database_path());

	get_zone_config().set_mapcache_file_name(tbl.get_or("map_cache_file_name", std::string("maps.dat")));
	CoreLog(info) <<"[Config] Mapcache file name is set to '{}', it will be read while initializing maps.");

	get_zone_config().set_map_container_count(tbl.get_or("map_containers", 1));
	CoreLog(warn) <<"[Config] Maps will be divided into '{}' thread containers.", get_zone_config().get_map_container_count());

	get_zone_config().set_entity_save_interval(tbl.get_or("entity_save_interval", 180000));
	CoreLog(info) <<"[Config] Entity data will be saved to the database every {} minutes and {} seconds.",
				  duration_cast<minutes>(std::chrono::milliseconds(get_zone_config().get_entity_save_interval())).count(),
				  duration_cast<seconds>(std::chrono::milliseconds(get_zone_config().get_entity_save_interval())).count());

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	CoreLog(info) <<"Done reading server configurations from '{}'.", file_path);

	return true;
}

void Horizon::Zone::ZoneMain::update(uint32_t diff)
{
	process_cli_commands();

	/**
	 * Task Scheduler Update.
	 */
	_task_scheduler.Update();

	/**
	 * Process Packets.
	 */
	ClientSocktMgr->update_socket_sessions(diff);
}

/**
 * Signal Handler for the Zone-Server main thread.
 * @param error
 */
void SignalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT) {
		ZoneServer->set_shutdown_stage(SHUTDOWN_INITIATED);
		ZoneServer->set_shutdown_signal(signal);
	}
}

void Horizon::Zone::ZoneMain::initialize_core()
{
	// Install a signal handler
	signal(SIGINT, SignalHandler);
	signal(SIGQUIT, SignalHandler);
	signal(SIGTERM, SignalHandler);
	
	/**
	 * Map Manager.
	 */
	MapMgr->initialize();

	/**
	 * Static Databases
	 */
	ExpDB->load();
	ExpDB->load_status_point_table();
	JobDB->load();
	ItemDB->load();
	ItemDB->load_refine_db();
	ItemDB->load_weapon_target_size_modifiers_db();
	ItemDB->load_weapon_attribute_modifiers_db();

	// Start Network
	ClientSocktMgr->start(get_io_service(),
						  network_conf().get_listen_ip(),
						  network_conf().get_listen_port(),
						  network_conf().get_network_thread_count());

	Server::initialize_core();
	uint32_t diff = general_conf().get_core_update_interval();

	while (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		update(diff);
		std::this_thread::sleep_for(std::chrono::microseconds(diff));
	}

	MapMgr->finalize();

	/**
	 * Server shutdown routine begins here...
	 */
	_task_scheduler.CancelAll();
	ClientSocktMgr->stop_network();
	Server::finalize_core();
}

/**
 * Initialize Zone-Server CLI Commands.
 */
void Horizon::Zone::ZoneMain::initialize_cli_commands()
{
	Server::initialize_cli_commands();
}

/**
 * Zone Server Main runtime entrypoint.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	if (argc > 1)
		ZoneServer->parse_exec_args(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Zoneacter Server.
	 */
	if (!ZoneServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Initialize the Common Core
	 */
	ZoneServer->initialize_core();

	/*
	 * Core Cleanup
	 */
	CoreLog(info) <<"Server shutting down...");

	return ZoneServer->general_conf().get_shutdown_signal();
}
