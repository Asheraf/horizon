//
// Created by SagunKho on 16/01/2018.
//

#include "Char.h"
#include "CharSocketMgr.h"

#include "../Packet.hpp"

#include <yaml-cpp/yaml.h>
#include <boost/asio.hpp>
#include <iostream>

using namespace std;

using boost::asio::ip::udp;

/* Create Socket Connection */
boost::asio::io_service *io_service;

CharMain::CharMain() : Server("Char", "../config/")
{
	config_file_name = "char-server.yaml";
}

CharMain::~CharMain()
{
}

/**
 * Prints the header for auth server.
 * @brief Appends the Core header.
 */
void CharMain::PrintHeader()
{
	CharLog->info("Character Server Initializing...");
}

void SignalHandler(const boost::system::error_code &error, int /*signalNumber*/)
{
	if (!error)
		io_service->stop();
}

/**
 * Read /config/char-server.yaml
 */
bool CharMain::ReadConfig()
{
	YAML::Node config;
	std::string filepath = Server::config_file_path + config_file_name;

	try {
		config = YAML::LoadFile(filepath);
	} catch (std::exception &err) {
		CharLog->error("Unable to read {}. ({})", filepath, err.what());
		return false;
	}

	/**
	 * Char Server Networking
	 * @brief Definitions of the authentication server networking configuration.
	 */
	if (config["BindIP"])
		netconf.listen_ip = config["BindIP"].as<std::string>();

	if (config["CharPort"])
		netconf.listen_port = config["CharPort"].as<uint16_t>();

	if (config["Network.Threads"])
		netconf.network_threads = config["Network.Threads"].as<uint32_t>();

	CharLog->info("Network configured to bind on tcp://{}:{} with a pool of {} threads.", netconf.listen_ip, netconf.listen_port, netconf.network_threads);

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
					CharLog->warn("Hostname not provided or invalid. Defaulting to '{}'...", hostname);
				} else {
					hostname = n["hostname"].as<std::string>();
				}

				if (!n["port"] || !n["port"].IsScalar()) {
					CharLog->warn("Port not provided or invalid. Defaulting to '{}'...", port);
				} else {
					port = n["port"].as<uint16_t>();
				}

				if (!n["database"] || !n["database"].IsScalar()) {
					CharLog->warn("Database not provided or invalid. Defaulting to '{}'...", database);
				} else {
					database = n["database"].as<std::string>();
				}

				if (!n["username"] || !n["username"].IsScalar()) {
					CharLog->warn("Username not provided or invalid. Defaulting to '{}'...", username);
				} else {
					username = n["username"].as<std::string>();
				}

				if (!n["password"] || !n["password"].IsScalar()) {
					CharLog->warn("Password not provided or invalid. Defaulting to '{}'...", password);
				} else {
					password = n["password"].as<std::string>();
				}

				if (!n["connection_threads"] || !n["connection_threads"].IsScalar()) {
					CharLog->warn("Connection Threads not provided or invalid. Defaulting to '{}'...", connection_threads);
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
						CharLog->warn("Invalid charset '{}' provided database. Defaulting to '{}'...", charset, charset);
					} else {
						charset = charset;
					}
				}

				break;
			default:
				CharLog->error("Unsupported node type in element {} for '{}'.", n.as<std::string>());
				return false;
		}
	} else {
		CharLog->error("Char database configuration not provided in '{}'.", filepath);
		return false;
	}

	/**
	 * Logging Configuration
	 * @brief
	 */
	if (config["log"])
		log.enabled = config["log"].as<bool>();

	CharLog->info("Done reading {} configurations in '{}'.", config.size(), config_file_path + config_file_name);

	return true;
}

int main(int argc, const char * argv[])
{
	/* Header */
	CharServer->PrintHeader();

	/*
	 * Read Configuration Settings for
	 * the Character Server.
	 */
	if (!CharServer->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	io_service = new boost::asio::io_service();

	// Start Character Network
	sCharSocketMgr.StartNetwork(*io_service,
								CharServer->getNetConf().listen_ip, CharServer->getNetConf().listen_port, CharServer->getNetConf().network_threads);

	boost::asio::signal_set signals(*io_service, SIGINT, SIGTERM);

	signals.async_wait(SignalHandler);

	/*
	 * I/O Run Loop
	 * @brief Main loop for I/O Service.
	 */
	io_service->run();

	/*
	 * Core Cleanup
	 */
	CharLog->info("Server shutting down...");

	/* Stop Network */
	sCharSocketMgr.StopNetwork();

	signals.cancel();

	delete io_service;

	return 0;
}