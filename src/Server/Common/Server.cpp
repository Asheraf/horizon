/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
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

#include "Server.hpp"

#include "Server/Common/CLI/CommandLineInterface.hpp"
#include "version.hpp"

#include <iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>
#include <jdbc/cppconn/version_info.h>
#include <readline/readline.h>

/* Public */
Server::Server(std::string /*name*/, std::string config_file_path, std::string config_file_name)
{
	std::cout << "   _   _            _                  " << std::endl;
	std::cout << "  | | | |          (_)                 " << std::endl;
	std::cout << "  | |_| | ___  _ __ _ _______  _ __    " << std::endl;
	std::cout << "  |  _  |/ _ \\| '__| |_  / _ \\| '_ \\   " << std::endl;
	std::cout << "  | | | | (_) | |  | |/ / (_) | | | |  " << std::endl;
	std::cout << "  \\_| |_/\\___/|_|  |_/___\\___/|_| |_|  " << std::endl;
	std::cout << std::endl;

	CoreLog->info("Compile CXX Flags: {}", _CMAKE_CXX_FLAGS);
	CoreLog->info("Version: {}", VER_PRODUCTVERSION_STR);
	CoreLog->info("Last Update: {}", _DATE);
	CoreLog->info("Branch: {}", _BRANCH);
	CoreLog->info("Copyright: {}", VER_LEGALCOPYRIGHT_STR);
	CoreLog->info("SPDLog Version: v{}.{}.{}", SPDLOG_VER_MAJOR, SPDLOG_VER_MINOR, SPDLOG_VER_PATCH);
	CoreLog->info("Boost Version: v{}.{}.{}", (BOOST_VERSION / 100000), (BOOST_VERSION / 100 % 1000),(BOOST_VERSION % 100));
	CoreLog->info("MySQL Connector++ Version: v{}", MYCPPCONN_STATIC_MYSQL_VERSION);
	CoreLog->info("Readline Version: v{}", RL_READLINE_VERSION);

	this->general_config.config_file_path = config_file_path;
	this->general_config.config_file_name = config_file_name;
}

Server::~Server()
{
}

void Server::parse_exec_args(const char *argv[], int argc)
{
	if (strcmp(argv[1], "--test-run") == 0) {
		CoreLog->info("Test run initiated.");
		for (int i = 2; i < argc; ++i) {
			std::string arg(argv[i]);
			std::vector<std::string> separated_args;
			boost::algorithm::split(separated_args, arg, boost::algorithm::is_any_of(" "));

			for (auto it = separated_args.begin(); it != separated_args.end(); ++it) {
				std::vector<std::string> arg_parts;
				boost::algorithm::split(arg_parts, *it, boost::algorithm::is_any_of("="));

				if (arg_parts.at(0).compare("--dbuser") == 0) {
					database_conf().set_username(arg_parts.at(1));
					CoreLog->info("Database user is set to '{}'", database_conf().get_database());
				} else if (arg_parts.at(0).compare("--dbpassword") == 0) {
					database_conf().set_password(arg_parts.at(1));
					CoreLog->info("Database password is set to '{}'", database_conf().get_password());
				} else if (arg_parts.at(0).compare("--dbhost") == 0) {
					database_conf().set_host(arg_parts.at(1));
					CoreLog->info("Database host is set to '{}'", database_conf().get_host());
				} else if (arg_parts.at(0).compare("--dbdatabase") == 0) {
					database_conf().set_database(arg_parts.at(1));
					CoreLog->info("Database database is set to '{}'", database_conf().get_database());
				} else {
					CoreLog->error("Unrecognised argument for test run '{}'", *it);
				}
			}
		}
		general_conf().set_test_run();
	}
}

#define core_config_error(setting_name, default) \
CoreLog->error("No setting for '{}' in configuration file, defaulting to {}", setting_name, default);

bool Server::parse_common_configs(sol::table &tbl)
{
	std::string tmp_string{""};
	uint32_t tmp_value{0};

	network_conf().set_listen_ip(tbl.get_or("bind_ip", std::string("127.0.0.1")));

	network_conf().set_listen_port(tbl.get_or("bind_port", 0));
	if (network_conf().get_listen_port() == 0){
		AuthLog->error("Invalid or non-existent configuration for 'bind_port', Halting...");
		return false;
	}

	network_conf().set_network_thread_count(tbl.get_or("network_threads", 1));

	if (std::thread::hardware_concurrency() > network_conf().get_network_thread_count())
		core_config_error("network_threads", 1);

	CoreLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.",
				  network_conf().get_listen_ip(), network_conf().get_listen_port(), network_conf().get_network_thread_count());

	/**
	 * Database Configuration
	 * @brief
	 */
	if (!general_conf().is_test_run()) {
		sol::table dbtbl = tbl.get<sol::table>("database");

		database_conf().set_host(dbtbl.get_or("hostname", std::string("127.0.0.1")));
		database_conf().set_port(dbtbl.get_or("port", 3306));
		database_conf().set_database(dbtbl.get_or("database", std::string("horizon")));
		database_conf().set_username(dbtbl.get_or("username", std::string("horizon")));
		database_conf().set_password(dbtbl.get_or("password", std::string("horizon")));
		database_conf().set_db_thread_count(dbtbl.get_or("connection_threads", 1));
	}

	/**
	 * Core I/O Thread Count
	 */
	general_conf().set_io_thread_count(tbl.get_or("global_io_threads", 1));

	CoreLog->info("Using {} threads for working on Global I/O Events.", general_conf().get_io_thread_count());

	/**
	 * Core Update Interval.
	 */
	general_conf().set_core_update_interval(tbl.get_or("core_update_interval", 500));
	CoreLog->info("Core update interval set to {}µs.", general_conf().get_core_update_interval());

	/**
	 * Client Type
	 */
	general_conf().set_client_type((client_type) tbl.get_or("client_type", (int) CLIENT_TYPE_RAGEXE));
	switch (general_conf().get_client_type())
	{
	case CLIENT_TYPE_RAGEXE:
		general_conf().set_client_type(CLIENT_TYPE_RAGEXE);
		CoreLog->warn("Server has been configured to use the 'Ragexe' client for packet information.");
		break;
	case CLIENT_TYPE_RAGEXE_RE:
		general_conf().set_client_type(CLIENT_TYPE_RAGEXE_RE);
		CoreLog->warn("Server has been configured to use the 'RagexeRE' client for packet information.");
		break;
	case CLIENT_TYPE_ZERO:
		general_conf().set_client_type(CLIENT_TYPE_ZERO);
		CoreLog->warn("Server has been configured to use the 'ZERO' client for packet information.");
		break;
	case CLIENT_TYPE_SAKRAY:
		general_conf().set_client_type(CLIENT_TYPE_SAKRAY);
		CoreLog->warn("Server has been configured to use the 'Sakray' client for packet information.");
		break;
	case CLIENT_TYPE_AD:
		general_conf().set_client_type(CLIENT_TYPE_AD);
		CoreLog->warn("Server has been configured to use the 'AD' client for packet information.");
		break;
	default:
		CoreLog->warn("Invalid client type {} set, defaulting to 0 (Ragexe)", tmp_value);
		general_conf().set_client_type(CLIENT_TYPE_RAGEXE);
		break;
	}

	general_conf().set_packet_version(tbl.get_or("packet_version", 0));
	if (general_conf().get_packet_version() == 0) {
		CoreLog->warn("No packet version defined for packet handling!");
		return false;
	}

	return true;
}

#undef core_config_error

void Server::initialize_mysql()
{
	std::string conn_uri = database_conf().get_username() + ":" + database_conf().get_password() + "@127.0.0.1/" + database_conf().get_database();

	_mysql_client = std::make_shared<mysqlx::Client>("mysqlx://" + conn_uri);

	try {
		mysqlx::Session s = _mysql_client->getSession();
		CoreLog->info("Successfully connected to mysql server on {}.", conn_uri);
	} catch (const mysqlx::Error &err) {
		CoreLog->info("Could not connect to mysql server on {} due to {}.", conn_uri, err.what());
	}
}

void Server::initialize_command_line()
{
	if (general_conf().is_test_run()) {
		CoreLog->info("Command line not supported during test-runs... skipping.");
		return;
	}

	_cli_thread = std::thread(std::bind(&cli_thread_start, this));
	initialize_cli_commands();
}

void Server::initialize_cli_commands()
{
	add_cli_command_func("shutdown", std::bind(&Server::clicmd_shutdown, this));
}

void Server::process_cli_commands()
{
	std::shared_ptr<CLICommand> command;

	while ((command = _cli_cmd_queue.try_pop())) {
		bool ret = false;
		std::function<bool(void)> cmd_func = get_cli_command_func(command->m_command);

		if (cmd_func) {
			ret = cmd_func();
		} else {
			CoreLog->info("Command '{}' not found!", command->m_command);
		}

		if (command->m_finish_func != nullptr)
			command->m_finish_func(command, ret);
	}
}

void Server::initialize_core()
{
	int global_thread_count = std::max(general_conf().get_io_thread_count(), 1);

	for (int i = 0; i < global_thread_count; ++i)
		_global_thread_group.create_thread(boost::bind(&boost::asio::io_service::run, boost::ref(get_io_service())));

	CoreLog->info("A global I/O thread pool of {} threads have been created.", global_thread_count);

	/**
	 * MySQL Startup
	 */
	initialize_mysql();

	/**
	 * Initialize Commandline Interface
	 */
	initialize_command_line();
}

void Server::finalize_core()
{
	if (general_conf().is_test_run())
		return;

	int global_thread_count = std::max(general_conf().get_io_thread_count(), 1);

	if (_cli_thread.joinable())
		_cli_thread.join();

	get_io_service().stop();

	_global_thread_group.join_all();

	CoreLog->info("Shutting down global I/O thread pool of {} threads.", global_thread_count);
}

boost::asio::io_service &Server::get_io_service()
{
	return _io_service;
}
