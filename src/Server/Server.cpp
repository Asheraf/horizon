//
//  server.cpp
//  Horizon
//
//  Created by SagunKho on 11/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#include "Server.hpp"
#include <iostream>

#include "version.h"

/* Public */
Server::Server(std::string name, std::string config_file_path)
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

	this->config_file_path = config_file_path;
}

Server::~Server()
{
}
