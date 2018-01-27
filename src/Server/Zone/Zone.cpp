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

/* Create Socket Connection */
boost::asio::io_service *io_service;

ZoneMain::ZoneMain() : Server("Zone", "config/", "zone-server.yaml")
{
}

ZoneMain::~ZoneMain()
{
}

/**
 * Prints the header for auth server.
 * @brief Appends the Core header.
 */
void ZoneMain::PrintHeader()
{
	ZoneLog->info("Zone Server Initializing...");
}

/**
 * Read /config/zone-server.yaml
 */
bool ZoneMain::ReadConfig()
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
	 * Process Configuration that is common between servers.
	 */
	if (!ProcessCommonConfiguration(config))
		return false;

	ZoneLog->info("Done reading {} configurations in '{}'.", config.size(), getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName());

	return true;
}

void ZoneMain::InitializeCLICommands()
{
	Server::InitializeCLICommands();
}

void ZoneMain::ConnectWithInterServer()
{
	try {
		sZoneSocketMgr.StartNetworkConnection("inter-server", this, getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(), 10);
	} catch (boost::system::system_error &e) {
		ZoneLog->error("{}", e.what());
	}
}

void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error) {
		ZoneServer->shutdown(SIGINT);
	}
}

int main(int argc, const char * argv[])
{
	/* Header */
	ZoneServer->PrintHeader();

	if (argc > 1)
		ZoneServer->ParseRuntimeArguments(argv, argc);

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
	sZoneSocketMgr.StartNetwork(*ZoneServer->getIOService(),
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
	sZoneSocketMgr.StopNetwork();

	signals.cancel();

	return ZoneServer->getGeneralConf().getShutdownSignal();
}