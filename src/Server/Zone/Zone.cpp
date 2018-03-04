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
	std::string file_path = getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName();

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
		getNetworkConf().setInterServerIp("127.0.0.1");
	} else {
		getNetworkConf().setInterServerIp(tmp_string);
	}

	if (!inter_server.lookupValue("port", tmp_value)) {
		zone_config_error("inter_server.port", 9998);
		getNetworkConf().setInterServerPort(9998);
	} else {
		getNetworkConf().setInterServerPort(tmp_value);
	}

	if (!inter_server.lookupValue("password", tmp_string)) {
		zone_config_error("inter_server.password", "ABCDEF");
		getNetworkConf().setInterServerPassword(tmp_string);
	} else {
		getNetworkConf().setInterServerPassword(tmp_string);
	}

	ZoneLog->info("Outbound connections: Inter-Server configured to tcp://{}:{} {}",
				  getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(),
				  (getNetworkConf().getInterServerPassword().length()) ? "using password" : "not using password");

	if (cfg.lookupValue("static_db_path", tmp_string))
		getZoneConfig().setDatabasePath(tmp_string);

	ZoneLog->info("Static database path set to '{}'", getZoneConfig().getDatabasePath());

	if (cfg.lookupValue("map_cache_file_name", tmp_string))
		getZoneConfig().setMapCacheFileName(tmp_string);

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!ProcessCommonConfiguration(cfg))
		return false;

	ZoneLog->info("Done reading {} configurations in '{}'.", cfg.getRoot().getLength(), file_path);

	return true;
}

void Horizon::Zone::ZoneMain::initializeCore()
{
	/**
	 * Inter-connection thread.
	 */
	std::thread inter_conn_thread(std::bind(&ZoneMain::connectWithInterServer, this));

	/**
	 * Map Manager.
	 */
	MapMgr->Initialize();

	Server::initializeCore();

	inter_conn_thread.join();
}

/**
 * Initialize Zone-Server CLI Commands.
 */
void Horizon::Zone::ZoneMain::initializeCLICommands()
{
	Server::initializeCLICommands();
}

/**
 * Create connection-pool of Inter-server connections.
 */
void Horizon::Zone::ZoneMain::connectWithInterServer()
{
	if (!getGeneralConf().isTestRun()) {
		if (InterSocktMgr->Start(INTER_SESSION_NAME, this, getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(), 1)) {
			ZoneInterAPI->setInterSession(InterSocktMgr->getConnectedSession(INTER_SESSION_NAME));

			do {
				std::this_thread::sleep_for(std::chrono::seconds(2));
			} while (!isShuttingDown() && ZoneInterAPI->pingInterServer());

			if (!isShuttingDown()) {
				InterSocktMgr->closeConnection(INTER_SESSION_NAME);
				connectWithInterServer();
			}
		}
	}
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

/**
 * Zone Server Main runtime entrypoint.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	if (argc > 1)
		ZoneServer->parseExecArguments(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Zoneacter Server.
	 */
	if (!ZoneServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(*ZoneServer->getIOService(), SIGINT, SIGTERM);
	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(SignalHandler);

	// Start Zoneacter Network
	ClientSocktMgr->Start(*ZoneServer->getIOService(),
            ZoneServer->getNetworkConf().getListenIp(),
            ZoneServer->getNetworkConf().getListenPort(),
            ZoneServer->getNetworkConf().getMaxThreads());

	/**
	 * Initialize the Common Core
	 */
	ZoneServer->initializeCore();

	/*
	 * Core Cleanup
	 */
	ZoneLog->info("Server shutting down...");

	/* Stop Network */
	ClientSocktMgr->StopNetwork();
	InterSocktMgr->StopNetwork();

	signals.cancel();

	return ZoneServer->getGeneralConf().getShutdownSignal();
}
