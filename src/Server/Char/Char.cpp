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

#include "Char.hpp"
#include "CharSocketMgr.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>

using namespace std;

using boost::asio::ip::udp;

/* Create Socket Connection */
boost::asio::io_service *io_service;

CharMain::CharMain() : Server("Char", "config/", "char-server.yaml")
{
}

CharMain::~CharMain()
{
}

/**
 * Prints the header for auth server.
 * @brief Appends the Core header.
 */
void CharMain::PrintHeader()
{
	CharLog->info("Character Server Initializing...");
}

/**
 * Read /config/char-server.yaml
 */
bool CharMain::ReadConfig()
{
	YAML::Node config;
	std::string filepath = getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName();

	try {
		config = YAML::LoadFile(filepath);
	} catch (std::exception &err) {
		CharLog->error("Unable to read {}. ({})", filepath, err.what());
		return false;
	}
	/**
	 * Inter Server Settings
	 * @brief Definitions of the Inter-server networking configuration.
	 */
	if (config["InterServer.IP"]) {
		getNetworkConf().setInterServerIp(config["InterServer.IP"].as<std::string>());
	} else {
		CharLog->error("Inter-server IP configuration not set, defaulting to '127.0.0.1'.");
		getNetworkConf().setInterServerIp("127.0.0.1");
	}

	if (config["InterServer.Port"]) {
		getNetworkConf().setInterServerPort(config["InterServer.Port"].as<uint16_t>());
	} else {
		CharLog->error("Inter-server Port configuration not set, defaulting to '9998'.");
		getNetworkConf().setInterServerPort(9998);
	}

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!ProcessCommonConfiguration(config))
		return false;

	CharLog->info("Done reading {} configurations in '{}'.", config.size(), getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName());

	return true;
}

void CharMain::InitializeCLICommands()
{
	Server::InitializeCLICommands();
}

void CharMain::ConnectWithInterServer()
{
	try {
		sCharSocketMgr.StartConnection("inter-server",
		                               *CharServer->getIOService(), getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(), 1);
	} catch (boost::system::system_error &e) {
		CharLog->error("{}", e.what());
	}
}

void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error) {
		CharServer->shutdown(SIGINT);
	}
}

int main(int argc, const char * argv[])
{
	/* Header */
	CharServer->PrintHeader();

	if (argc > 1)
		CharServer->ParseRuntimeArguments(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Character Server.
	 */
	if (!CharServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	// Start Character Network
	sCharSocketMgr.StartNetwork(*CharServer->getIOService(),
	        CharServer->getNetworkConf().getListenIp(),
            CharServer->getNetworkConf().getListenPort(),
            CharServer->getNetworkConf().getMaxThreads());

	/**
	 * Establish a connection to the inter-server.
	 */
	CharServer->ConnectWithInterServer();

	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(*CharServer->getIOService(), SIGINT, SIGTERM);

	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(SignalHandler);

	/**
	 * Initialize the Common Core
	 */
	CharServer->InitializeCore();

	/*
	 * Core Cleanup
	 */
	CharLog->info("Server shutting down...");

	/* Stop Network */
	sCharSocketMgr.StopNetwork();

	signals.cancel();

	return CharServer->getGeneralConf().getShutdownSignal();
}