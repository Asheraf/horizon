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

struct network_configuration
{
	/* Listen IP */
	const std::string &getListenIp() const { return listen_ip; }
	void setListenIp(const std::string &listen_ip) { network_configuration::listen_ip = listen_ip; }
	/* Listen Port */
	uint16_t getListenPort() const { return listen_port; }
	void setListenPort(uint16_t listen_port) { network_configuration::listen_port = listen_port; }
	/* Max Threads */
	uint32_t getMaxThreads() const { return max_threads; }
	void setMaxThreads(uint32_t max_threads) { network_configuration::max_threads = max_threads; }

	std::string listen_ip; //< Listen IP
	uint16_t listen_port; //< Listen Port Number
	uint32_t max_threads; //< Maximum network threads.
};

struct database_configuration
{
	/* Database Host */
	const std::string &getHost() const { return host; }
	void setHost(const std::string &host) { database_configuration::host = host; }
	/* Username */
	const std::string &getUsername() const { return username; }
	void setUsername(const std::string &username) { database_configuration::username = username; }
	/* Password */
	const std::string &getPassword() const { return password; }
	void setPassword(const std::string &password) { database_configuration::password = password; }
	/* Database Name */
	const std::string &getDatabase() const { return database; }
	void setDatabase(const std::string &database) { database_configuration::database = database; }
	/* Maximum Connection Threadpool */
	int getMaxThreads() const { return max_threads; }
	void setMaxThreads(int max_threads) { database_configuration::max_threads = max_threads; }

	std::string host, username, password;
	std::string database;
	int max_threads;
};

struct general_server_configuration
{
	/* Minimal Load for Test Run */
	bool isTestRun() const { return minimal; };
	void setTestRun() { this->minimal = true; };
	/* Configuration File Path */
	const std::string &getConfigFilePath() const { return config_file_path; };
	void setConfigFilePath(const std::string &config_file_path) { this->config_file_path = config_file_path; };
	/* Configuration File Name */
	const std::string &getConfigFileName() const { return config_file_name; };
	void setConfigFileName(const std::string &config_file_name) { this->config_file_name = config_file_name; };
	/* Shutting Down Flags */
	bool IsShuttingDown() const { return is_shutting_down; };
	void setShuttingDown(int signal) { this->is_shutting_down = true; this->shutdown_signal = signal; };
	/* Shut Down Signal */
	int getShutdownSignal() const { return shutdown_signal; };
	void setShutdownSignal(int shutdown_signal) { this->shutdown_signal = shutdown_signal; };
	/* Maximum Core I/O Operations Threads */
	int getGlobalIOThreads() const { return global_io_threads; };
	void setGlobalIOThreads(int global_io_threads) { this->global_io_threads = global_io_threads; };
	/* Core Update Interval */
	int getCoreUpdateInterval() const { return core_update_interval; };
	void setCoreUpdateInterval(int core_update_interval) { this->core_update_interval = core_update_interval; };

	/* Minimal Test Run Flag */
	bool minimal;
	/* Configuration Files */
	std::string config_file_path;
	std::string config_file_name;
	bool is_shutting_down;                         ///< Flagged for a shutdown.
	int shutdown_signal;                           ///< Shutdown signal.
	int global_io_threads;                         ///< Maximum amount of Core Threads spawned to perform i/o run.
	int core_update_interval;                      ///< Core update interval timer.
};

#endif //HORIZON_GENERALSERVERCONFIGURATION_H
