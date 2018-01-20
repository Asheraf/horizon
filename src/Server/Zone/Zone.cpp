/**           _   _            _
 *          | | | |          (_)
 *          | |_| | ___  _ __ _ _______  _ __
 *          |  _  |/ _ \| '__| |_  / _ \| '_ \
 *          | | | | (_) | |  | |/ / (_) | | | |
 *          \_| |_/\___/|_|  |_/___\___/|_| |_|
 *
 * This file is part of Horizon (c).
 * Copyright (c) 2018 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla. (sagunxp@gmail.com)
 *
 * Under a proprietary license this file is not for use
 * or viewing without permission.
 ****************************************************/

#include "Zone.hpp"
#include "ZoneSocketMgr.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <iostream>
#include <boost/make_shared.hpp>
#include <Server/Server.hpp>


using namespace std;

using boost::asio::ip::udp;

/* Create Socket Connection */
boost::asio::io_service *io_service;

ZoneMain::ZoneMain() : Server("Zone", "../config/", "zone-server.yaml")
{
}

ZoneMain::~ZoneMain()
{
}

/**
 * Prints the header for auth server.
 * @brief Appends the Core header.
 */
void ZoneMain::PrintHeader()
{
	ZoneLog->info("Zone Server Initializing...");
}

void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error)
		io_service->stop();
}

/**
 * Read /config/zone-server.yaml
 */
bool ZoneMain::ReadConfig()
{
	YAML::Node config;
	std::string filepath = this->general_config.config_file_path + this->general_config.config_file_name;

	try {
		config = YAML::LoadFile(filepath);
	} catch (std::exception &err) {
		ZoneLog->error("Unable to read {}. ({})", filepath, err.what());
		return false;
	}

	/**
	 * Zone Server Networking
	 * @brief Definitions of the authentication server networking configuration.
	 */
	if (config["BindIP"])
		this->general_config.network.listen_ip = config["BindIP"].as<std::string>();

	if (config["ZonePort"])
		this->general_config.network.listen_port = config["ZonePort"].as<uint16_t>();

	if (config["Network.Threads"])
		this->general_config.network.max_threads = config["Network.Threads"].as<uint32_t>();

	ZoneLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.",
	              this->general_config.network.listen_ip, this->general_config.network.listen_port, this->general_config.network.max_threads);

	/**
	 * Database Configuration
	 * @brief
	 */
	if (config["database"]) {
		YAML::Node n = config["database"];
		std::string hostname = "localhost", database = "ragnarok", username = "ragnarok", password = "ragnarok";
		uint16_t port = 3306;
		uint8_t connection_threads = 2;

		if (n.Type() != YAML::NodeType::Map) {
			ZoneLog->error("Unsupported node type in element {} for '{}'.", n.as<std::string>());
			return false;
		}

		if (!ZoneServer->isTestRun()) {
			if (!n["hostname"] || !n["hostname"].IsScalar()) {
				ZoneLog->warn("Hostname not provided or invalid. Defaulting to '{}'...", hostname);
			} else {
				hostname = n["hostname"].as<std::string>();
			}
		} else {
			hostname = "mysql";
		}

		if (!n["port"] || !n["port"].IsScalar()) {
			ZoneLog->warn("Port not provided or invalid. Defaulting to '{}'...", port);
		} else {
			port = n["port"].as<uint16_t>();
		}

		if (!n["database"] || !n["database"].IsScalar()) {
			ZoneLog->warn("Database not provided or invalid. Defaulting to '{}'...", database);
		} else {
			database = n["database"].as<std::string>();
		}

		if (!n["username"] || !n["username"].IsScalar()) {
			ZoneLog->warn("Username not provided or invalid. Defaulting to '{}'...", username);
		} else {
			username = n["username"].as<std::string>();
		}

		if (!n["password"] || !n["password"].IsScalar()) {
			ZoneLog->warn("Password not provided or invalid. Defaulting to '{}'...", password);
		} else {
			password = n["password"].as<std::string>();
		}

		if (!n["connection_threads"] || !n["connection_threads"].IsScalar()) {
			ZoneLog->warn("Connection Threads not provided or invalid. Defaulting to '{}'...", connection_threads);
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
				ZoneLog->warn("Invalid charset '{}' provided database. Defaulting to '{}'...", charset, charset);
			} else {
				charset = charset;
			}
		}

		ZoneServer->setDBHost(hostname);
		ZoneServer->setDBDatabase(database);
		ZoneServer->setDBUsername(username);
		ZoneServer->setDBPassword(password);

		// Create a pool of mysql connections.
		mysql_connection_factory = boost::make_shared<MySQLConnectionFactory>(hostname, database, username, password);
		mysql_pool = boost::make_shared<ConnectionPool<MySQLConnection>>(connection_threads, mysql_connection_factory);
	} else {
		ZoneLog->error("Zone database configuration not provided in '{}'.", filepath);
		return false;
	}

	/**
	 * Logging Configuration
	 * @brief
	 */
	if (config["log"])
		this->logs.enabled = config["log"].as<bool>();

	ZoneLog->info("Done reading {} configurations in '{}'.", config.size(), this->general_config.config_file_path + this->general_config.config_file_name);

	return true;
}

int main(int argc, const char * argv[])
{
	/* Header */
	ZoneServer->PrintHeader();

	if (argc > 1)
		ZoneServer->ParseRuntimeArguments(argv, argc);

	/*
	 * Read Configuration Settings for
	 * the Zoneacter Server.
	 */
	if (!ZoneServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	io_service = new boost::asio::io_service();

	// Start Zoneacter Network
	sZoneSocketMgr.StartNetwork(*io_service,
								ZoneServer->getNetConf().listen_ip, ZoneServer->getNetConf().listen_port, ZoneServer->getNetConf().max_threads);

	boost::asio::signal_set signals(*io_service, SIGINT, SIGTERM);

	signals.async_wait(SignalHandler);

	/*
	 * I/O Run Loop
	 * @brief Main loop for I/O Service.
	 */
	if (!ZoneServer->isTestRun())
		io_service->run();

	/*
	 * Core Cleanup
	 */
	ZoneLog->info("Server shutting down...");

	/* Stop Network */
	sZoneSocketMgr.StopNetwork();

	signals.cancel();

	delete io_service;

	return 0;
}