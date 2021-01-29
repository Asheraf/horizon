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
#include "Server/Zone/Game/StaticDB/ExpDB.hpp"
#include "Server/Zone/Game/StaticDB/JobDB.hpp"
#include "Server/Zone/Game/StaticDB/ItemDB.hpp"

#include <iostream>
#include <boost/make_shared.hpp>
#include <chrono>
#include <signal.h>

#include <sol.hpp>

using namespace std;
using namespace Horizon::Zone;

/**
 * Zone Main server constructor.
 */
ZoneServer::ZoneServer()
: Server(), _update_timer(_io_service)
{
}

/**
 * Zone Main server destructor.
 */
ZoneServer::~ZoneServer()
{
}

#define zone_config_error(setting_name, default) \
	HLog(error) << "No setting for '" << setting_name << "' in configuration file, defaulting to '" << default << "'.";

/**
 * Read /config/zone-server.yaml
 * @return false on failure, true on success.
 */
bool ZoneServer::read_config()
{
	using namespace std::chrono;

	sol::state lua;
	std::string file_path = general_conf().get_config_file_path().string();

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
	} catch(const std::exception &e) {
		HLog(error) << "ZoneMain::ReadConfig: " << e.what() << ".";
		return false;
	}

	sol::table tbl = lua["horizon_config"];

	zone_config().set_static_db_path(tbl.get_or("static_db_path", std::string("db/")));
	HLog(info) << "Static database path set to " << zone_config().get_static_db_path() << "";

	zone_config().set_mapcache_path(tbl.get_or("map_cache_file_path", std::string("db/maps.dat")));
	HLog(info) << "Mapcache file name is set to " << zone_config().get_mapcache_path() << ", it will be read while initializing maps.";

//	zone_config().set_entity_save_interval(tbl.get_or("entity_save_interval", 180000));
//	HLog(info) << "Entity data will be saved to the database every " << duration_cast<minutes>(std::chrono::milliseconds(zone_config().get_entity_save_interval())).count() << " minutes and " << duration_cast<seconds>(std::chrono::milliseconds(zone_config().get_entity_save_interval())).count() << " seconds.";
	
	HLog(info) << "Maps will be managed by '" << MAX_MAP_CONTAINER_THREADS << "' thread containers.";

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	HLog(info) << "Done reading server configurations from '" << file_path << "'.";

	return true;
}

void ZoneServer::update(uint64_t diff)
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
	
	if (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		_update_timer.expires_from_now(boost::posix_time::milliseconds(MAX_CORE_UPDATE_INTERVAL));
		_update_timer.async_wait(std::bind(&ZoneServer::update, this, MAX_CORE_UPDATE_INTERVAL));
	} else {
		get_io_service().stop();
	}
}

/**
 * Signal Handler for the Zone-Server main thread.
 * @param error
 */
void SignalHandler(int signal)
{
	if (signal == SIGINT || signal == SIGTERM || signal == SIGQUIT) {
		sZone->set_shutdown_stage(SHUTDOWN_INITIATED);
		sZone->set_shutdown_signal(signal);
	}
}

void ZoneServer::initialize_core()
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
						  general_conf().get_listen_ip(),
						  general_conf().get_listen_port(),
						  MAX_NETWORK_THREADS);

	Server::initialize_core();
	
	_update_timer.expires_from_now(boost::posix_time::milliseconds(MAX_CORE_UPDATE_INTERVAL));
	_update_timer.async_wait(std::bind(&ZoneServer::update, this, MAX_CORE_UPDATE_INTERVAL));
	
	get_io_service().run();

	HLog(info) << "Server shutdown initiated ...";
	
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
void ZoneServer::initialize_cli_commands()
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
		sZone->parse_exec_args(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Zoneacter Server.
	 */
	if (!sZone->read_config())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Initialize the Common Core
	 */
	sZone->initialize_core();

	/*
	 * Core Cleanup
	 */
	HLog(info) << "Server shutting down...";

	return sZone->general_conf().get_shutdown_signal();
}
