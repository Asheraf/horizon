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
#include "Auth.hpp"
#include "Server/Auth/SocketMgr/InterSocketMgr.hpp"
#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <Server/Common/Server.hpp>
#include <libconfig.h++>

using boost::asio::ip::udp;
using namespace std::chrono_literals;

/**
 * AuthMain Constructor.
 */
Horizon::Auth::AuthMain::AuthMain()
: Server("Auth", "config/", "auth-server.conf")
{
	InitializeCLICommands();
}

/**
 * AuthMain Destructor.
 */
Horizon::Auth::AuthMain::~AuthMain()
{
}

#define auth_config_error(setting_name, default) \
	AuthLog->error("No setting for '{}' in configuration file, defaulting to {}", setting_name, default);

/**
 * Read /config/auth-server.yaml
 * @return true on success, false on failure.
 */
bool Horizon::Auth::AuthMain::ReadConfig()
{

	libconfig::Config cfg;
	std::string file_path = getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName();
	std::string tmp_string;
	int tmp_value;

	// Read the file. If there is an error, report it and exit.
	try {
		cfg.readFile(file_path.c_str());
	} catch(const libconfig::FileIOException &fioex) {
		CharLog->error("I/O error while reading file '{}'.", file_path);
		return false;
	} catch(const libconfig::ParseException &pex) {
		AuthLog->error("Parse error at {}:{} - {}", pex.getFile(), pex.getLine(), pex.getError());
		return false;
	}

	const libconfig::Setting &inter_server = cfg.getRoot()["inter_server"];

	if (!inter_server.lookupValue("ip_address", tmp_string)) {
		auth_config_error("inter_server.ip_address", "127.0.0.1");
		getNetworkConf().setInterServerIp("127.0.0.1");
	} else {
		getNetworkConf().setInterServerIp(tmp_string);
	}

	if (!inter_server.lookupValue("port", tmp_value)) {
		auth_config_error("inter_server.port", 9998);
		getNetworkConf().setInterServerPort(9998);
	} else {
		getNetworkConf().setInterServerPort(tmp_value);
	}

	if (!inter_server.lookupValue("password", tmp_string)) {
		auth_config_error("inter_server.password", "ABCDEF");
		getNetworkConf().setInterServerPassword(tmp_string);
	} else {
		getNetworkConf().setInterServerPassword(tmp_string);
	}

	AuthLog->info("Outbound connections: Inter-Server configured to tcp://{}:{} {}",
		getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(),
		(getNetworkConf().getInterServerPassword().length()) ? "using password" : "not using password");

	if (cfg.lookupValue("pass_hash_method", tmp_value)) {
		HashingMethods hashingMethod = static_cast<HashingMethods>(tmp_value);
		if (hashingMethod < PASS_HASH_NONE || hashingMethod > PASS_HASH_BCRYPT) {
			auth_config_error("pass_hash_method", PASS_HASH_NONE);
			getAuthConfig().setPassHashMethod(PASS_HASH_NONE);
		} else {
			getAuthConfig().setPassHashMethod(hashingMethod);
		}
	} else {
		auth_config_error("pass_hash_method", PASS_HASH_NONE);
		getAuthConfig().setPassHashMethod(PASS_HASH_NONE);
	}

	if (getAuthConfig().getPassHashMethod() == PASS_HASH_NONE)
		AuthLog->warn("Passwords are stored in plain text! This is not recommended!");

	if (cfg.lookupValue("client_date_format", tmp_string))
		getAuthConfig().setClientDateFormat(tmp_string);

	/**
	 * Logging Configuration
	 */
	const libconfig::Setting &log = cfg.getRoot()["log"];

	if (log.isGroup()) {
		if (log.lookupValue("enable_logging", tmp_value))
			getAuthConfig().getLogConf().enable();
		if (log.lookupValue("login_max_tries", tmp_value))
			getAuthConfig().getLogConf().setLoginMaxTries(tmp_value);
		if (log.lookupValue("login_fail_ban_time", tmp_value))
			getAuthConfig().getLogConf().setLoginFailBanTime(tmp_value);
		if (log.lookupValue("login_fail_check_time", tmp_value))
			getAuthConfig().getLogConf().setLoginFailCheckTime(tmp_value);
	} else {
		AuthLog->warn("Invalid config type for 'log' provided, expected group. Skipping all entries...");
	}

	AuthLog->info("Logging is {}.", getAuthConfig().getLogConf().isEnabled() ? "enabled" : "disabled");
	AuthLog->info("Failed logins exceeding {} tries every {} seconds will be banned for {} seconds.",
				  getAuthConfig().getLogConf().getLoginFailCheckTime(), getAuthConfig().getLogConf().getLoginMaxTries(), getAuthConfig().getLogConf().getLoginFailBanTime());

	/**
	 * Character Servers.
	 * @brief configuration for the connection to character servers.
	 */
	const libconfig::Setting &character_servers = cfg.getRoot()["character_servers"];

	if (character_servers.isList()) {
		for (int i = 0; i < character_servers.getLength(); i++) {
			const libconfig::Setting &serv = character_servers[i];
			character_server_data char_serv;

			if (!serv.lookupValue("id", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'id' parameter for character server #{}, skipping...", i + 1);
				continue;
			}
			char_serv.id = tmp_value;

			if (!serv.lookupValue("name", tmp_string)) {
				AuthLog->error("Invalid or non-existent 'name' parameter for character server #{}, skipping...", i + 1);
				continue;
			}
			char_serv.name = tmp_string;

			if (!serv.lookupValue("host", tmp_string)) {
				AuthLog->error("Invalid or non-existent 'host' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}
			char_serv.ip_address = tmp_string;

			if (!serv.lookupValue("port", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'port' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}
			char_serv.port = tmp_value;

			if (!serv.lookupValue("type", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'type' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}

			if (tmp_value < CHAR_SERVER_TYPE_NORMAL || tmp_value >= CHAR_SERVER_TYPE_MAX) {
				AuthLog->error("Invalid or non-existent 'type' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}

			char_serv.server_type = static_cast<character_server_types>(tmp_value);

			if (!serv.lookupValue("is_new", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'is_new' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}

			char_serv.is_new = tmp_value ? true : false;

			addCharacterServer(char_serv);
			AuthLog->info("Configured Character Server: {}@{}:{} {}", char_serv.name, char_serv.ip_address, char_serv.port, char_serv.is_new ? "(new)" : "");
		}
	} else {
		AuthLog->warn("Invalid config type for 'log' provided, expected group. Skipping all entries...");
	}

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!ProcessCommonConfiguration(cfg))
		return false;

	AuthLog->info("Done reading {} configurations in '{}'.", cfg.getRoot().getLength(), file_path);

	return true;
}

#undef auth_config_error

/**
 * CLI Command: Reload Configuration
 * @return boolean value from AuthServer->ReadConfig()
 */
bool Horizon::Auth::AuthMain::CLICmd_ReloadConfig()
{
	// Clear all character server info before reloading.
	_character_servers.clear();

	AuthLog->info("Reloading configuration from '{}'.", getGeneralConf().getConfigFileName());

	return AuthServer->ReadConfig();
}

/**
 * Initialize CLI Comamnds
 */
void Horizon::Auth::AuthMain::InitializeCLICommands()
{
	addCLIFunction("reloadconf", std::bind(&AuthMain::CLICmd_ReloadConfig, this));

	Server::InitializeCLICommands();
}

void Horizon::Auth::AuthMain::InitializeCore()
{
	/**
	 * Establish a connection to the inter-server.
	 */
	std::thread inter_conn_thread(std::bind(&AuthMain::ConnectWithInterServer, this));

	// Initialize Main Core.
	Server::InitializeCore();

	// Join connection thread on end.
	inter_conn_thread.join();
}

/**
 * Connect with Inter Server
 */
void Horizon::Auth::AuthMain::ConnectWithInterServer()
{
	if (!getGeneralConf().isTestRun()) {
		try {
			InterSocktMgr->Start(INTER_SESSION_NAME, this, getNetworkConf().getInterServerIp(), getNetworkConf().getInterServerPort(), 1);
		} catch (boost::system::system_error &e) {
		}
	}
}

/**
 * Signal Handler from the main thread.
 * @param ioServiceRef
 * @param error
 */
void SignalHandler(std::weak_ptr<boost::asio::io_service> &ioServiceRef, const boost::system::error_code &error, int /*signal*/)
{
	if (!error) {
		if (std::shared_ptr<boost::asio::io_service> io_service = ioServiceRef.lock())
			io_service->stop();
		AuthServer->shutdown(SIGINT);
	}
}

/**
 * Main Runtime Method
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	if (argc > 1)
		AuthServer->ParseExecArguments(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Authentication Server.
	 */
	if (!AuthServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(*AuthServer->getIOService(), SIGINT, SIGTERM);
	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(std::bind(&SignalHandler, std::weak_ptr<boost::asio::io_service>(AuthServer->getIOService()), std::placeholders::_1, std::placeholders::_2));

	// Start Auth Network
	ClientSocktMgr->Start(*AuthServer->getIOService(),
		AuthServer->getNetworkConf().getListenIp(),
		AuthServer->getNetworkConf().getListenPort(),
		AuthServer->getNetworkConf().getMaxThreads());

	/**
	 * Initialize the Common Core
	 */
	AuthServer->InitializeCore();

	/*
	 * Core Cleanup
	 */
	AuthLog->info("Server shutting down...");

	/* Stop Network */
	ClientSocktMgr->StopNetwork();
	InterSocktMgr->StopNetwork();

	// Cancel signal handling.
	signals.cancel();

	return AuthServer->getGeneralConf().getShutdownSignal();
}
