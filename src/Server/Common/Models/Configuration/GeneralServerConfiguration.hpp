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

#ifndef HORIZON_GENERALSERVERCONFIGURATION_H
#define HORIZON_GENERALSERVERCONFIGURATION_H

#include <cstring>

enum client_types {
	CLIENT_TYPE_RAGEXE    = 0,
	CLIENT_TYPE_RAGEXE_RE = 1,
	CLIENT_TYPE_ZERO      = 2,
	CLIENT_TYPE_SAKRAY    = 3,
	CLIENT_TYPE_AD        = 4,
	CLIENT_TYPE_MAX
};
struct network_configuration
{
	/* Listen IP */
	const std::string &get_listen_ip() const { return listen_ip; }
	void set_listen_ip(const std::string &listen_ip) { network_configuration::listen_ip = listen_ip; }
	/* Listen Port */
	uint16_t get_listen_port() const { return listen_port; }
	void set_listen_port(uint16_t listen_port) { network_configuration::listen_port = listen_port; }
	/* Max Threads */
	uint32_t get_network_thread_count() const { return max_threads; }
	void set_network_thread_count(uint32_t max_threads) { network_configuration::max_threads = max_threads; }

	std::string listen_ip; //< Listen IP
	uint16_t listen_port; //< Listen Port Number
	uint32_t max_threads; //< Maximum network threads.
};

struct database_configuration
{
	/* Database Host */
	const std::string &get_host() const { return host; }
	void set_host(const std::string &host) { database_configuration::host = host; }
	/* Port */
	const uint16_t &get_port() const { return _port; }
	void set_port(uint16_t port) { _port = port; }
	/* Username */
	const std::string &get_username() const { return username; }
	void set_username(const std::string &username) { database_configuration::username = username; }
	/* Password */
	const std::string &get_password() const { return password; }
	void set_password(const std::string &password) { database_configuration::password = password; }
	/* Database Name */
	const std::string &get_database() const { return database; }
	void set_database(const std::string &database) { database_configuration::database = database; }
	/* Maximum Connection Threadpool */
	int get_db_thread_count() const { return max_threads; }
	void set_db_thread_count(int max_threads) { database_configuration::max_threads = max_threads; }

	std::string host{""}, username{""}, password{""};
	std::string database{""};
	int max_threads{1};
	uint16_t _port{0};
};

struct general_server_configuration
{
	/* Minimal Load for Test Run */
	bool is_test_run() const { return minimal; };
	void set_test_run() { this->minimal = true; };
	/* Configuration File Path */
	const std::string &get_config_file_path() const { return config_file_path; };
	void set_config_file_path(const std::string &config_file_path) { this->config_file_path = config_file_path; };
	/* Configuration File Name */
	const std::string &get_config_file_name() const { return config_file_name; };
	void set_config_file_name(const std::string &config_file_name) { this->config_file_name = config_file_name; };
	/* Shut Down Signal */
	int get_shutdown_signal() const { return shutdown_signal; };
	void set_shutdown_signal(int shutdown_signal) { this->shutdown_signal = shutdown_signal; };
	/* Maximum Core I/O Operations Threads */
	int get_io_thread_count() const { return global_io_threads; };
	void set_io_thread_count(int global_io_threads) { this->global_io_threads = global_io_threads; };
	/* Core Update Interval */
	int get_core_update_interval() const { return core_update_interval; };
	void set_core_update_interval(int core_update_interval) { this->core_update_interval = core_update_interval; };
	/* Client Type */
	uint32_t get_client_type() const { return _client_type; }
	void set_client_type(uint32_t type) { _client_type = type; }
	/* Packet Version */
	uint32_t get_packet_version() const { return _packet_version; }
	void set_packet_version(uint32_t version) { _packet_version = version; }

	/* Minimal Test Run Flag */
	bool minimal{false};
	/* Configuration Files */
	std::string config_file_path{""};
	std::string config_file_name{""};
	int shutdown_signal;                              ///< Shutdown signal.
	int global_io_threads{1};                         ///< Maximum amount of Core Threads spawned to perform i/o run.
	int core_update_interval{500};                    ///< Core update interval timer.
	int _client_type{0};                              ///< Client Type to use (Ragexe, RagexeRE, Zero, Sakray or AD)
	int _packet_version{0};                           ///< Maximum client version allowed to connect.
};

#endif //HORIZON_GENERALSERVERCONFIGURATION_H
