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

#include "Core/Database/MySqlConnection.hpp"
#include "Core/Logging/Logger.hpp"
#include "Server/Char/Session/Session.hpp"
#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Char/SocketMgr/InterSocketMgr.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

using namespace std;

using boost::asio::ip::udp;

/**
 * CharMain Constructor
 */
Horizon::Char::CharMain::CharMain() : Server("Char", "config/", "char-server.yaml")
{
	//
}

/**
 * CharMain Destructor
 */
Horizon::Char::CharMain::~CharMain()
{
	//
}

/**
 * Read /config/char-server.yaml
 * @return true on success false on failure.
 */
bool Horizon::Char::CharMain::ReadConfig()
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

	if (config["InterServer.Password"]) {
		getNetworkConf().setInterServerPassword(config["InterServer.Password"].as<std::string>());
	}

	CharLog->info("Outbound connections: Inter-Server configured to tcp://{}:{} {}",
	              getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(),
	              (getNetworkConf().getInterServerPassword().length()) ? "using password" : "not using password");

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!ProcessCommonConfiguration(config))
		return false;

	CharLog->info("Done reading {} configurations in '{}'.", config.size(), getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName());

	return true;
}

/* Initialize Char-Server CLI Commands */
void Horizon::Char::CharMain::InitializeCLICommands()
{
	Server::InitializeCLICommands();
}

void Horizon::Char::CharMain::InitializeCore()
{
	/* Inter-server connection thread. */
	std::thread inter_conn_thread(std::bind(&CharMain::ConnectWithInterServer, this));

	Server::InitializeCore();

	inter_conn_thread.join();
}

/**
 * Connect with the Inter-server.
 */
void Horizon::Char::CharMain::ConnectWithInterServer()
{
	if (!getGeneralConf().isTestRun()) {
		try {
			InterSocktMgr->Start(INTER_SESSION_NAME, this, getNetworkConf().getInterServerIp(),
			                                      getNetworkConf().getInterServerPort(), 1);
		} catch (boost::system::system_error &e) {
			CharLog->error("{}", e.what());
		}
	}
}

/**
 * Signal handler for the Char-Server main thread.
 * @param[in|out] error   boost system error code.
 * @param[in]     signal  interrupt signal code
 */
void SignalHandler(const boost::system::error_code &error, int /*signal*/)
{
	if (!error) {
		CharServer->shutdown(SIGINT);
	}
}

/**
 * Main entry point of the char-server application.
 * @param argc
 * @param argv
 * @return integer of shutdown signal.
 */
int main(int argc, const char * argv[])
{
	/* Parse Command Line Arguments */
	if (argc > 1)
		CharServer->ParseExecArguments(argv, argc);

	/* Read Char Configuration */
	if (!CharServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/* Core Signal Handler  */
	boost::asio::signal_set signals(*CharServer->getIOService(), SIGINT, SIGTERM);
	signals.async_wait(SignalHandler);

	/* Start Character Network */
	ClientSocktMgr->Start(*CharServer->getIOService(),
	        CharServer->getNetworkConf().getListenIp(),
            CharServer->getNetworkConf().getListenPort(),
            CharServer->getNetworkConf().getMaxThreads());

	/* Initialize the Common Core */
	CharServer->InitializeCore();

	/* Core Cleanup */
	CharLog->info("Server shutting down...");

	/* Stop Network */
	ClientSocktMgr->StopNetwork();
	InterSocktMgr->StopNetwork();

	signals.cancel();

	return CharServer->getGeneralConf().getShutdownSignal();
}
