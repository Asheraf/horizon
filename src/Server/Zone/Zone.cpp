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

#include "Zone.hpp"

#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Session/ZoneSession.hpp" // required by clientmgr for update()
#include "Server/Zone/Game/Entities/Unit/Player/Player.hpp"
#include "Server/Zone/Game/StaticDB/StaticDB.hpp"
#include "Server/Zone/Game/Script/ScriptMgr.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <libconfig.h++>

using namespace std;
using boost::asio::ip::udp;
using namespace Horizon::Zone::Game;

/**
 * Zone Main server constructor.
 */
Horizon::Zone::ZoneMain::ZoneMain() : Server("Zone", "config/", "zone-server.conf")
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
	libconfig::Config cfg;
	std::string tmp_string;
	int tmp_value;
	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(file_path.c_str());
	} catch(const libconfig::FileIOException &fioex) {
		ZoneLog->error("I/O error while reading file '{}'.", file_path);
		return false;
	} catch(const libconfig::ParseException &pex) {
		ZoneLog->error("Parse error at {}:{} - {}", pex.getFile(), pex.getLine(), pex.getError());
		return false;
	}

	if (cfg.lookupValue("static_db_path", tmp_string))
		get_zone_config().set_database_path(tmp_string);

	ZoneLog->info("Static database path set to '{}'", get_zone_config().get_database_path());

	if (cfg.lookupValue("map_cache_file_name", tmp_string))
		get_zone_config().set_mapcache_file_name(tmp_string);

	if (cfg.lookupValue("map_containers", tmp_value) || tmp_value < 1) {
		get_zone_config().set_map_container_count(tmp_value);
	} else {
		ZoneLog->warn("Invalid value or no configuration found for 'map_containers', defaulting to 1.");
		get_zone_config().set_map_container_count(1);
	}

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(cfg))
		return false;

	ZoneLog->info("Done reading {} configurations in '{}'.", cfg.getRoot().getLength(), file_path);

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

	/**
	 * Process map-related updates.
	 */
	//MapMgr->update(diff);
}

/**
 * Signal Handler for the Zone-Server main thread.
 * @param error
 */
void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error) {
		ZoneServer->shutdown(SIGINT);
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
	 * Script Manager
	 */
	ScriptMgr->initialize();
	
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

	while (!is_shutting_down() && !general_conf().is_test_run()) {
		uint32_t diff = general_conf().get_core_update_interval();

		update(diff);

		std::this_thread::sleep_for(std::chrono::microseconds(diff));
	}
	/**
	 * Cancel all pending tasks.
	 */
	_task_scheduler.CancelAll();

	/**
	 * Server shutdown routine begins here...
	 */
	Server::finalize_core();

	/**
	 * Stop all networks
	 */
	ClientSocktMgr->stop_network();

	/**
	 * Unmanage globally managed sockets.
	 */
	ClientSocktMgr->unmanage_sockets();

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
