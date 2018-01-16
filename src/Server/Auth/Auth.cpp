//
//  main.cpp
//  XYZAuth
//
//  Created by Sagun Khosla on 11/6/17.
//  Copyright © 2017 Horizon. All rights reserved.
//

#include "Auth.hpp"
#include "AuthSocketMgr.hpp"

#include "../Packet.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <iostream>

using namespace std;

using boost::asio::ip::udp;

/* Create Socket Connection */
boost::asio::io_service *io_service;

AuthMain::AuthMain() : Server("Auth", "../config/")
{
	auth_file_name = "auth-server.yaml";
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
	std::string filepath = Server::config_file_path + auth_file_name;

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
		netconf.listen_ip = config["BindIP"].as<std::string>();

	if (config["AuthPort"])
		netconf.listen_port = config["AuthPort"].as<uint16_t>();

	if (config["Network.Threads"])
		netconf.network_threads = config["Network.Threads"].as<uint32_t>();

	AuthLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.", netconf.listen_ip, netconf.listen_port, netconf.network_threads);

	/**
	 * Additional Configuration
	 * @brief
	 */
    if (config["pass_hash_method"]) {
		pass_hash_method = static_cast<HashingMethods>(config["pass_hash_method"].as<int>());
	}

	if (pass_hash_method == PASS_HASH_NONE)
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
			if (!n["hostname"] || !n["hostname"].IsScalar()) {
				AuthLog->warn("Hostname not provided or invalid. Defaulting to '{}'...", hostname);
			} else {
				hostname = n["hostname"].as<std::string>();
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
	 * Credential length limit.
	 * @brief
	 */
	if (config["username_length"]) {
		YAML::Node n = config["username_length"];
		if (!n || n.Type() != YAML::NodeType::Sequence) {
			AuthLog->error("Invalid format provided for 'username_length' configuration. Defaulting to {} and {}",
						   credentials.min_username_length, credentials.max_username_length);
		} else {
			uint8_t min = (uint8_t) n[0].as<int>(), max = (uint8_t) n[1].as<int>();

			if (min < credentials.min_username_length) {
				AuthLog->error("Minimum required username length cannot be less than {}. Defaulting...", credentials.min_username_length);
			} else {
				credentials.min_username_length = min;
			}

			if (max > credentials.max_username_length) {
				AuthLog->error("Maximum username length cannot exceed {}. Defaulting...", credentials.max_username_length);
			} else {
				credentials.max_username_length = max;
			}
		}
	}

	if (config["password_length"]) {
		YAML::Node n = config["password_length"];
		if (!n || n.Type() != YAML::NodeType::Sequence) {
			AuthLog->error("Invalid format provided for 'password_length' configuration. Defaulting to {} and {}",
						   credentials.min_password_length, credentials.max_password_length);
		} else {
			uint8_t min = (uint8_t) n[0].as<int>(), max = (uint8_t) n[1].as<int>();

			if (min < credentials.min_password_length) {
				AuthLog->error("Minimum required password length cannot be less than {}. Defaulting...", credentials.min_password_length);
			} else {
				credentials.min_password_length = min;
			}

			if (max > credentials.max_password_length) {
				AuthLog->error("Maximum password length cannot exceed {}. Defaulting...", credentials.max_password_length);
			} else {
				credentials.max_password_length = max;
			}
		}
	}

	/**
	 * Logging Configuration
	 * @brief
	 */
	if (config["log"])
		log.enabled = config["log"].as<bool>();

	if (config["login_max_tries"])
		log.login_max_tries = config[ "login_max_tries" ].as<uint32_t>();

	if (config["login_fail_ban_time"])
		log.login_fail_ban_time = config["login_fail_ban_time"].as<time_t>();

	if (config["login_fail_check_time"])
		log.login_fail_check_time = config["login_fail_check_time"].as<time_t>();

	if (log.enabled) {
		AuthLog->info("Logging is {}.", log.enabled ? "enabled" : "disabled", filepath);
		AuthLog->info("Failed logins exceeding {} tries every {} seconds will be banned for {} seconds.",
					  log.login_fail_check_time, log.login_max_tries, log.login_fail_ban_time);
	}

	/**
	 * Date Format for clients
	 * @brief
	 */
	if (config["date_format"])
		date_format = config["date_format"].as<std::string>();

	if (config["client_version"])
		client_version = config["client_version"].as<uint32_t>();

	if (config["dns_blacklist"]["enabled"]) {
		YAML::Node n = config["dns_blacklist"]["servers"];

		if (!n || n.Type() != YAML::NodeType::Sequence) {
			AuthLog->error("DNS blacklisting has been enabled, but no servers are listed! Disabling...");
		} else {
			for (size_t i = 0; i < n.size(); i++)
				dns_blacklist.push_back(n[i].as<std::string>());
		}
	}

	AuthLog->info("Done reading {} configurations in '{}'.", config.size(), config_file_path + auth_file_name);

	return true;
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
	bool minimal = false;

	/* Header */
	AuthServer->PrintHeader();

	if (argc >= 2) {
		if (strcmp(argv[1], "--test-run") == 0) {
			AuthLog->info("Test run initiated.");
			minimal = true;
		}
	}

	/*
	 * Read Configuration Settings for
	 * the Authentication Server.
	 */
	if (!AuthServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	io_service = new boost::asio::io_service();

	// Start Auth Network
	sAuthSocketMgr.StartNetwork(*io_service,
		AuthServer->getNetConf().listen_ip, AuthServer->getNetConf().listen_port, AuthServer->getNetConf().network_threads);

	boost::asio::signal_set signals(*io_service, SIGINT, SIGTERM);

	signals.async_wait(SignalHandler);

	/*
	 * I/O Run Loop
	 * @brief Main loop for I/O Service.
	 */
	if (!minimal)
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
