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

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/make_shared.hpp>
#include <Server/Common/CLI/CommandLineInterface.hpp>

#include "version.hpp"

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

void Server::ParseRuntimeArguments(const char *argv[], int argc)
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

bool Server::ProcessCommonConfiguration(YAML::Node &config)
{
	std::string hostname = "localhost", database = "ragnarok", username = "ragnarok", password = "ragnarok";
	uint16_t port = 3306;
	int connection_threads = 2;

	try {
		/**
		 * Auth Server Networking
		 * @brief Definitions of the authentication server networking configuration.
		 */
		if (config["BindIP"])
			getNetworkConf().setListenIp(config["BindIP"].as<std::string>());

		if (config["BindPort"])
			getNetworkConf().setListenPort(config["BindPort"].as<uint16_t>());

		if (config["Network.Threads"])
			getNetworkConf().setMaxThreads(config["Network.Threads"].as<uint32_t>());

		CoreLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.",
		              getNetworkConf().getListenIp(), getNetworkConf().getListenPort(), getNetworkConf().getMaxThreads());

		/**
		 * Database Configuration
		 * @brief
		 */
		if (!getGeneralConf().isTestRun() && config["database"]) {
			YAML::Node n = config["database"];

			switch (n.Type())
			{
			case YAML::NodeType::Map:
			{
				if (!n["hostname"] || !n["hostname"].IsScalar()) {
					CoreLog->warn("Hostname not provided or invalid. Defaulting to '{}'...", hostname);
				} else {
					hostname = n["hostname"].as<std::string>();
				}

				if (!n["port"] || !n["port"].IsScalar()) {
					CoreLog->warn("Port not provided or invalid. Defaulting to '{}'...", port);
				} else {
					port = n["port"].as<uint16_t>();
				}

				if (!n["database"] || !n["database"].IsScalar()) {
					CoreLog->warn("Database not provided or invalid. Defaulting to '{}'...", database);
				} else {
					database = n["database"].as<std::string>();
				}

				if (!n["username"] || !n["username"].IsScalar()) {
					CoreLog->warn("Username not provided or invalid. Defaulting to '{}'...", username);
				} else {
					username = n["username"].as<std::string>();
				}

				if (!n["password"] || !n["password"].IsScalar()) {
					CoreLog->warn("Password not provided or invalid. Defaulting to '{}'...", password);
				} else {
					password = n["password"].as<std::string>();
				}

				if (!n["connection_threads"] || !n["connection_threads"].IsScalar()) {
					CoreLog->warn("Connection Threads not provided or invalid. Defaulting to '{}'...", connection_threads);
				} else {
					connection_threads = n["connection_threads"].as<int>();
				}

				if (n["charset"] || n["charset"].IsScalar()) {
					std::string charset = n["charset"].as<std::string>();

					std::vector<std::string> sets = {
						"dec8", "cp850", "hp8", "koi8r", "latin1", "latin2", "swe7", "ascii",
						"ujis", "sjis", "hebrew", "tis620", "euckr", "koi8u", "gb2312", "greek",
						"cp1250", "gbk", "latin5", "armscii8", "utf8", "ucs2", "cp866", "keybcs2",
						"macce", "macroman", "cp852", "latin7", "utf8mb4", "cp1251", "utf16", "cp1256",
						"cp1257", "utf32", "binary", "geostd8", "cp932", "eucjpms"
					};

					if (std::find(sets.begin(), sets.end(), charset) == sets.end()) {
						CoreLog->warn("Invalid charset '{}' provided database. Defaulting to '{}'...", charset, charset);
					} else {
						charset = charset;
					}
				}
			}
				break;
			default:
				CoreLog->error("Unsupported node type in element {} for '{}'.", n.as<std::string>());
				return false;
			}
			/**
			 * Set MySQL Information.
			 */
			getDatabaseConf().setHost(hostname);
			getDatabaseConf().setDatabase(database);
			getDatabaseConf().setUsername(username);
			getDatabaseConf().setPassword(password);
			getDatabaseConf().setMaxThreads(connection_threads);
		} else if (!getGeneralConf().isTestRun()) {
			CoreLog->error("Database configuration not provided in '{}'.", getGeneralConf().getConfigFilePath() + getGeneralConf().getConfigFileName());
			return false;
		}

		/**
		 * Core I/O Thread Count
		 */
		if (config["global_io_threads"]) {
			this->getGeneralConf().setGlobalIOThreads(config["global_io_threads"].as<uint32_t>());
			CoreLog->info("Using {} threads for working on core-wide I/O Services.", this->getGeneralConf().getGlobalIOThreads());
		} else {
			CoreLog->info("I/O Thread configuration not found, defaulting to 2.");
			this->getGeneralConf().setGlobalIOThreads(2);
		}

		/**
		 * Core Update Interval.
		 */
		if (config["core_update_interval"]) {
			this->getGeneralConf().setCoreUpdateInterval(config["core_update_interval"].as<uint32_t>());
			CoreLog->info("Core update interval set to {}ms.", this->getGeneralConf().getCoreUpdateInterval());
		} else {
			CoreLog->info("Core update interval was not defined, defaulting to 500ms.");
			this->getGeneralConf().setCoreUpdateInterval(500);
		}
	} catch (YAML::Exception &e) {
		CoreLog->error("{}", e.what());
		return false;
	}

	return true;
}

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
