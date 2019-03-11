/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun K. (sagunxp@gmail.com)
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#ifndef HORIZON_SERVER_HPP
#define HORIZON_SERVER_HPP

#include "Logging/Logger.hpp"
#include "CLI/CLICommand.hpp"
#include "Core/Multithreading/ThreadSafeQueue.hpp"
#include "Models/Configuration/GeneralServerConfiguration.hpp"
#include <mysqlx/xdevapi.h>

#include <cstdio>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <sol.hpp>

using boost::asio::ip::tcp;

enum shutdown_stages
{
	SHUTDOWN_NOT_STARTED      = 0,
	SHUTDOWN_INITIATED        = 1,
	SHUTDOWN_CLEANUP_COMPLETE = 2,
	SHUTDOWN_COMPLETE         = 3
};

class Server
{
public:
	Server(std::string name, std::string config_file_path, std::string config_file_name);
	~Server();

	void parse_exec_args(const char *argv[], int argc);

	/* Shutting Down Flags */
	shutdown_stages get_shutdown_stage() const { return _shutdown_stage.load(); };
	void set_shutdown_stage(shutdown_stages new_stage)
	{
		_shutdown_stage.exchange(new_stage);
	};

	void set_shutdown_signal(int signal) { _shutdown_signal.exchange(signal); }

	/* Core I/O Service*/
	boost::asio::io_service &get_io_service();
	/* General Configuration */
	struct general_server_configuration &general_conf() { return this->general_config; }
	/* Network Configuration */
	network_configuration &network_conf() { return network_config; };
	void setNetwork(const network_configuration &network) { this->network_config = network; };
	/* Database Configuration */
	database_configuration &database_conf() { return database_config; }

	/**
	 * Processing Functions
	 */
	/* Common Configuration */
	bool parse_common_configs(sol::table &cfg);
	/* Initialize Core */
	virtual void initialize_core();
	virtual void finalize_core();
	/* Mysql Threads */
	void initialize_mysql();
	/* Command Line Interface */
	void initialize_command_line();

	virtual void initialize_cli_commands();
	void process_cli_commands();
	void queue_cli_command(CLICommand &&cmdMgr) { _cli_cmd_queue.push(std::move(cmdMgr)); }
	void add_cli_command_func(std::string cmd, std::function<bool(void)> func) { _cli_function_map.insert(std::make_pair(cmd, func)); };

	/* CLI Function getter */
	std::function<bool(void)> get_cli_command_func(std::string &cmd)
	{
		auto it = _cli_function_map.find(cmd);
		return (it != _cli_function_map.end()) ? it->second : nullptr;
	}

	/**
	 * CLI Commands
	 */
	bool clicmd_shutdown()
	{
		set_shutdown_stage(SHUTDOWN_INITIATED);
		set_shutdown_signal(SIGTERM);
		return true;
	}

	std::shared_ptr<mysqlx::Client> get_mysql_client() { return _mysql_client; }

protected:
	/* General Configuration */
	struct general_server_configuration general_config;
	/* Network Configuration */
	struct network_configuration network_config;
	/* Database Configuration */
	struct database_configuration database_config;
	/* MySQL Client */
	std::shared_ptr<mysqlx::Client> _mysql_client;
	// CLI command holder to be thread safe
	ThreadSafeQueue<CLICommand> _cli_cmd_queue;
	std::thread _cli_thread;
	boost::thread_group _global_thread_group;
	std::atomic<shutdown_stages> _shutdown_stage;
	std::atomic<int> _shutdown_signal;
	std::unordered_map<std::string, std::function<bool(void)>> _cli_function_map;
	/**
	 * Core IO Service
	 */
	boost::asio::io_service _io_service;
};

#endif /* HORIZON_SERVER_HPP */
