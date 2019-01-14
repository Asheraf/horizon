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

#include "Server/Zone/Interface/InterAPI.hpp"
#include "Server/Zone/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Zone/SocketMgr/InterSocketMgr.hpp"
#include "Server/Zone/Game/Map/MapManager.hpp"
#include "Server/Zone/Session/ZoneSession.hpp" // required by clientmgr for update()
#include "Server/Zone/Game/Models/Entities/Unit/Player/Player.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <libconfig.h++>

using namespace std;
using boost::asio::ip::udp;

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

	/**
	 * Inter Server Settings
	 * @brief Definitions of the Inter-server networking configuration.
	 */
	const libconfig::Setting &inter_server = cfg.getRoot()["inter_server"];

	if (!inter_server.lookupValue("ip_address", tmp_string)) {
		zone_config_error("inter_server.ip_address", "127.0.0.1");
		network_conf().set_inter_server_ip("127.0.0.1");
	} else {
		network_conf().set_inter_server_ip(tmp_string);
	}

	if (!inter_server.lookupValue("port", tmp_value)) {
		zone_config_error("inter_server.port", 9998);
		network_conf().set_inter_server_port(9998);
	} else {
		network_conf().set_inter_server_port(tmp_value);
	}

	if (!inter_server.lookupValue("password", tmp_string)) {
		zone_config_error("inter_server.password", "ABCDEF");
		network_conf().set_inter_server_password(tmp_string);
	} else {
		network_conf().set_inter_server_password(tmp_string);
	}

	ZoneLog->info("Outbound connections: Inter-Server configured to tcp://{}:{} {}",
				  network_conf().get_inter_server_ip(), network_conf().get_inter_server_port(),
				  (network_conf().get_inter_server_password().length()) ? "using password" : "not using password");

	if (cfg.lookupValue("static_db_path", tmp_string))
		get_zone_config().set_database_path(tmp_string);

	ZoneLog->info("Static database path set to '{}'", get_zone_config().get_database_path());

	if (cfg.lookupValue("map_cache_file_name", tmp_string))
		get_zone_config().set_mapcache_file_name(tmp_string);

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

	for (auto &p : _player_map)
		p.second.lock()->update(diff);
	
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
	 * Establish a connection to the inter-server.
	 */
	if (!general_conf().is_test_run())
		establish_inter_connection();

	/**
	 * Map Manager.
	 */
	MapMgr->initialize();
	
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

		std::chrono::time_point<std::chrono::system_clock> start_t = std::chrono::system_clock::now();
		update(diff);
		std::chrono::time_point<std::chrono::system_clock> end_t = std::chrono::system_clock::now();
		//printf("cycle time - %dμs\n", (int) std::chrono::duration_cast<std::chrono::microseconds>(end_t - start_t).count());

		std::this_thread::sleep_for(std::chrono::microseconds(diff));
	}

	/**
	 * Server shutdown routine begins here...
	 */
	Server::finalize_core();

	/**
	 * Stop all networks
	 */
	ClientSocktMgr->stop_network();
	InterSocktMgr->stop_network();

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
 * Create connection-pool of Inter-server connections.
 */
void Horizon::Zone::ZoneMain::establish_inter_connection()
{
	if (InterSocktMgr->start(INTER_SESSION_NAME, this,
		network_conf().get_inter_server_ip(), network_conf().get_inter_server_port(), 1))
	{
		ZoneInterAPI->set_inter_socket(InterSocktMgr->get_connector_socket(INTER_SESSION_NAME));
		_task_scheduler.Schedule(Seconds(12),
			 [this] (TaskContext inter_ping) {
				 if (!ZoneInterAPI->pingInterServer()) {
					 InterSocktMgr->close_connection(INTER_SESSION_NAME);
					 establish_inter_connection();
					 return;
				 }

				 if (!is_shutting_down())
					 inter_ping.Repeat();
			 });
	}
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
