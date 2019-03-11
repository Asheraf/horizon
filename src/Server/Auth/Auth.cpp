/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/
#include "Auth.hpp"
#include "Server/Auth/SocketMgr/ClientSocketMgr.hpp"
#include "Server/Common/Server.hpp"

#include <boost/asio.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <sol.hpp>

using boost::asio::ip::udp;
using namespace std::chrono_literals;
using namespace Horizon::Auth;

/**
 * AuthMain Constructor.
 */
AuthMain::AuthMain()
: Server("Auth", "config/", "auth-server.lua")
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
	sol::state lua;

	std::string file_path = general_conf().get_config_file_path() + general_conf().get_config_file_name();
	std::string tmp_string;
	int tmp_value;
	sol::table tbl;

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
		tbl = lua["server_config"];
	} catch (const std::exception &error) {
		CharLog->error("AuthMain::ReadConfig: '{}'.", error.what());
		return false;
	}

	tmp_value = tbl.get_or("pass_hash_method", (int) PASS_HASH_NONE);
	if (tmp_value < PASS_HASH_NONE || tmp_value > PASS_HASH_SCRYPT) {
		auth_config_error("pass_hash_method", PASS_HASH_NONE);
		get_auth_config().set_pass_hash_method(PASS_HASH_NONE);
	} else {
		get_auth_config().set_pass_hash_method((login_hash_method) tmp_value);
	}

	if (get_auth_config().get_pass_hash_method() == PASS_HASH_NONE)
		AuthLog->warn("Passwords are stored in plain text! This is not recommended!");

	tmp_string = tbl.get_or("client_date_format", std::string("%Y-%m-%d %H:%M:%S"));
	get_auth_config().set_client_date_format(tmp_string);

	/**
	 * Logging Configuration
	 */
	try {
		sol::table log_tbl = tbl.get<sol::table>("log");

		bool enable = log_tbl.get_or("enable_logging", false);

		if (enable) {
			get_auth_config().get_log_conf().enable();
			get_auth_config().get_log_conf().set_login_max_tries(log_tbl.get_or("login_max_tries", 0));
			get_auth_config().get_log_conf().set_login_fail_ban_time(log_tbl.get_or("login_fail_ban_time", 0));
			get_auth_config().get_log_conf().set_login_fail_check_time(log_tbl.get_or("login_fail_check_time", 0));
		}
	} catch (std::exception &error) {
		AuthLog->info("Log configuration was not found! Using default values...");
	}

	AuthLog->info("Logging is {}.", get_auth_config().get_log_conf().isEnabled() ? "enabled" : "disabled");
	AuthLog->info("Failed logins exceeding {} tries every {} seconds will be banned for {} seconds.",
				  get_auth_config().get_log_conf().get_login_fail_check_time(), get_auth_config().get_log_conf().get_login_max_tries(), get_auth_config().get_log_conf().get_login_fail_ban_time());

	/**
	 * Character Servers.
	 * @brief configuration for the connection to character servers.
	 */
	sol::table cs_tbl = tbl.get<sol::table>("character_servers");
	cs_tbl.for_each([this](sol::object const &key, sol::object const &value) {
		std::string t_str;
		character_server_data char_serv;
		sol::table serv = value.as<sol::table>();

		char_serv.id = key.as<int>();
		char_serv.name = serv.get_or("Name", std::string(""));
		if (char_serv.name.empty()) {
			AuthLog->error("Invalid or non-existent 'name' parameter for character server #{}, skipping...", char_serv.id);
			return;
		}

		char_serv.ip_address = serv.get_or("Host", std::string(""));
		if (char_serv.ip_address.empty()) {
			AuthLog->error("Invalid or non-existent 'host' parameter for character server '{}', skipping...", char_serv.name);
			return;
		}

		char_serv.port = serv.get_or("Port", 0);
		if (!char_serv.port) {
			AuthLog->error("Invalid or non-existent 'port' parameter for character server '{}', skipping...", char_serv.name);
			return;
		}

		char_serv.server_type = (character_server_type) serv.get_or("Type", (int) CHAR_SERVER_TYPE_NORMAL);

		char_serv.is_new = serv.get_or("IsNew", false);

		add_character_server(char_serv);
		AuthLog->info("Configured Character Server: {}@{}:{} {}", char_serv.name, char_serv.ip_address, char_serv.port, char_serv.is_new ? "(new)" : "");
	});

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	AuthLog->info("Done reading server configuration from '{}'.", file_path);

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
		AuthServer->set_shutdown_stage(SHUTDOWN_INITIATED);
		AuthServer->set_shutdown_signal(SIGTERM);
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
	while (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		process_cli_commands();
		_task_scheduler.Update();
		ClientSocktMgr->update_socket_sessions(diff);
		std::this_thread::sleep_for(std::chrono::microseconds(diff));
	}

	/**
	 * Server shutdown routine begins here...
	 */
	_task_scheduler.CancelAll();
	ClientSocktMgr->stop_network();
	Server::finalize_core();

	set_shutdown_stage(SHUTDOWN_CLEANUP_COMPLETE);

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
