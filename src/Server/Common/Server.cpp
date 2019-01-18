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

#include "Server.hpp"

#include "Server/Common/CLI/CommandLineInterface.hpp"
#include "version.hpp"

#include <iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

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

	CoreLog->info("Version: {}", VER_FILEVERSION_STR);
	CoreLog->info("Branch: {}", _BRANCH);
	CoreLog->info("Copyright: {}", VER_LEGALCOPYRIGHT_STR);
	CoreLog->info("Boost Version: v{}.{}.{}", (BOOST_VERSION / 100000), (BOOST_VERSION / 100 % 1000),(BOOST_VERSION % 100));
	CoreLog->info("Compiled On: ", _DATE);

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
					CoreLog->info("Database user is manually set to '{}'", database_conf().get_database());
				} else if (arg_parts.at(0).compare("--dbpassword") == 0) {
					database_conf().set_password(arg_parts.at(1));
					CoreLog->info("Database password is manually set to '{}'", database_conf().get_password());
				} else if (arg_parts.at(0).compare("--dbhost") == 0) {
					database_conf().set_host(arg_parts.at(1));
					CoreLog->info("Database host is manually set to '{}'", database_conf().get_host());
				} else if (arg_parts.at(0).compare("--dbdatabase") == 0) {
					database_conf().set_database(arg_parts.at(1));
					CoreLog->info("Database database is manually set to '{}'", database_conf().get_database());
				} else if (arg_parts.at(0).compare("--dbthreads") == 0) {
					int num = std::atoi(arg_parts.at(1).c_str());
					int threads = std::max(1, std::min(num, 10));
					database_conf().set_db_thread_count(threads);
					CoreLog->info("Database max threads are manually set to '{}'", database_conf().get_db_thread_count());
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

bool Server::parse_common_configs(libconfig::Config &cfg)
{
	std::string tmp_string{""};
	uint32_t tmp_value{0};

	if (cfg.lookupValue("bind_ip", tmp_string)) {
		network_conf().set_listen_ip(tmp_string);
	} else {
		core_config_error("bind_ip", "127.0.0.1");
		network_conf().set_listen_ip("127.0.0.1");
	}

	if (cfg.lookupValue("bind_port", tmp_value)) {
		network_conf().set_listen_port(tmp_value);
	} else {
		AuthLog->error("Invalid or non-existent configuration for 'bind_port', Halting...");
		return false;
	}

	if (cfg.lookupValue("network_threads", tmp_value)) {
		network_conf().set_network_thread_count(tmp_value);
	} else {
		core_config_error("network_threads", 1);
		network_conf().set_network_thread_count(1);
	}

	CoreLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.",
				  network_conf().get_listen_ip(), network_conf().get_listen_port(), network_conf().get_network_thread_count());

	/**
	 * Database Configuration
	 * @brief
	 */
	if (!general_conf().is_test_run()) {
		const libconfig::Setting &dbconf = cfg.getRoot()["database"];

		if (dbconf.lookupValue("hostname", tmp_string)) {
			database_conf().set_host(tmp_string);
		} else {
			core_config_error("hostname", "127.0.0.1");
			database_conf().set_host("127.0.0.1");
		}

		if (dbconf.lookupValue("port", tmp_value)) {
			database_conf().set_port(tmp_value);
		} else {
			core_config_error("hostname", 3306);
			database_conf().set_port(3306);
		}

		if (dbconf.lookupValue("database", tmp_string)) {
			database_conf().set_database(tmp_string);
		} else {
			core_config_error("database", "horizon");
			database_conf().set_database("horizon");
		}

		if (dbconf.lookupValue("username", tmp_string)) {
			database_conf().set_username(tmp_string);
		} else {
			core_config_error("username", "horizon");
			database_conf().set_username("horizon");
		}

		if (dbconf.lookupValue("password", tmp_string)) {
			database_conf().set_password(tmp_string);
		} else {
			core_config_error("password", "horizon");
			database_conf().set_password("horizon");
		}

		if (dbconf.lookupValue("connection_threads", tmp_value)) {
			database_conf().set_db_thread_count(tmp_value);
		} else {
			core_config_error("connection_threads", 1);
			database_conf().set_db_thread_count(1);
		}
	}

	/**
	 * Core I/O Thread Count
	 */
	if (cfg.lookupValue("global_io_threads", tmp_value)) {
		general_conf().set_io_thread_count(tmp_value);
		CoreLog->info("Using {} threads for working on Global I/O Events.", general_conf().get_io_thread_count());
	} else {
		CoreLog->info("I/O Thread configuration not found, defaulting to 2.");
		general_conf().set_io_thread_count(2);
	}

	/**
	 * Core Update Interval.
	 */
	if (cfg.lookupValue("core_update_interval", tmp_value)) {
		general_conf().set_core_update_interval(tmp_value);
		CoreLog->info("Core update interval set to {}ms.", general_conf().get_core_update_interval());
	} else {
		CoreLog->info("Core update interval was not defined, defaulting to 500ms.");
		general_conf().set_core_update_interval(500);
	}

	return true;
}

#undef core_config_error

void Server::initialize_mysql()
{
	std::string conn_uri = database_conf().get_username() + ":" + database_conf().get_password() + "@127.0.0.1/" + database_conf().get_database();

	_mysql_client = std::make_shared<mysqlx::Client>("mysqlx://root:sagun123@localhost:33060/horizon");

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

	m_CLIThread = std::thread(std::bind(&cli_thread_start, this));
	initialize_cli_commands();
}

void Server::initialize_cli_commands()
{
	add_cli_command_func("shutdown", std::bind(&Server::clicmd_shutdown, this));
}

void Server::process_cli_commands()
{
	std::shared_ptr<CLICommand> command;

	while ((command = m_CLICmdQueue.try_pop())) {
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
	boost::thread_group global_thread_group;

	int global_thread_count = std::max(general_conf().get_io_thread_count(), 1);

	for (int i = 0; i < global_thread_count; ++i)
		global_thread_group.create_thread(boost::bind(&boost::asio::io_service::run, boost::ref(get_io_service())));

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
	if (!general_conf().is_test_run())
		m_CLIThread.join();
}

boost::asio::io_service &Server::get_io_service()
{
	return _io_service;
}
