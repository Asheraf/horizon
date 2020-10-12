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

#include "Char.hpp"

#include "Core/Logging/Logger.hpp"
#include "Server/Char/Session/CharSession.hpp"
#include "Server/Char/SocketMgr/ClientSocketMgr.hpp"

#include <boost/asio.hpp>
#include <boost/make_shared.hpp>
#include <iostream>

#include <sol.hpp>

using namespace Horizon::Char;

using namespace std;

/**
 * Char Constructor
 */
CharServer::CharServer() : Server()
{
	//
}

/**
 * Char Destructor
 */
CharServer::~CharServer()
{
	//
}

#define char_config_error(s, d) \
	HLog(error) << "No setting for '" << s << "' in configuration file, defaulting to '" << d << "'.";

/**
 * Read /config/char-server.yaml
 * @return true on success false on failure.
 */
bool CharServer::ReadConfig()
{
	sol::state lua;
	std::string file_path = general_conf().get_config_file_path().string();

	// Read the file. If there is an error, report it and exit.
	try {
		lua.script_file(file_path);
	} catch(const std::exception &e) {
		HLog(error) << "Char::ReadConfig: " << e.what();
		return false;
	}

	sol::table tbl = lua["horizon_config"];

	sol::table chtbl = tbl.get<sol::table>("new_character");
	get_char_config().set_start_map(chtbl.get_or("start_map", std::string("new_1-1")));
	get_char_config().set_start_x(chtbl.get_or("start_x", 53));
	get_char_config().set_start_y(chtbl.get_or("start_y", 111));
	get_char_config().set_start_zeny(chtbl.get_or("start_zeny", 0));

	sol::optional<sol::table> maybe_chitbl = chtbl.get<sol::optional<sol::table>>("start_items");

	if (maybe_chitbl) {
		sol::table chitbl = maybe_chitbl.value();
		chitbl.for_each([this](sol::object const &key, sol::object const &value) {
			get_char_config().add_start_item(std::make_pair(key.as<int>(), value.as<int>()));
		});
		if (chitbl.size() < 1) {
			get_char_config().add_start_item(std::make_pair(1201, 1));
			get_char_config().add_start_item(std::make_pair(2301, 1));
		}
	}

	get_char_config().set_character_deletion_time(tbl.get_or("character_deletion_time", 86400));

	sol::table zone_tbl = tbl.get<sol::table>("zone_server");
	get_char_config().set_zone_server_ip(zone_tbl.get_or("ip_address", std::string("127.0.0.1")));
	get_char_config().set_zone_server_port(zone_tbl.get_or("port", 5121));

	/**
	 * Process Configuration that is common between servers.
	 */
	if (!parse_common_configs(tbl))
		return false;

	HLog(info) << "Done reading server configurations from '" << file_path << "'.";

	return true;
}

#undef char_config_error

/* Initialize Char-Server CLI Commands */
void CharServer::initialize_cli_commands()
{
	Server::initialize_cli_commands();
}

/**
 * Signal handler for the Char-Server main thread.
 * @param[in|out] error   boost system error code.
 * @param[in]     signal  interrupt signal code
 */
void SignalHandler(const boost::system::error_code &error, int /*signal*/)
{
	if (!error) {
		sChar->set_shutdown_stage(SHUTDOWN_INITIATED);
		sChar->set_shutdown_signal(SIGINT);
	}
}

void CharServer::initialize_core()
{
	/* Core Signal Handler  */
	boost::asio::signal_set signals(get_io_service(), SIGINT, SIGTERM);
	signals.async_wait(SignalHandler);

	/* Start Character Network */
	ClientSocktMgr->start(get_io_service(),
						  general_conf().get_listen_ip(),
						  general_conf().get_listen_port(),
						  MAX_NETWORK_THREADS);

	Server::initialize_core();

	while (get_shutdown_stage() == SHUTDOWN_NOT_STARTED && !general_conf().is_test_run()) {
		process_cli_commands();
		_task_scheduler.Update();
		ClientSocktMgr->update_socket_sessions(MAX_CORE_UPDATE_INTERVAL);
		std::this_thread::sleep_for(std::chrono::microseconds(MAX_CORE_UPDATE_INTERVAL));
	}

	/**
	 * Cancel all pending tasks.
	 */
	_task_scheduler.CancelAll();

	/**
	 * Server shutdown routine begins here...
	 */
	Server::finalize_core();

	/**
	 * Stop all networks
	 */
	ClientSocktMgr->stop_network();

	/* Cancel signal handling. */
	signals.cancel();
}

/**
 * Main entry point of the char-server application.
 * @param argc
 * @param argv
 * @return integer of shutdown signal.
 */
int main(int argc, const char * argv[])
{
	/* Parse Command Line Arguments */
	if (argc > 1)
		sChar->parse_exec_args(argv, argc);

	/* Read Char Configuration */
	if (!sChar->ReadConfig())
		exit(SIGTERM); // Stop process if the file can't be read.

	/* Initialize the Common Core */
	sChar->initialize_core();

	/* Core Cleanup */
	HLog(info) << "Server shutting down...";

	return sChar->general_conf().get_shutdown_signal();
}
