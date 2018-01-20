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

#include "version.hpp"

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
					setDBUsername(arg_parts.at(1));
					CoreLog->info("Database user is manually set to '{}'", getDBUsername());
				} else if (arg_parts.at(0).compare("--dbpassword") == 0) {
					setDBPassword(arg_parts.at(1));
					CoreLog->info("Database password is manually set to '{}'", getDBPassword());
				} else if (arg_parts.at(0).compare("--dbhost") == 0) {
					setDBHost(arg_parts.at(1));
					CoreLog->info("Database host is manually set to '{}'", getDBHost());
				} else if (arg_parts.at(0).compare("--dbdatabase") == 0) {
					setDBDatabase(arg_parts.at(1));
					CoreLog->info("Database database is manually set to '{}'", getDBDatabase());
				} else if (arg_parts.at(0).compare("--dbthreads") == 0) {
					int num = std::atoi(arg_parts.at(1).c_str());
					int threads = std::max(1, std::min(num, 10));
					setDBMaxThreads(threads);
					CoreLog->info("Database max threads are manually set to '{}'", getDBMaxThreads());
				} else {
					CoreLog->error("Unrecognised argument for test run '{}'", *it);
				}
			}
		}
		this->setTestRun();
	}
}

void Server::InitializeMySQLConnections()
{
	// Create a pool of MySQL connections
	mysql_connection_factory = boost::make_shared<MySQLConnectionFactory>(getDBHost(), getDBDatabase(), getDBUsername(), getDBPassword());
	mysql_pool = boost::make_shared<ConnectionPool<MySQLConnection>>(getDBMaxThreads(), mysql_connection_factory);
}
