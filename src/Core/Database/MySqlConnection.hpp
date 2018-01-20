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
 * Copyright 2013 Active911 Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http: *www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HORIZON_MYSQLCONNECTION_H
#define HORIZON_MYSQLCONNECTION_H
#include "ConnectionPool.hpp"
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
#include <boost/shared_ptr.hpp>

class MySQLConnection : public Connection
{
public:
	~MySQLConnection()
	{
		if (this->sql_connection) {
			DBLog->info("Terminating mysql connections.");
			this->sql_connection->close();
			this->sql_connection.reset(); 	// Release and destruct
		}

	};

	boost::shared_ptr<sql::Connection> sql_connection;
};


class MySQLConnectionFactory : public ConnectionFactory
{
public:
	MySQLConnectionFactory(std::string &host, std::string &database, std::string &username, std::string &password)
	: host(host), database(database), username(username), password(password)
	{
		// Connection Factory.
	}

	// Any exceptions thrown here should be caught elsewhere
	boost::shared_ptr<Connection> create()
	{
		// Get the driver
		sql::Driver *driver = nullptr;
		driver = get_driver_instance();

		// Create the connection
		boost::shared_ptr<MySQLConnection> conn(new MySQLConnection());

		try {
			// Connect
			conn->sql_connection = boost::shared_ptr<sql::Connection>(driver->connect(this->host, this->username, this->password));
			// Set Default Schema
			conn->sql_connection->setSchema(database);
		} catch (sql::SQLException &e) {
			DBLog->error("{}", e.what());
		}

		DBLog->info("Initiated MySQL connection to database '{}' for user '{}' on host '{}'.", this->database, this->username, this->host);

		return boost::static_pointer_cast<Connection>(conn);
	}

private:
	std::string host;
	std::string database;
	std::string username;
	std::string password;
};



#endif //HORIZON_MYSQLCONNECTION_H
