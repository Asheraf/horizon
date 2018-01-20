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
#include "AuthSocketMgr.hpp"

#include "Server/Packet.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

using boost::asio::ip::udp;

/* Create Socket Connection */
boost::asio::io_service *io_service;

AuthMain::AuthMain()
: Server("Auth", "../config/", "auth-server.yaml")
{
	account_online_list = std::make_shared<OnlineListType>();
}

AuthMain::~AuthMain()
{
}

/**
 * Prints the header for auth server.
 * @brief Appends the Core header.
 */
void AuthMain::PrintHeader()
{
	AuthLog->info("Authentication Server Initializing...");
}

/**
 * Read /config/auth-server.yaml
 */
bool AuthMain::ReadConfig()
{
	YAML::Node config;
	std::string filepath = this->general_config.config_file_path + this->general_config.config_file_name;

	try {
		config = YAML::LoadFile(filepath);
	} catch (std::exception &err) {
		AuthLog->error("Unable to read {}. ({})", filepath, err.what());
		return false;
	}

	/**
	 * Auth Server Networking
	 * @brief Definitions of the authentication server networking configuration.
	 */
	if (config["BindIP"])
		this->general_config.network.listen_ip = config["BindIP"].as<std::string>();

	if (config["AuthPort"])
		this->general_config.network.listen_port = config["AuthPort"].as<uint16_t>();

	if (config["Network.Threads"])
		this->general_config.network.max_threads = config["Network.Threads"].as<uint32_t>();

	AuthLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.",
	              this->general_config.network.listen_ip, this->general_config.network.listen_port, this->general_config.network.max_threads);

	/**
	 * Additional Configuration
	 * @brief
	 */
    if (config["pass_hash_method"]) {
		this->auth_config.pass_hash_method = static_cast<HashingMethods>(config["pass_hash_method"].as<int>());
	}

	if (this->auth_config.pass_hash_method == PASS_HASH_NONE)
		AuthLog->warn("Passwords are stored in plain text! This is not recommended!");

	/**
	 * Database Configuration
	 * @brief
	 */
	if (config["database"]) {
		YAML::Node n = config["database"];
		std::string hostname = "localhost", database = "ragnarok", username = "ragnarok", password = "ragnarok";
		uint16_t port = 3306;
		uint8_t connection_threads = 2;

		switch (n.Type())
		{
		case YAML::NodeType::Map:
		{
			if (!AuthServer->isTestRun()) {
				if (!n["hostname"] || !n["hostname"].IsScalar()) {
					AuthLog->warn("Hostname not provided or invalid. Defaulting to '{}'...", hostname);
				} else {
					hostname = n["hostname"].as<std::string>();
				}
			} else {
				hostname = "mysql";
			}

			if (!n["port"] || !n["port"].IsScalar()) {
				AuthLog->warn("Port not provided or invalid. Defaulting to '{}'...", port);
			} else {
				port = n["port"].as<uint16_t>();
			}

			if (!n["database"] || !n["database"].IsScalar()) {
				AuthLog->warn("Database not provided or invalid. Defaulting to '{}'...", database);
			} else {
				database = n["database"].as<std::string>();
			}

			if (!n["username"] || !n["username"].IsScalar()) {
				AuthLog->warn("Username not provided or invalid. Defaulting to '{}'...", username);
			} else {
				username = n["username"].as<std::string>();
			}

			if (!n["password"] || !n["password"].IsScalar()) {
				AuthLog->warn("Password not provided or invalid. Defaulting to '{}'...", password);
			} else {
				password = n["password"].as<std::string>();
			}

			if (!n["connection_threads"] || !n["connection_threads"].IsScalar()) {
				AuthLog->warn("Connection Threads not provided or invalid. Defaulting to '{}'...", connection_threads);
			} else {
				connection_threads = (uint8_t) n["connection_threads"].as<int>();
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
					AuthLog->warn("Invalid charset '{}' provided database. Defaulting to '{}'...", charset, charset);
				} else {
					charset = charset;
				}
			}

			AuthServer->setDBHost(hostname);
			AuthServer->setDBDatabase(database);
			AuthServer->setDBUsername(username);
			AuthServer->setDBPassword(password);

			// Create a pool of MySQL connections
			mysql_connection_factory = boost::make_shared<MySQLConnectionFactory>(hostname, database, username, password);
			mysql_pool = boost::make_shared<ConnectionPool<MySQLConnection>>(connection_threads, mysql_connection_factory);
		}
			break;
		default:
			AuthLog->error("Unsupported node type in element {} for '{}'.", n.as<std::string>());
			return false;
		}
	} else {
		AuthLog->error("Auth database configuration not provided in '{}'.", filepath);
		return false;
	}

	/**
	 * Logging Configuration
	 */
	if (config["log"])
		this->auth_config.logs.enabled = config["log"].as<bool>();

	if (config["login_max_tries"])
		this->auth_config.logs.login_max_tries = config[ "login_max_tries" ].as<uint32_t>();

	if (config["login_fail_ban_time"])
		this->auth_config.logs.login_fail_ban_time = config["login_fail_ban_time"].as<time_t>();

	if (config["login_fail_check_time"])
		this->auth_config.logs.login_fail_check_time = config["login_fail_check_time"].as<time_t>();

	if (this->auth_config.logs.enabled) {
		AuthLog->info("Logging is {}.", this->auth_config.logs.enabled ? "enabled" : "disabled", filepath);
		AuthLog->info("Failed logins exceeding {} tries every {} seconds will be banned for {} seconds.",
		              this->auth_config.logs.login_fail_check_time, this->auth_config.logs.login_max_tries, this->auth_config.logs.login_fail_ban_time);
	}

	/**
	 * Date Format for clients
	 * @brief
	 */
	if (config["date_format"])
		this->auth_config.date_format = config["date_format"].as<std::string>();

	if (config["client_version"])
		this->auth_config.client_version = config["client_version"].as<uint32_t>();

	AuthLog->info("Done reading {} configurations in '{}'.", config.size(), this->general_config.config_file_path + this->general_config.config_file_name);

	return true;
}

std::shared_ptr<OnlineListType> AuthMain::getAccountOnlineList() const
{
	return account_online_list;
}

void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error)
		io_service->stop();
}

/**
 * Main Runtime Method
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char * argv[])
{
	/* Header */
	AuthServer->PrintHeader();

	if (argc > 1)
		AuthServer->ParseRuntimeArguments(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Authentication Server.
	 */
	if (!AuthServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	io_service = new boost::asio::io_service();

	// Start Auth Network
	sAuthSocketMgr.StartNetwork(*io_service,
		AuthServer->getNetConf().listen_ip, AuthServer->getNetConf().listen_port, AuthServer->getNetConf().max_threads);

	boost::asio::signal_set signals(*io_service, SIGINT, SIGTERM);

	signals.async_wait(SignalHandler);

	/*
	 * I/O Run Loop
	 * @brief Main loop for I/O Service.
	 */
	if (!AuthServer->isTestRun())
		io_service->run();

	/*
	 * Core Cleanup
	 */
	AuthLog->info("Server shutting down...");

	/* Stop Network */
	sAuthSocketMgr.StopNetwork();

	signals.cancel();

	delete io_service;

	return 0;
}
