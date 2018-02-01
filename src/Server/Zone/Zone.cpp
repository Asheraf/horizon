/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#include "Zone.hpp"
#include "ZoneSocketMgr.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>

using namespace std;
using boost::asio::ip::udp;

/**
 * Zone Main server constructor.
 */
Horizon::Zone::ZoneMain::ZoneMain() : Server("Zone", "config/", "zone-server.yaml")
{
}

/**
 * Zone Main server destructor.
 */
Horizon::Zone::ZoneMain::~ZoneMain()
{
}

/**
 * Read /config/zone-server.yaml
 * @return false on failure, true on success.
 */
bool Horizon::Zone::ZoneMain::ReadConfig()
{
	YAML::Node config;
	std::string filepath = getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName();

	try {
		config = YAML::LoadFile(filepath);
	} catch (std::exception &err) {
		ZoneLog->error("Unable to read {}. ({})", filepath, err.what());
		return false;
	}
	/**
	 * Inter Server Settings
	 * @brief Definitions of the Inter-server networking configuration.
	 */
	if (config["InterServer.IP"]) {
		getNetworkConf().setInterServerIp(config["InterServer.IP"].as<std::string>());
	} else {
		ZoneLog->error("Inter-server IP configuration not set, defaulting to '127.0.0.1'.");
		getNetworkConf().setInterServerIp("127.0.0.1");
	}

	if (config["InterServer.Port"]) {
		getNetworkConf().setInterServerPort(config["InterServer.Port"].as<uint16_t>());
	} else {
		ZoneLog->error("Inter-server Port configuration not set, defaulting to '9998'.");
		getNetworkConf().setInterServerPort(9998);
	}

	if (config["InterServer.Password"]) {
		getNetworkConf().setInterServerPassword(config["InterServer.Password"].as<std::string>());
	}

	ZoneLog->info("Outbound connections: Inter-Server configured to tcp://{}:{} {}",
	              getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(),
	              (getNetworkConf().getInterServerPassword().length()) ? "using password" : "not using password");

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!ProcessCommonConfiguration(config))
		return false;

	ZoneLog->info("Done reading {} configurations in '{}'.", config.size(), getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName());

	return true;
}

void Horizon::Zone::ZoneMain::InitializeCore()
{
	/**
	 * Inter-connection thread.
	 */
	std::thread inter_conn_thread(std::bind(&ZoneMain::ConnectWithInterServer, this));

	Server::InitializeCore();

	inter_conn_thread.join();
}

/**
 * Initialize Zone-Server CLI Commands.
 */
void Horizon::Zone::ZoneMain::InitializeCLICommands()
{
	Server::InitializeCLICommands();
}

/**
 * Create connection-pool of Inter-server connections.
 */
void Horizon::Zone::ZoneMain::ConnectWithInterServer()
{
	if (!getGeneralConf().isTestRun()) {
		try {
			sZoneSocketMgr->StartNetworkConnection("inter-server", this, getNetworkConf().getInterServerIp(),
			                                      getNetworkConf().getInterServerPort(), 10);
		} catch (boost::system::system_error &e) {
			ZoneLog->error("{}", e.what());
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
		ZoneServer->ParseExecArguments(argv, argc);

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
	sZoneSocketMgr->StartNetwork(*ZoneServer->getIOService(),
            ZoneServer->getNetworkConf().getListenIp(),
            ZoneServer->getNetworkConf().getListenPort(),
            ZoneServer->getNetworkConf().getMaxThreads());

	/**
	 * Initialize the Common Core
	 */
	ZoneServer->InitializeCore();

	/*
	 * Core Cleanup
	 */
	ZoneLog->info("Server shutting down...");

	/* Stop Network */
	sZoneSocketMgr->StopNetwork();

	signals.cancel();

	return ZoneServer->getGeneralConf().getShutdownSignal();
}
