//
//  server.hpp
//  Horizon
//
//  Created by SagunKho on 11/06/2017.
//  Copyright © 2017 Horizon. All rights reserved.
//

#ifndef HORIZON_SERVER_HPP
#define HORIZON_SERVER_HPP

#include "Logging/Logger.hpp"

#include <cstdio>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Server
{
public:
	Server(std::string name, std::string config_file_path);
	~Server();

protected:
	std::string config_file_path;
};

#endif /* HORIZON_SERVER_HPP */
