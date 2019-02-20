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

#include "Zone.hpp"

#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Session/ZoneSession.hpp" // required by clientmgr for update()
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/StaticDB.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <sol.hpp>

using namespace std;
using boost::asio::ip::udp;
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
	ZoneLog->error("No setting for '{}' in configuration file, defaulting to '{}'.", setting_name, default);

/**
 * Read /config/zone-server.yaml
 * @return false on failure, true on success.
 */
bool Horizon::Zone::ZoneMain::ReadConfig()
{
	sol::state lua;
	int tmp_value;
	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
	} catch(const std::exception &e) {
		ZoneLog->error("ZoneMain::ReadConfig: {}.", e.what());
		return false;
	}

	sol::table tbl = lua["server_config"];
	
	get_zone_config().set_database_path(tbl.get_or("static_db_path", std::string("db/")));
	ZoneLog->info("Static database path set to '{}'", get_zone_config().get_database_path());

	get_zone_config().set_mapcache_file_name(tbl.get_or("map_cache_file_name", std::string("maps.dat")));
	ZoneLog->info("Mapcache file name is set to '{}', it will be read while initializing maps.");

	get_zone_config().set_map_container_count(tbl.get_or("map_containers", 1));
	ZoneLog->warn("Maps will be divided into '{}' thread containers.", get_zone_config().get_map_container_count());

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	ZoneLog->info("Done reading server configurations from '{}'.", file_path);

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
void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error) {
		ZoneServer->set_shutdown_stage(SHUTDOWN_INITIATED);
		ZoneServer->set_shutdown_signal(SIGINT);
	}
}

void Horizon::Zone::ZoneMain::initialize_core()
{
	/**
	 * Map Manager.
	 */
	MapMgr->initialize();

	/**
	 * Static Databases
	 */
	StaticDB->load_all();
	
	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(SignalHandler);
	
	// Start Network
	ClientSocktMgr->start(get_io_service(),
						  network_conf().get_listen_ip(),
						  network_conf().get_listen_port(),
						  network_conf().get_network_thread_count());

	Server::initialize_core();

	while (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		uint32_t diff = general_conf().get_core_update_interval();
		update(diff);
		std::this_thread::sleep_for(std::chrono::microseconds(diff));
	}

	/**
	 * Server shutdown routine begins here...
	 */
	_task_scheduler.CancelAll();
	ClientSocktMgr->stop_network();
	Server::finalize_core();

	/* Cancel signal handling. */
	signals.cancel();
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
	ZoneLog->info("Server shutting down...");

	return ZoneServer->general_conf().get_shutdown_signal();
}
