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
#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Common/Server.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <libconfig.h++>

using boost::asio::ip::udp;
using namespace std::chrono_literals;
using namespace Horizon::Auth;

/**
 * AuthMain Constructor.
 */
AuthMain::AuthMain()
: Server("Auth", "config/", "auth-server.conf")
{
	initialize_cli_commands();
}

/**
 * AuthMain Destructor.
 */
AuthMain::~AuthMain()
{
}

#define auth_config_error(setting_name, default) \
	AuthLog->error("No setting for '{}' in configuration file, defaulting to {}", setting_name, default);

/**
 * Read /config/auth-server.yaml
 * @return true on success, false on failure.
 */
bool AuthMain::ReadConfig()
{
	libconfig::Config cfg;
	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();
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

	if (cfg.lookupValue("pass_hash_method", tmp_value)) {
		login_hash_method hashingMethod = static_cast<login_hash_method>(tmp_value);
		if (hashingMethod < PASS_HASH_NONE || hashingMethod > PASS_HASH_BCRYPT) {
			auth_config_error("pass_hash_method", PASS_HASH_NONE);
			get_auth_config().set_pass_hash_method(PASS_HASH_NONE);
		} else {
			get_auth_config().set_pass_hash_method(hashingMethod);
		}
	} else {
		auth_config_error("pass_hash_method", PASS_HASH_NONE);
		get_auth_config().set_pass_hash_method(PASS_HASH_NONE);
	}

	if (get_auth_config().get_pass_hash_method() == PASS_HASH_NONE)
		AuthLog->warn("Passwords are stored in plain text! This is not recommended!");

	if (cfg.lookupValue("client_date_format", tmp_string))
		get_auth_config().set_client_date_format(tmp_string);

	/**
	 * Logging Configuration
	 */
	const libconfig::Setting &log = cfg.getRoot()["log"];

	if (log.isGroup()) {
		if (log.lookupValue("enable_logging", tmp_value))
			get_auth_config().get_log_conf().enable();
		if (log.lookupValue("login_max_tries", tmp_value))
			get_auth_config().get_log_conf().set_login_max_tries(tmp_value);
		if (log.lookupValue("login_fail_ban_time", tmp_value))
			get_auth_config().get_log_conf().set_login_fail_ban_time(tmp_value);
		if (log.lookupValue("login_fail_check_time", tmp_value))
			get_auth_config().get_log_conf().set_login_fail_check_time(tmp_value);
	} else {
		AuthLog->warn("Invalid config type for 'log' provided, expected group. Skipping all entries...");
	}

	AuthLog->info("Logging is {}.", get_auth_config().get_log_conf().isEnabled() ? "enabled" : "disabled");
	AuthLog->info("Failed logins exceeding {} tries every {} seconds will be banned for {} seconds.",
				  get_auth_config().get_log_conf().get_login_fail_check_time(), get_auth_config().get_log_conf().get_login_max_tries(), get_auth_config().get_log_conf().get_login_fail_ban_time());

	/**
	 * Character Servers.
	 * @brief configuration for the connection to character servers.
	 */
	const libconfig::Setting &character_servers = cfg.getRoot()["character_servers"];

	if (character_servers.isList()) {
		for (int i = 0; i < character_servers.getLength(); i++) {
			const libconfig::Setting &serv = character_servers[i];
			character_server_data char_serv;

			if (!serv.lookupValue("Id", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'id' parameter for character server #{}, skipping...", i + 1);
				continue;
			}
			char_serv.id = tmp_value;

			if (!serv.lookupValue("Name", tmp_string)) {
				AuthLog->error("Invalid or non-existent 'name' parameter for character server #{}, skipping...", i + 1);
				continue;
			}
			char_serv.name = tmp_string;

			if (!serv.lookupValue("Host", tmp_string)) {
				AuthLog->error("Invalid or non-existent 'host' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}
			char_serv.ip_address = tmp_string;

			if (!serv.lookupValue("Port", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'port' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}
			char_serv.port = tmp_value;

			if (!serv.lookupValue("Type", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'type' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}

			if (tmp_value < CHAR_SERVER_TYPE_NORMAL || tmp_value >= CHAR_SERVER_TYPE_MAX) {
				AuthLog->error("Invalid or non-existent 'type' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}

			char_serv.server_type = static_cast<character_server_types>(tmp_value);

			if (!serv.lookupValue("IsNew", tmp_value)) {
				AuthLog->error("Invalid or non-existent 'is_new' parameter for character server '{}', skipping...", char_serv.name);
				continue;
			}

			char_serv.is_new = tmp_value ? true : false;

			add_character_server(char_serv);
			AuthLog->info("Configured Character Server: {}@{}:{} {}", char_serv.name, char_serv.ip_address, char_serv.port, char_serv.is_new ? "(new)" : "");
		}
	} else {
		AuthLog->warn("Invalid config type for 'log' provided, expected group. Skipping all entries...");
	}

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(cfg))
		return false;

	AuthLog->info("Done reading {} configurations in '{}'.", cfg.getRoot().getLength(), file_path);

	return true;
}

#undef auth_config_error

/**
 * CLI Command: Reload Configuration
 * @return boolean value from AuthServer->ReadConfig()
 */
bool AuthMain::clicmd_reload_config()
{
	// Clear all character server info before reloading.
	_character_servers.clear();

	AuthLog->info("Reloading configuration from '{}'.", general_conf().get_config_file_name());

	return AuthServer->ReadConfig();
}

/**
 * Initialize CLI Comamnds
 */
void AuthMain::initialize_cli_commands()
{
	add_cli_command_func("reloadconf", std::bind(&AuthMain::clicmd_reload_config, this));

	Server::initialize_cli_commands();
}

/**
 * Signal Handler from the main thread.
 * @param ioServiceRef
 * @param error
 */
void SignalHandler(const boost::system::error_code &error, int /*signal*/)
{
	if (!error) {
		AuthServer->shutdown(SIGINT);
	}
}

void AuthMain::initialize_core()
{
	/**
	 * Core Signal Handler
	 */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	// Set signal handler for callbacks.
	// Set signal handlers (this must be done before starting io_service threads,
	// because otherwise they would unblock and exit)
	signals.async_wait(std::bind(&SignalHandler, std::placeholders::_1, std::placeholders::_2));

	// Start Auth Network
	ClientSocktMgr->start(get_io_service(),
						  network_conf().get_listen_ip(),
						  network_conf().get_listen_port(),
						  network_conf().get_network_thread_count());

	// Initialize core.
	Server::initialize_core();

	uint32_t diff = general_conf().get_core_update_interval();
	/* Server Update Loop */
	while (!is_shutting_down() && !general_conf().is_test_run()) {
		process_cli_commands();
		_task_scheduler.Update();
		ClientSocktMgr->update_socket_sessions(diff);
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
 * Main Runtime Method
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	if (argc > 1)
		AuthServer->parse_exec_args(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Authentication Server.
	 */
	if (!AuthServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/**
	 * Initialize the Common Core
	 */
	AuthServer->initialize_core();

	/*
	 * Core Cleanup
	 */
	AuthLog->info("Server shutting down...");

	return AuthServer->general_conf().get_shutdown_signal();
}
