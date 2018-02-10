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
#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>

/* Public */
Server::Server(std::string /*name*/, std::string config_file_path, std::string config_file_name)
: io_service(std::make_shared<boost::asio::io_service>())
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

void Server::ParseExecArguments(const char *argv[], int argc)
{
	if (strcmp(argv[1], "--test-run") == 0) {
		CoreLog->info("Test run initiated.");
		for (int i = 2; i < argc; ++i) {
			std::string arg(argv[i]);
			std::vector<std::string> separated_args;
			boost::split(separated_args, arg, boost::is_any_of(" "));

			for (auto it = separated_args.begin(); it != separated_args.end(); ++it) {
				std::vector<std::string> arg_parts;
				boost::split(arg_parts, *it, boost::is_any_of("="));

				if (arg_parts.at(0).compare("--dbuser") == 0) {
					getDatabaseConf().setUsername(arg_parts.at(1));
					CoreLog->info("Database user is manually set to '{}'", getDatabaseConf().getDatabase());
				} else if (arg_parts.at(0).compare("--dbpassword") == 0) {
					getDatabaseConf().setPassword(arg_parts.at(1));
					CoreLog->info("Database password is manually set to '{}'", getDatabaseConf().getPassword());
				} else if (arg_parts.at(0).compare("--dbhost") == 0) {
					getDatabaseConf().setHost(arg_parts.at(1));
					CoreLog->info("Database host is manually set to '{}'", getDatabaseConf().getHost());
				} else if (arg_parts.at(0).compare("--dbdatabase") == 0) {
					getDatabaseConf().setDatabase(arg_parts.at(1));
					CoreLog->info("Database database is manually set to '{}'", getDatabaseConf().getDatabase());
				} else if (arg_parts.at(0).compare("--dbthreads") == 0) {
					int num = std::atoi(arg_parts.at(1).c_str());
					int threads = std::max(1, std::min(num, 10));
					getDatabaseConf().setMaxThreads(threads);
					CoreLog->info("Database max threads are manually set to '{}'", getDatabaseConf().getMaxThreads());
				} else {
					CoreLog->error("Unrecognised argument for test run '{}'", *it);
				}
			}
		}
		getGeneralConf().setTestRun();
	}
}

#define core_config_error(setting_name, default) \
CoreLog->error("No setting for '{}' in configuration file, defaulting to {}", setting_name, default);

bool Server::ProcessCommonConfiguration(libconfig::Config &cfg)
{
	std::string tmp_string{""};
	uint32_t tmp_value{0};

	if (cfg.lookupValue("bind_ip", tmp_string)) {
		getNetworkConf().setListenIp(tmp_string);
	} else {
		core_config_error("bind_ip", "127.0.0.1");
		getNetworkConf().setListenIp("127.0.0.1");
	}

	if (cfg.lookupValue("bind_port", tmp_value)) {
		getNetworkConf().setListenPort(tmp_value);
	} else {
		AuthLog->error("Invalid or non-existent configuration for 'bind_port', Halting...");
		return false;
	}

	if (cfg.lookupValue("network_threads", tmp_value)) {
		getNetworkConf().setMaxThreads(tmp_value);
	} else {
		core_config_error("network_threads", 1);
		getNetworkConf().setMaxThreads(1);
	}

	CoreLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.",
				  getNetworkConf().getListenIp(), getNetworkConf().getListenPort(), getNetworkConf().getMaxThreads());

	/**
	 * Database Configuration
	 * @brief
	 */
	if (!getGeneralConf().isTestRun()) {
		const libconfig::Setting &dbconf = cfg.getRoot()["database"];

		if (dbconf.lookupValue("hostname", tmp_string)) {
			getDatabaseConf().setHost(tmp_string);
		} else {
			core_config_error("hostname", "127.0.0.1");
			getDatabaseConf().setHost("127.0.0.1");
		}

		if (dbconf.lookupValue("port", tmp_value)) {
			getDatabaseConf().setPort(tmp_value);
		} else {
			core_config_error("hostname", 3306);
			getDatabaseConf().setPort(3306);
		}

		if (dbconf.lookupValue("database", tmp_string)) {
			getDatabaseConf().setDatabase(tmp_string);
		} else {
			core_config_error("database", "horizon");
			getDatabaseConf().setDatabase("horizon");
		}

		if (dbconf.lookupValue("username", tmp_string)) {
			getDatabaseConf().setUsername(tmp_string);
		} else {
			core_config_error("username", "horizon");
			getDatabaseConf().setUsername("horizon");
		}

		if (dbconf.lookupValue("password", tmp_string)) {
			getDatabaseConf().setPassword(tmp_string);
		} else {
			core_config_error("password", "horizon");
			getDatabaseConf().setPassword("horizon");
		}

		if (dbconf.lookupValue("connection_threads", tmp_value)) {
			getDatabaseConf().setMaxThreads(tmp_value);
		} else {
			core_config_error("connection_threads", 1);
			getDatabaseConf().setMaxThreads(1);
		}
	}

	/**
	 * Core I/O Thread Count
	 */
	if (cfg.lookupValue("global_io_threads", tmp_value)) {
		getGeneralConf().setGlobalIOThreads(tmp_value);
		CoreLog->info("Using {} threads for working on Global I/O Events.", getGeneralConf().getGlobalIOThreads());
	} else {
		CoreLog->info("I/O Thread configuration not found, defaulting to 2.");
		getGeneralConf().setGlobalIOThreads(2);
	}

	/**
	 * Core Update Interval.
	 */
	if (cfg.lookupValue("core_update_interval", tmp_value)) {
		getGeneralConf().setCoreUpdateInterval(tmp_value);
		CoreLog->info("Core update interval set to {}ms.", getGeneralConf().getCoreUpdateInterval());
	} else {
		CoreLog->info("Core update interval was not defined, defaulting to 500ms.");
		getGeneralConf().setCoreUpdateInterval(500);
	}

	return true;
}

#undef core_config_error

void Server::InitializeMySQLConnections()
{
	// Create a pool of MySQL connections
	mysql_connection_factory = boost::make_shared<MySQLConnectionFactory>(getDatabaseConf().getHost(), getDatabaseConf().getDatabase(), getDatabaseConf().getUsername(), getDatabaseConf().getPassword());
	mysql_pool = boost::make_shared<ConnectionPool<MySQLConnection>>(getDatabaseConf().getMaxThreads(), mysql_connection_factory);
}

void Server::InitializeCLI()
{
	if (getGeneralConf().isTestRun()) {
		CoreLog->info("Command line not supported during test-runs... skipping.");
		return;
	}

	m_CLIThread = std::thread(std::bind(&CLIThreadStart, this));
	InitializeCLICommands();
}

void Server::InitializeCLICommands()
{
	addCLIFunction("shutdown", std::bind(&Server::CLICmd_Shutdown, this));
}

void Server::ProcessCLICommands()
{
	CLICommand *command = nullptr;

	while (m_CLICmdQueue.next(command)) {
		bool ret = false;
		std::function<bool(void)> cmd_func = getCLIFunc(command->m_command);

		if (cmd_func) {
			ret = cmd_func();
		} else {
			CoreLog->info("Command '{}' not found!", command->m_command);
		}

		if (command->m_finish_func != nullptr)
			command->m_finish_func(command, ret);

		delete command;
	}
}

void Server::InitializeCore()
{
	std::shared_ptr<boost::asio::io_service> io_service = getIOService();
	std::shared_ptr<std::vector<std::thread>> thread_pool(new std::vector<std::thread>(), [io_service] (std::vector<std::thread> *del)
	{
		io_service->stop();
		for (std::thread &thr : *del)
			thr.join();
		delete del;
	});

	int global_thread_count = std::max(getGeneralConf().getGlobalIOThreads(), 1);

	for (int i = 0; i < global_thread_count; ++i) {
		thread_pool->push_back(std::thread(std::bind(&Server::IOServiceLoop, this)));
	}

	CoreLog->info("A Thread pool of {} global I/O threads have been spawned.", this->getGeneralConf().getGlobalIOThreads());

	/**
	 * MySQL Startup
	 */
	InitializeMySQLConnections();

	/**
	 * Initialize Commandline Interface
	 */
	InitializeCLI();

	while (!IsShuttingDown() && !getGeneralConf().isTestRun()) {
		ProcessCLICommands();
		std::this_thread::sleep_for(std::chrono::milliseconds(getGeneralConf().getCoreUpdateInterval()));
	}

	// Join the CLI Thread.
	if (!getGeneralConf().isTestRun())
		m_CLIThread.join();
}

void Server::IOServiceLoop()
{
	getIOService()->run();
}

const std::shared_ptr<boost::asio::io_service> &Server::getIOService() const
{
	return this->io_service;
}
